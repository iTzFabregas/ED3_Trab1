#include <stdio.h>
#include <stdlib.h>

#include "register.h"
#include "print_msg.h"

//aloca memoria e inicializa variaveis para o cabecalho
Header_reg* create_header(){
    Header_reg* header = malloc(sizeof(Header_reg));
    header->status = '0';
    header->topo = -1;
    header->proxRRN = 0;
    header->nroRegRem = 0;
    header->nroPagDisco = 0;
    header->qttCompacta = 0;

    return header;
}

//libera memoria usada no cabecalho
void release_header(Header_reg* header){
    free(header);
    header = NULL;
}

//aloca memoria e inicializa variaveis para o reg de dados
Data_reg* create_reg(){
    Data_reg* reg = malloc(sizeof(Data_reg));
    reg->removido = '0';
    reg->encadeamento = -1;

    return reg;
}

//libera memoria usada no reg de dados
void release_reg(Data_reg* reg){
    free(reg);
    reg = NULL;
}

//le os campos do cabecalho
int read_header(Header_reg* header, FILE* file){
    fread(&header->status, sizeof(char), 1, file);
    if(header->status == '0'){
        error_file();
        return 0; //erro no arquivo    
    }
    
    fread(&header->topo, sizeof(int), 1, file);
    fread(&header->proxRRN, sizeof(int), 1, file);
    fread(&header->nroRegRem, sizeof(int), 1, file);
    fread(&header->nroPagDisco, sizeof(int), 1, file);
    fread(&header->qttCompacta, sizeof(int), 1, file);

    fseek(file, 939, SEEK_CUR);

    return 1; //sucesso
}

//le todos os campos de um registro do arquivo de dados
int read_register(FILE* file, Data_reg* registro) {

    int cnt;
    fread(&registro->removido, REMOVIDO_TAM, 1, file);
    if (registro->removido == '1') { // se o registro esta removido, pula
        return 0;
    }

    fread(&registro->encadeamento, ENCADEAMENTO_TAM, 1, file);
    fread(&registro->idConecta, IDCONECTA_TAM, 1, file);
    fread(registro->siglaPais, SIGLAPAIS_TAM, 1, file);
    registro->siglaPais[2] = '\0';
    fread(&registro->idPoPsConectado, IDPOPSCONECTADO, 1, file);
    fread(&registro->unidadeMedida, UNIDADEMEDIDA_TAM, 1, file);
    fread(&registro->velocidade, VELOCIDADE_TAM, 1, file);  

    cnt = 0;
    do // le o campo variavel char por char até o '|'
    {
        fread(&registro->nomePoPs[cnt], 1, 1, file);
    } while (registro->nomePoPs[cnt++] != '|');
    registro->nomePoPs[--cnt] = '\0';

    cnt = 0;
    do // le o campo variavel char por char até o '|'
    {
        fread(&registro->nomePais[cnt], 1, 1, file);
    } while (registro->nomePais[cnt++] != '|');
    registro->nomePais[--cnt] = '\0';
    
    return 1;
}

//escreve o cabecalho no arquivo indicado
void write_header(FILE* file, Header_reg* header) {
    fseek(file, 0, SEEK_SET);

    fwrite(&header->status, sizeof(char), 1, file);
    fwrite(&header->topo, sizeof(int), 1, file);
    fwrite(&header->proxRRN, sizeof(int), 1, file);
    fwrite(&header->nroRegRem, sizeof(int), 1, file);
    fwrite(&header->nroPagDisco, sizeof(int), 1, file);
    fwrite(&header->qttCompacta, sizeof(int), 1, file);
    char garbage = GARBAGE;
    for(size_t i = 0; i < 939; i++){
        fwrite(&garbage, sizeof(char), 1, file);
    }
}

//escreve os campos de registro e seu lixo no arquivo indicado
void write_register(FILE* file_write, Data_reg* registro) {
    fwrite(&registro->removido, REMOVIDO_TAM, 1, file_write);
    fwrite(&registro->encadeamento, ENCADEAMENTO_TAM, 1, file_write);
    fwrite(&registro->idConecta, IDCONECTA_TAM, 1, file_write);
    fwrite(registro->siglaPais, SIGLAPAIS_TAM, 1, file_write);
    fwrite(&registro->idPoPsConectado, IDPOPSCONECTADO, 1, file_write);
    fwrite(&registro->unidadeMedida, UNIDADEMEDIDA_TAM, 1, file_write);
    fwrite(&registro->velocidade, VELOCIDADE_TAM, 1, file_write);
    int len = 20;
    

    int cnt = 0;
    while(registro->nomePoPs[cnt] != '|' && registro->nomePoPs[cnt] != '\0') {
        fwrite(&registro->nomePoPs[cnt++], sizeof(char), 1, file_write);
        len++;
    }

    if (registro->nomePoPs[cnt] != '|') {
        registro->nomePoPs[cnt] = '|';
    }
    fwrite(&registro->nomePoPs[cnt], sizeof(char), 1, file_write);
    len++;


    cnt = 0;
    while(registro->nomePais[cnt] != '|' && registro->nomePais[cnt] != '\0') {
        fwrite(&registro->nomePais[cnt++], sizeof(char), 1, file_write);
        len++;
    }
    if (registro->nomePais[cnt] != '|') {
        registro->nomePais[cnt] = '|';
    }
    fwrite(&registro->nomePais[cnt], sizeof(char), 1, file_write);
    len++;
    

    char garbage = GARBAGE;
    for(size_t i = 0; i < LEN_REG-len; i++){
        fwrite(&garbage, sizeof(char), 1, file_write);
    }
}
