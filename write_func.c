#include<string.h>

#include "write_func.h"
#include "register.h"

void insert_garbage(FILE* file, int len){
    char garbage = GARBAGE;

    for(int i = 0; i < len; i++){
        fwrite(&garbage, sizeof(char), 1, file);
    }
}

void write_header2(Header_reg* header, FILE* file){
    fwrite(&header->status, sizeof(char), 1, file);
    fwrite(&header->topo, sizeof(int), 1, file);
    fwrite(&header->proxRRN, sizeof(int), 1, file);
    fwrite(&header->nroRegRem, sizeof(int), 1, file);
    fwrite(&header->nroPagDisco, sizeof(int), 1, file);
    fwrite(&header->qttCompacta, sizeof(int), 1, file);
}

void write_const_string(char* str, FILE* file, int len){
    if(strcmp(str, "") == 0){
        insert_garbage(file, len);
    } else {
        fwrite(str, sizeof(char) * len, 1, file);
    }
}

void write_var_string(char* str, FILE* file, int len){
    char pipe = DELIMITER;

    if(strcmp(str, "") != 0){
        fwrite(str, sizeof(char) * strlen(str), 1, file);    
    }
    fwrite(&pipe, sizeof(char), 1, file);
}

void write_reg(Data_reg* reg, FILE* file){
    fwrite(&reg->removido, sizeof(char), 1, file);
    fwrite(&reg->encadeamento, sizeof(int), 1, file);
    fwrite(&reg->idConecta, sizeof(int), 1, file);
    write_const_string(reg->siglaPais, file, 2);
    fwrite(&reg->idPoPsConectado, sizeof(int), 1, file); 
    write_const_string(&reg->unidadeMedida, file, 1); 
    fwrite(&reg->velocidade, sizeof(int), 1, file);

    write_var_string(reg->nomePoPs, file, strlen(reg->nomePoPs));
    write_var_string(reg->nomePais, file, strlen(reg->nomePais));
}