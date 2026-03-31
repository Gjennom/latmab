#include "latmab.h"

int main(){
	SetTraceLogCallback(custom_log);
	InitWindow(SCREENWIDTH,SCREENHEIGHT,"Latmab 2026");
	SetTargetFPS(FPS);
	Font roboto_mono = LoadFontEx(
		"resources/RobotoMono-Regular.ttf",
		255,
		NULL,
		0
	);

	text_box t = new_text_box(0);
	read_text_box(&t,"mcore.c");
	char_vector c = new_char_vector();
	push_back_char('\0',&c);
	Color VERYDARKGRAY = {20,20,20,255};
	long GFC = 0;
	int_pair ul = {0,0};
	int_pair lr = {600,200};
	Vector2 upperleft = {100,100};
	while(!WindowShouldClose()){
		GFC++;/*
		update_text_line(&c);
		if(c.should_push){
			push_back_text(c.data,&t);
			free_char_vector(&c);
			c = new_char_vector();
			push_back_char('\0',&c);
		}*/
		BeginDrawing();
		ClearBackground(VERYDARKGRAY);/*
		DrawTextEx(roboto_mono,c.data,(Vector2){ul.x,lr.y+20},20,0,WHITE);
		display_text_box(
			ul,
			lr,
			roboto_mono,
			LIGHTGRAY,
			20,
			t,
			t.size - 1
		);*/

		run_terminal(
			ul,
			lr,
			&t,
			&c,
			roboto_mono,
			WHITE,
			20
		);
		EndDrawing();
	}

	free_text_box(&t);
	free_char_vector(&c);
	UnloadFont(roboto_mono);
	return 0;
}
