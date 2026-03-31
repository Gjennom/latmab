#include "latmab.h"

void run_line(char_vector* line, text_box* t){
	char result[line->size + 1024];
	result[0] = '\0';
	strcat(result,line->data);
	strcat(result," is what you entered, numbnuts");
	push_back_text(result,t);
}
