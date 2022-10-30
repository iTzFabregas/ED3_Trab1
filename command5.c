#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "command5.h"
#include "register.h"
#include "open_close.h"
#include "funcoesDadas.h"
#include "print_msg.h"

//executa o comando 5, insere um registro lido do teclado no arquivo
int command5(char* filename, int num_insertions){
    //abre o arquivo e cria o cabecalho
    FILE* file = open_file(filename, FILE_READWRITEB);
    Header_reg* header = create_header();
    if(!read_header(header, file)){
        release_header(header);
        close_file(file);
        return 0; //erro
    }

    //arquvio torna-se instavel durante a execucao do comando
    fseek(file, 0, SEEK_SET);
    header->status = '0';
    fwrite(&header->status, sizeof(char), 1, file);

    //realiza as n insercoes
    for(int i = 0; i < num_insertions; i++){
        //cria o registro de dados
        Data_reg* reg = create_reg();

        //variavel para pegar os campos de valores inteiros do teclado
        char* str = malloc(sizeof(char) * 10);

        scanf("%s ", str);
        if(strcmp(str, "NULO") != 0){
            reg->idConecta = atoi(str);
        } else {
            reg->idConecta = -1;
        }
        scan_quote_string(reg->nomePoPs);
        scan_quote_string(reg->nomePais);   
        scan_quote_string(reg->siglaPais);
        reg->siglaPais[2] = '\0';

        scanf(" %s", str);
        if(strcmp(str, "NULO") != 0)
            reg->idPoPsConectado = atoi(str);
        else
            reg->idPoPsConectado = -1;

        scan_quote_string(&reg->unidadeMedida);

        scanf(" %s", str);
        if(strcmp(str, "NULO") != 0)
            reg->velocidade = atoi(str);
        else
            reg->velocidade = -1;

        //calcula o tamanho do registro
        int len_reg = 22 + strlen(reg->nomePoPs) + strlen(reg->nomePais);

        //nenhum registro removido, insere no fim do arquivo
        if(header->nroRegRem == 0){
            fseek(file, 0, SEEK_END);

            write_register(file, reg);

            header->proxRRN++;
        
        //ha registros removidos, inserir conforme a pilha
        } else {
            fseek(file, LEN_DISC_PAG + (header->topo * LEN_REG) + 1, SEEK_SET); //posiciona no RRN de registro removido

            int next_rem;
            fread(&next_rem, sizeof(int), 1, file);
            fseek(file, LEN_DISC_PAG + (header->topo * LEN_REG), SEEK_SET);

            write_register(file, reg);

            header->nroRegRem--;
            header->topo = next_rem;
        }

        free(str);
        release_reg(reg);                
    }

    //calcula o numero de paginas de disco
    fseek(file, 0, SEEK_END);
    long int aux = ftell(file); 
    header->nroPagDisco = 0;
    header->nroPagDisco = aux / LEN_DISC_PAG;
    if(aux % LEN_DISC_PAG != 0){
        header->nroPagDisco++; 
    }

    //atualiza o cabecalho
    header->status = '1';
    write_header(file, header);

    //libera memoria
    release_header(header);
    close_file(file);

    return 1; //sucesso
}
