#include<stdio.h>

#include "register.h"

void insert_garbage(FILE* file, int len);
void write_header2(Header_reg* header, FILE* file);
void write_const_string(char* str, FILE* file, int len);
void write_var_string(char* str, FILE* file, int len);
void write_reg(Data_reg* reg, FILE* file);

