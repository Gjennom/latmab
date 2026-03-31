#include "latmab.h"

// default constructor for int_vector
int_vector new_int_vector(){
	int_vector result;
	result.data = calloc(1,sizeof(int));
	result.size = 0;
	result.capacity = 1;
	return result;
}

// push back int
void push_back_int(int val,int_vector* dest){
	if(dest->size == dest->capacity){
		int* new_data = calloc(dest->capacity * 2,sizeof(int));
		dest->capacity *= 2;
		for(int i = 0; i < dest->size; i++){
			new_data[i] = dest->data[i];
		}
		free(dest->data);
		dest->data = new_data;
	}
	dest->data[dest->size] = val;
	dest->size++;	
}

// delete int vector
void free_int_vector(int_vector* dest){
	free(dest->data);
}

// default constructor for double_vector
double_vector new_double_vector(){
	double_vector result;
	result.data = calloc(1,sizeof(double));
	result.size = 0;
	result.capacity = 1;
	return result;
}

// push back double
void push_back_double(double val,double_vector* dest){
	if(dest->size == dest->capacity){
		double* new_data = calloc(dest->capacity * 2, sizeof(double));
		dest->capacity *= 2;
		for(int i = 0; i < dest->size; i++){
			new_data[i] = dest->data[i];
		}
		free(dest->data);
		dest->data = new_data;
	}
	dest->data[dest->size] = val;
	dest->size++;
}

void free_double_vector(double_vector* dest){
	free(dest->data);
}

code_vector new_code_vector(){
	code_vector result;
	result.data = calloc(8,sizeof(uint8_t));
	result.size = 0;
	result.capacity = 8;
	return result;
}

void push_back_code(uint8_t val,code_vector* dest){
	if(dest->size == dest->capacity){
		size_t new_cap = dest->capacity * 2;
		uint8_t* new_data = realloc(dest->data,new_cap);
		if(!new_data) exit(1);
		dest->data = new_data;
	}
	dest->data[dest->size] = val;
	dest->size++;
}

void free_code_vector(code_vector* dest){
	free(dest->data);
}

// default constructor for char_vector
char_vector new_char_vector(){
	char_vector result;
	result.data = calloc(1,sizeof(char));
	result.size = 0;
	result.capacity = 1;
	result.index = 0;
	result.should_push = 0;
	result.lowest_editable = 3;
	return result;
}

// push back char
void push_back_char(char val, char_vector* dest){
	if(dest->size == dest->capacity){
		char* new_data = calloc(dest->capacity * 2,sizeof(char));
		dest->capacity *= 2;
		for(int i = 0; i < dest->size; i++){
			new_data[i] = dest->data[i];
		}
		free(dest->data);
		dest->data = new_data;
	}
	dest->data[dest->size] = val;
	dest->size++;
}

// pop char at index
void pop_char_index(size_t index, char_vector* dest){
	for(int i = index; i < dest->size - 1; i++){
		dest->data[i] = dest->data[i + 1];
	} dest->size--;
}

// push char at index
void push_char_index(size_t index, char c, char_vector* dest){
	push_back_char(dest->data[dest->size],dest);
	for(int i = dest->size; i > index; i--){
		dest->data[i] = dest->data[i - 1];
	} dest->data[index] = c;
}

// delete char vector
void free_char_vector(char_vector* dest){
	free(dest->data);
}

// allocate text box
text_box new_text_box(size_t rows){
	text_box t;
	t.cursor = (int_pair){0, 0};
	t.size = rows;
	t.capacity = (rows) ? rows * 2 : 1; // 1 if rows == 0
	t.line_lengths = new_int_vector();
	t.text = calloc(rows * 2, sizeof(char_vector));
	for(int i = 0; i < rows; i++){
		t.text[i] = new_char_vector();
		push_back_char('\0',&t.text[i]);
		push_back_int(1,&t.line_lengths);
	} return t;
}

// deallocates text box
void free_text_box(text_box* t){
	free_int_vector(&t->line_lengths);
	for(int i = 0; i < t->capacity; i++){
		free_char_vector(&t->text[i]);
	} free(t->text);
}

// writes line to end of text box
void push_back_text(const char* line, text_box* t){
	size_t linelen = strlen(line);
	if(t->size == t->capacity){
		char_vector* new_data = calloc(t->capacity * 2 + 1,sizeof(char_vector));
		t->capacity *= 2;
		for(int i = 0; i < t->size; i++){
			new_data[i] = t->text[i];
		} free(t->text);
		t->text = new_data;
	}
	push_back_int(linelen,&t->line_lengths);
	char* newline = calloc(linelen + 1, sizeof(char));
	strcpy(newline, line);
	t->text[t->size].data = newline;
	t->size++;
}

// writes contents of text box to filename
// returns 1 if successful, 0 otherwise
int write_text_box(const text_box t,char* filename){
	FILE* fout;
	fout = fopen(filename,"wb");
	if(!fout){
		printf("%s is an invalid destination\n",filename);
		return -1;
	}
	for(int i = 0; i < t.size; i++){
		fprintf(fout,"%s/n",t.text[i].data);
	} return 1;
}

// reads from file, writes to text box, limited 1024 chars per line
// returns 1 is successful, 0 otherwise
int read_text_box(text_box* t,char* filename){
	FILE* fin;
	fin = fopen(filename,"r");
	char line[1024];
	if(!fin){
		printf("%s is an invalid file name\n",filename);
		return -1;
	}
	while(fgets(line,sizeof(line),fin)){
		push_back_text(line, t);
	} fclose(fin);
	return 1;
}

// prints contents of text_box to terminal
void print_text_box(text_box t){
	printf(
		"Cursor: {%i, %i}\nSize: %i\nCapacity: %i\n",
		t.cursor.x,
		t.cursor.y,
		t.size,
		t.capacity
	);
	for(int i = 0; i < t.size; i++){
		printf(
			"%-6i| %s", 
			t.line_lengths.data[i], 
			t.text[i].data
		);
	}
}

