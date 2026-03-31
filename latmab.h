#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "raylib.h"

#define SCREENWIDTH    1200
#define SCREENHEIGHT   700
#define FONTRATIO      0.45
#define FPS            60
#define LINESTART      ">> " // limited to 32 chars

#ifndef GLOBALS_H
#define GLOBALS_H

#endif

// struct definitions

/*
int_vector usage:
	int_vector v = niv(); // initialize
	pbi(12,&v); // push back 12
	int i = v.data[0]; // read data from v
	fiv(&v); // free data
*/

typedef struct{
	int* data;
	size_t size; // used space
	size_t capacity; // total space
}int_vector;

/*
double_vector usage:
	double_vector v = ndv(); // initialize
	pbd(3.14159,&v); // push back 3.14159
	double pi = v.data[0]; read data from v
	fdv(&v); // free data
*/

typedef struct{
	double* data;
	size_t size; // used space
	size_t capacity; // total space
}double_vector;

typedef struct{
	char* data;
	size_t size; // used space
	size_t capacity; // total space
	// used for text lines:
	size_t index;
	size_t lowest_editable;
	char should_push;
}char_vector;

typedef struct{
	uint8_t* data; // array of bytecode opcodes
	size_t size;   // used space
	size_t capacity; // total space avaliable
}code_vector;

typedef struct int_pair{
	int x;
	int y;
}int_pair;

typedef struct double_pair{
	double x;
	double y;
}float_pair;

typedef struct int_matrix{
	size_t rows;
	size_t cols;
	int** data;
}int_matrix;

typedef struct double_matrix{
	size_t rows;
	size_t cols;
	double** data;
}double_matrix;

typedef struct var_data{
	double_matrix* data;
	size_t size;
	size_t capacity;
}var_data;

typedef struct text_box{
	// vars owned by mcore
	int_pair cursor;
	size_t size;
	size_t capacity;
	char_vector* text;
	int_vector line_lengths;

	// vars owned by menvi
	int_pair upper_right_char; 
}text_box;

//
// In general, function names are obfuscated to incentivize
// reading function declarations
//

/* 
mcore.c:
	declaration of all functions not explicitly tied
	to mlang or menvi.

	includes:
		all functions related to text processing
		all functions related to text storage
		all functions related to matrix math 
*/

/**************************************************************

mcore.c function declarations:

**************************************************************/

// default constructor for int_vector
int_vector new_int_vector();

// push back int
void push_back_int(int val, int_vector* dest);

// delete int vector
void free_int_vector(int_vector* dest);

// default constructor for double_vector
double_vector new_double_vector();

// push back double
void push_back_double(double val, double_vector* dest);

// delete double vector
void free_double_vector(double_vector* dest);

// default constructor for char_vector
char_vector new_char_vector();

// push back char
void push_back_char(char val, char_vector* dest);

// pop char at index
void pop_char_index(size_t index, char_vector* dest);

// push char at index
void push_char_index(size_t index, char c, char_vector* dest);

// delete char vector
void free_char_vector(char_vector* dest);

// default constructor for text_box
text_box new_text_box(size_t rows);

// deallocates text box
void free_text_box(text_box* t);

// writes line to end of text box
void push_back_text(const char* line, text_box* t);

// writes contents of text box to filename
// returns 1 if successful, 0 otherwise
int write_text_box(const text_box t, char* filename);

// reads from file, writes to text box
// returns 1 is successful, 0 otherwise
int read_text_box(text_box* t, char* filename);

// prints contents of text_box to terminal
void print_text_box(text_box t);

/* 
menvi.c:
	declarations of all functions related to the UI.

	includes:
		all functions related to display of text
		all functions related to text editing UI
		all functions related to buttons / interactables
		all functions related to graphing
		
*/

/**************************************************************

menvi.c function declarations:

**************************************************************/

// applies keyboard input to text line
void update_text_line(char_vector* t);

// updates text box using keyboard input
void update_text_box(text_box* t);

// displays contents of text box
void display_text_box(int_pair upper_left, int_pair lower_right,Font font, Color tint, int fontsize, text_box t, int index);

// to keep the default raylib log from printing
void custom_log(int msgType, const char *text, va_list args);

// runs a frame of the terminal
void run_terminal(int_pair upper_left, int_pair lower_right, text_box* t, char_vector* c, Font font, Color tint, int fontsize);

/*
mlang.c:
	declarations of all functions related to implementation
	of latmab / mlang.

	includes:
		lexer, parser, interpreter for mlang
*/

/**************************************************************

mlang.c function declarations:

**************************************************************/

// enters a line into the latmab VM
void run_line(char_vector* line, text_box* t);

//
