#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesDadas.h"
#include "register.h"

#define REMOVIDO_TAM 1
#define ENCADEAMENTO_TAM 4
#define IDCONECTA_TAM 4
#define SIGLAPAIS_TAM 2
#define IDPOPSCONECTADO 4
#define UNIDADEMEDIDA_TAM 1
#define VELOCIDADE_TAM 4
#define NOMEPOPS_TAM 50
#define NOMEPAIS_TAM 50

typedef struct
{
    char removido;
    int encademanento;
    int idConecta;
    char siglaPais[SIGLAPAIS_TAM];
    int idPoPsConectado;
    char unidadeMedida[UNIDADEMEDIDA_TAM];
    int velocidade;
    char nomePops[NOMEPOPS_TAM]; 
    char nomePais[NOMEPAIS_TAM];

} registro;


void printar_registros(registro *registro) {
    printf("Identificador do ponto: %d\n", registro->idConecta);
    printf("Nome do ponto: %s\n", registro->nomePops);
    printf("Pais de localizacao: %s\n", registro->nomePops);
    printf("Sigla do pais: %s\n", registro->nomePais);
    printf("Identificador do ponto conectado: %d\n", registro->idPoPsConectado);
    printf("Velocidade de transmissao: %d %sbps\n", registro->velocidade, registro->unidadeMedida);
    printf("\n");
}


void comando_2(char arquivo[]) {
    FILE* file = fopen(arquivo, "rb");
    if (file == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    registro *registro = malloc(sizeof(registro));
    Header_reg *header = malloc(sizeof(Header_reg));

    int inicio = ftell(file);
    fread(&header->status, sizeof(char), 1, file);
    fread(&header->topo, sizeof(int), 1, file);
    fread(&header->proxRRN, sizeof(int), 1, file);
    fread(&header->nroRegRem, sizeof(int), 1, file);
    fread(&header->nroPagDisco, sizeof(int), 1, file);
    fread(&header->qttCompacta, sizeof(int), 1, file);
    fseek(file, 939, SEEK_CUR);
    printf("%ld\n", ftell(file) - inicio);
    
    int cnt = 0;
    int qnt_paginas = 0;
    int len = 0;
    while(fread(&registro->removido, REMOVIDO_TAM, 1, file) != 0) {

        fread(&registro->encademanento, ENCADEAMENTO_TAM, 1, file);
        fread(&registro->idConecta, IDCONECTA_TAM, 1, file);
        fread(registro->siglaPais, SIGLAPAIS_TAM, 1, file);
        fread(&registro->idPoPsConectado, IDPOPSCONECTADO, 1, file);
        fread(registro->unidadeMedida, UNIDADEMEDIDA_TAM, 1, file);
        fread(&registro->velocidade, VELOCIDADE_TAM, 1, file);
        len = 20;

        do
        {
            fread(&registro->nomePops[cnt], 1, 1, file);
            len++;
        } while (registro->nomePops[cnt++] != '|');
        registro->nomePops[--cnt] = '\0';
        cnt = 0;

        do
        {
            fread(&registro->nomePais[cnt], 1, 1, file);
            len++;
        } while (registro->nomePais[cnt++] != '|');
        registro->nomePais[--cnt] = '\0';

        fseek(file, LEN_REG-len, SEEK_CUR);
        cnt = 0;
        len = 0;

        printf("->>-->> %c\n", registro->removido);
        if(registro->removido == '0') {
            printar_registros(registro);
        }
        qnt_paginas++;
    }
    if (qnt_paginas == 0) {
        printf("Registro inexistente.\n");
    } else {
    printf("Numero de paginas de disco: %d\n\n", qnt_paginas);
    }

    free(header);
    free(registro);
    fclose(file);
}