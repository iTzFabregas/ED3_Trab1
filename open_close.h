#ifndef __OPEN_CLOSE_H__
#define __OPEN_CLOSE_H__

#include<stdio.h>

//macros importantes
#define FILE_READB 0
#define FILE_WRITEB 1
#define FILE_READT 2
#define FILE_READWRITEB 3

//abre um arquivo no modo desejado 
FILE* open_file(char* filename, int mode);

//fecha um arquivo
void close_file(FILE* file);

#endif