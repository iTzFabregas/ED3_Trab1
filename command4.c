#include "command4.h"

int field_position(FILE* file, char field_name[], int field_value_i, char field_value_s[]) {

    if (strcmp(field_name, "idConecta") == 0) { // verifica se o campo de remocao é esse

        fseek(file, 5, SEEK_CUR); // pula para a posicao desse campo
        int this_idConecta;
        fread(&this_idConecta, sizeof(int), 1, file);

        if (this_idConecta == field_value_i) { // se o valor do campo é igual ao de remocao
            return 1;
        } else {
            return 0;
        }

    } else if (strcmp(field_name, "siglaPais") == 0) { // verifica se o campo de remocao é esse

        fseek(file, 9, SEEK_CUR); // pula para a posicao desse campo
        char this_siglaPais[3];
        fread(&this_siglaPais, sizeof(char) * 2, 1, file);
        this_siglaPais[2] = '\0'; 

        if (strcmp(this_siglaPais, field_value_s) == 0) { // se o valor do campo é igual ao de remocao
            return 1;
        } else {
            return 0;
        }

    } else if (strcmp(field_name, "idPoPsConectado") == 0) { // verifica se o campo de remocao é esse

        fseek(file, 11, SEEK_CUR); // pula para a posicao desse campo
        int this_idPoPsConectado;
        fread(&this_idPoPsConectado, sizeof(int), 1, file);

        if (this_idPoPsConectado == field_value_i) { // se o valor do campo é igual ao de remocao
            return 1;
        } else {
            return 0;
        }
        
    } else if (strcmp(field_name, "unidadeMedida") == 0) { // verifica se o campo de remocao é esse

        fseek(file, 15, SEEK_CUR); // pula para a posicao desse campo
        char this_unidadeMedida[2];
        fread(&this_unidadeMedida, sizeof(char), 1, file);
        this_unidadeMedida[1] = '\0'; 

        if (strcmp(this_unidadeMedida, field_value_s) == 0) { // se o valor do campo é igual ao de remocao
            return 1;
        } else {
            return 0;
        }
        
    } else if (strcmp(field_name, "velocidade") == 0) { // verifica se o campo de remocao é esse

        fseek(file, 16, SEEK_CUR); // pula para a posicao desse campo
        int this_velocidade;
        fread(&this_velocidade, sizeof(int), 1, file);

        if (this_velocidade == field_value_i) { // se o valor do campo é igual ao de remocao
            return 1;
        } else {
            return 0;
        }
        
    } else if (strcmp(field_name, "nomePoPs") == 0) { // verifica se o campo de remocao é esse

        fseek(file, 20, SEEK_CUR); // pula para a posicao desse campo
        char this_nomePops[NOMEPOPS_TAM];
        int cnt = 0;
        do
        {
            fread(&this_nomePops[cnt], 1, 1, file);
        } while (this_nomePops[cnt++] != '|');
        this_nomePops[--cnt] = '\0';

        if (strcmp(this_nomePops, field_value_s) == 0) { // se o valor do campo é igual ao de remocao
            return 1;
        } else {
            return 0;
        }
        
    } else if (strcmp(field_name, "nomePais") == 0) { // verifica se o campo de remocao é esse

        fseek(file, 20, SEEK_CUR); // pula para a posicao do inicio dos campos de tamanho variavel
        char c;
        do // while para pular o nomePops ate o '|'
        {
            fread(&c, 1, 1, file);
        } while (c != '|');
        
        char this_nomePais[NOMEPOPS_TAM];
        int cnt = 0;
        do
        {
            fread(&this_nomePais[cnt], 1, 1, file);
        } while (this_nomePais[cnt++] != '|');
        this_nomePais[--cnt] = '\0';

        if (strcmp(this_nomePais, field_value_s) == 0) { // se o valor do campo é igual ao de remocao
            return 1;
        } else {
            return 0;
        }

    } else {
        return 0;
    }
}

int comando_4(char filename[]) {

    FILE* file = open_file(filename, FILE_READWRITEB);
    if (file == NULL) {
        return 0;
    }
    Header_reg* header = malloc(sizeof(Header_reg));
    if(read_header(header, file) == 0) {
        return 0;
    }

    int num_deletes;
    scanf("%d", &num_deletes);

    for (size_t i = 0; i < num_deletes; i++) {

        char field_name[24];
        scanf("%s", field_name);

        int field_name_i;
        char field_name_s[24];

    
        if (field_name[0] == 'i' || field_name[0] == 'v') { // campos que possuem int como entrada
            scanf("%d", &field_name_i);
        } else { // campos que possuem string entre aspas como entrada
            scan_quote_string(field_name_s);
        }


        for (size_t j = 0; j < header->proxRRN; j++) {

            fseek(file, (LEN_DISC_PAG + (LEN_REG*j)), SEEK_SET);

            char removido;
            fread(&removido, REMOVIDO_TAM, 1, file);
            if (removido == '1') { // se o registro esta removido, pula
                continue; 
            }
            
            fseek(file, -1, SEEK_CUR);
            if (field_position(file, field_name, field_name_i, field_name_s)) { // se ele retorna que esse registro deve ser deletado

                fseek(file, (LEN_DISC_PAG + (LEN_REG*j)), SEEK_SET);

                int prev_top = header->topo;
                header->topo = j; // coloca o RRN atual no topo
                header->nroRegRem++; // aumenta numero de registros deletados
                
                char removido = '1';
                int encadeamento = prev_top; // coloca o antigo topo no encadeamento
                char garbage = GARBAGE;

                fwrite(&removido,sizeof(char), 1, file);
                fwrite(&encadeamento, sizeof(int), 1, file);
                for(int i = 0; i < 59; i++){ // coloca lixo no resto do registro
                    fwrite(&garbage, sizeof(char), 1, file);
                }

                write_header(file, header); // update header

            }
        }
    }

    header->status = '1';
    write_header(file, header); // update header como status 1
    
    free(header);
    fclose(file);
    return 1;
}