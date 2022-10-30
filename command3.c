#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "register.h"
#include "open_close.h"
#include "funcoesDadas.h"
#include "print_msg.h"

//recebe os inputs do teclado e guarda qual sera o campo usado na busca
int receive_inputs(char fieldname[][20], char field[][20], int type_field[], int num_searches){
   for(int i = 0; i < num_searches; i++){
        scanf("%s ", fieldname[i]);

        if(strcmp(fieldname[i], "idConecta") == 0){
            scanf("%s", field[i]);
            type_field[i] = 1;
        } else if(strcmp(fieldname[i], "siglaPais") == 0){
            scan_quote_string(field[i]);
            type_field[i] = 2;
        } else if(strcmp(fieldname[i], "idPoPsConectado") == 0){
            scanf("%s", field[i]);
            type_field[i] = 3;
        } else if(strcmp(fieldname[i], "unidadeMedida") == 0){
            scan_quote_string(field[i]);
            type_field[i] = 4;
        } else if(strcmp(fieldname[i], "velocidade") == 0){
            scanf("%s", field[i]);
            type_field[i] = 5;
        } else if(strcmp(fieldname[i], "nomePoPs") == 0){
            scan_quote_string(field[i]);
            type_field[i] = 6;
        } else if(strcmp(fieldname[i], "nomePais") == 0){
            scan_quote_string(field[i]);
            type_field[i] = 7;
        } else {
            error_file();
            return 0;
        }
    }
    return 1;
}

void read_fields(Data_reg* reg, FILE* file){
    if(reg->removido == '1'){
        fseek(file, 63, SEEK_CUR);
        return;
    }

    int cnt = 0;
    int len = 20;

    fread(&reg->encadeamento, sizeof(int), 1, file);
    fread(&reg->idConecta, sizeof(int), 1, file);
    fread(reg->siglaPais, sizeof(char), 2, file);
    reg->siglaPais[2] = '\0';
    fread(&reg->idPoPsConectado, sizeof(int), 1, file);
    fread(&reg->unidadeMedida, sizeof(char), 1, file);
    fread(&reg->velocidade, sizeof(int), 1, file);
            
    do{
        fread(&reg->nomePoPs[cnt], 1, 1, file);
        len++;
    } while (reg->nomePoPs[cnt++] != '|');
        reg->nomePoPs[--cnt] = '\0';
        cnt = 0;

    do{
        fread(&reg->nomePais[cnt], 1, 1, file);
        len++;
    } while (reg->nomePais[cnt++] != '|');
    reg->nomePais[--cnt] = '\0';

    fseek(file, LEN_REG - len, SEEK_CUR);
}

//executa o comando 3, busca registros que tenham um campo igual ao especificado pelo teclado
void command3(char* filename, int num_searches){
    //variaveis para guardar os inputs
    char fieldname[num_searches][20];
    char field[num_searches][20];
    int type_field[num_searches];

    if(!receive_inputs(fieldname, field, type_field, num_searches)){
        return;
    }

    //abre o arquivo e cria um cabecalho
    FILE* file = open_file(filename, FILE_READB);
    Header_reg* header = create_header();
    if(!read_header(header, file)){
        release_header(header);
        close_file(file);
        return;
    }
    
    //realiza as n buscas
    int flag;
    for(int i = 0; i < num_searches; i++){
        flag = 1;
        Data_reg* reg = create_reg();

        if(reg->nomePais == NULL){
            error_file();
        }

        //percorre todos os registros de dados
        printf("Busca %d\n", i + 1);
        while(fread(&reg->removido, sizeof(char), 1, file) != 0) {
            read_fields(reg, file);

            //regitro removido deve ser desconsiderado
            if(reg->removido == '1'){
                continue;
            }

            //verifica se o registro possui o campo igual ao especificado na busca
            int value;
            switch (type_field[i]){
            case 1:
                value = atoi(field[i]);

                if(reg->idConecta == value){
                    printar_registros(reg);
                    flag = 0;
                }
                break;
            case 2:
                if(strcmp(reg->siglaPais, field[i]) == 0){
                    printar_registros(reg);
                    flag = 0;
                }
                break;
            case 3:
                value = atoi(field[i]);

                if(reg->idPoPsConectado == value){
                    printar_registros(reg);
                    flag = 0;
                }
                break;
            case 4:
                if(reg->unidadeMedida == field[i][0]){
                    printar_registros(reg);
                    flag = 0;
                }
                break;
            case 5:
                value = atoi(field[i]);

                if(reg->velocidade == value){
                    printar_registros(reg);
                    flag = 0;
                }
                break;
            case 6:
                if(strcmp(reg->nomePoPs, field[i]) == 0){
                    printar_registros(reg);
                    flag = 0;
                }
                break;
            case 7:
                if(strcmp(reg->nomePais, field[i]) == 0){
                    printar_registros(reg);
                    flag = 0;
                }
                break;
            default:
                break;
            }
        }
        
        //se nenhum registro coincidiu com a busca
        if(flag){
            error_reg();
        }

        printf("Numero de paginas de disco: %d\n\n", header->nroPagDisco);

        //desaloca memoria e volta o arquivo para o primeiro reg de dados
        release_reg(reg);
        fseek(file, 960, SEEK_SET);
    }
    
    //desaloca memoria
    release_header(header);
    close_file(file);
}