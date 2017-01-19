#include <stdio.h>
#include <stdlib.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_image.h"

int main(int argc,char** argv){
	al_init();
	al_init_image_addon();
	al_init_native_dialog_addon();
	/**< 選擇一張圖片來裁切 */
	printf("choose a picture to clip\n");
	ALLEGRO_FILECHOOSER* fileChooser = al_create_native_file_dialog("./","選擇一張圖片來裁切"
													,NULL,ALLEGRO_FILECHOOSER_PICTURES);
	al_show_native_file_dialog(NULL,fileChooser);

	if(al_get_native_file_dialog_count(fileChooser)!=1){
		printf("no choose any file\n");
		al_destroy_native_file_dialog(fileChooser);
		return 0;
	}

	const char* filename = al_get_native_file_dialog_path(fileChooser,0);
	printf("要切成幾個pixel? ");
	int cutPixel = 0;
	scanf("%d",&cutPixel);

	printf("%s",filename);
	ALLEGRO_BITMAP* bitmap = al_load_bitmap(filename);
	if(bitmap==NULL)return 0;

	int width = al_get_bitmap_width(bitmap);
	int height = al_get_bitmap_height(bitmap);

	int count = 0;

	int x = 0;
	int y = 0;

	mkdir("Output/");
	for(y=0;y<height;y+=cutPixel){
		for(x=0;x<width;x+=cutPixel){
			ALLEGRO_BITMAP* tmpBitmap =al_create_bitmap(cutPixel,cutPixel);
			al_set_target_bitmap(tmpBitmap);
			al_draw_bitmap_region(bitmap,x,y,cutPixel,cutPixel,0,0,0);
			char saveName[100];
			sprintf(saveName,"Output/pic%05d.jpg",count);
			printf("%s\n",saveName);
			al_save_bitmap(saveName,tmpBitmap);

			al_destroy_bitmap(tmpBitmap);
			count++;
		}
	}
	printf("Success\n");
	return 0;
}
