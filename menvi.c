#include "latmab.h"

// applies keyboard input to text line
void update_text_line(char_vector* t){
	char c = GetCharPressed();
	int k = GetKeyPressed();
	// key actions:
	switch(k){
		case 257: // enter
			t->should_push = 1;
			break;
		case 259: // backspace
			if(!t->index) break;
			pop_char_index(t->index - 1,t);
			t->index--;
			break;
		case 263: // left arrow
			if(!t->index) break;
			t->index--;
			break;
		case 262: // right arrow
			if(t->size - 1 == t->index) break;
			t->index++;
			break;
		case 258: // tab
			push_char_index(t->index,'\t',t);
			t->index++;
			break;
		default:
			break;
	}
	// char actions:
	if(c){
		push_char_index(t->index,c,t);
		t->index++;
	}
}

// updates text box using keyboard input
void update_text_box(text_box* t){
	
}

// displays contents of text box, 'index' is of last line
void display_text_box(int_pair upper_left, int_pair lower_right, Font font, Color tint, int fontsize, text_box t, int index){
	int num_lines = (lower_right.y - upper_left.x) / fontsize;
	int num_cols = (lower_right.x - upper_left.x) / (fontsize * FONTRATIO); 
	char buff[1024] = {0};
	if(!t.size) return;
	for(int i = 0; i < num_lines; i++){
		if(index - i < 0) break;
		strcpy(buff,t.text[index - i].data);
		buff[num_cols] = '\0'; // truncate cols to space
		Vector2 pos = {upper_left.x,upper_left.y + fontsize * (num_lines - i)};
		DrawTextEx(
			font,
			buff,
			pos,
			fontsize,
			0,
			tint
		);
	}
}

// to keep the default raylib log from printing
void custom_log(int msgType, const char *text, va_list args){
	return;
}

// runs a frame of the terminal
void run_terminal(int_pair upper_left, int_pair lower_right, text_box* t, char_vector* c, Font font, Color tint, int fontsize){
	update_text_line(c);
	if(c->should_push){
		int n = 0;
		char cdisp[c->size + 32];
		cdisp[0] = '\0';
		strcat(cdisp,LINESTART);
		strcat(cdisp,c->data);
		push_back_text(cdisp,t);
		run_line(c,t);
		free_char_vector(c);
		*c = new_char_vector();
		push_back_char('\0',c);
	}
	char cline[c->size + 32];
	cline[0] = '\0';
	strcat(cline,LINESTART);
	strcat(cline,c->data);
	DrawTextEx(
		font,
		cline,
		(Vector2){upper_left.x,lower_right.y + fontsize},
		fontsize,
		0,
		tint
	);
	display_text_box(
		upper_left,
		lower_right,
		font,
		tint,
		fontsize,
		*t,
		t->size - 1
	);
}
