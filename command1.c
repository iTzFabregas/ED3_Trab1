#include<stdlib.h>
#include<string.h>

#include "command1.h"
#include "register.h"
#include "funcoesDadas.h"
#include "open_close.h"

#include "write_func.h"

//retira o valor de um campo da linha
char* cut_field(char *line, int begin, int end){
    char* field = malloc(sizeof(char) * (end - begin + 2));

    int i;
    for(i = 0; (i+begin <= end); i++){
        field[i] = line[begin + i];
    }

    //retira um espaço em branco no fim do campo
    if(i > 0 && field[i-1] == ' '){
        field[i - 1] = '\0';    
    } else {
        field[i] = '\0';
    }
    
    return field;
}

//extrai de uma linha de texto todos os campos separados
char** parse_line(char* line, char sorter, int num_sorter){
    //calcula o tamanho total da linha
    int end = 0;
    for(end = 0; line[end] != '\n' && line[end] != '\0'; end++);

    //aloca memoria necessaria
    char** fields = malloc(sizeof(char*) * (num_sorter + 1));
    int* pos_sorter = malloc(sizeof(int) * num_sorter);

    //encontra a posicao dos separadores de campos
    int j = 0;
    for(int i = 0; i < end; i++){
        if(line[i] == sorter){
            pos_sorter[j] = i;
            j++;
        }
    }

    //extrai os campos
    fields[0] = cut_field(line, 0, pos_sorter[0] - 1);
    for(int i = 0; i < (num_sorter - 1); i++){
        fields[i+1] = cut_field(line, pos_sorter[i] + 1, pos_sorter[i+1] - 1);
    }
    fields[num_sorter] = cut_field(line, pos_sorter[num_sorter-1] + 1, end);

    //desaloca memoria utilizada
    free(pos_sorter);

    return  fields;
}

//executa o comando 1, le registros e os grava no arquivo
int command1(char* f_name_input, char* f_name_output){
    //abre os arquivos de entrada e saida
    FILE* file_input = open_file(f_name_input, FILE_READT);
    if(file_input == NULL){
        return 0; //erro
    }
    FILE* file_output = open_file(f_name_output, FILE_WRITEB);
    if(file_output == NULL){
        return 0; //erro
    }

    //cria um registro de cabecario e o escreve, mais o lixo, no arquivo de saida
    Header_reg* header = create_header();
    write_header(file_output, header);

    //o registro de cabecario ocupa uma pagina de disco
    header->nroPagDisco++;

    //aloca memoria para ler as linhas do arquivo de entrada
    char* line = malloc(sizeof(char) * 100);
    
    //le a primeira linha p/ pular os nomes dos campos
    fgets(line, 100, file_input);

    int num_bytes = 0;
    char pipe = DELIMITER;

    //le todas as linhas restantes do arquivo de entrada
    while(fgets(line, 100, file_input)){
        //cria um registro de dados
        Data_reg* reg = create_reg();
        
        //guarda os valores de um campo em um vetor dinamico
        char** fields = parse_line(line, SORTER, 6);

        //registro de dados recebe os campos adequados
        //faz conversao para int nos campos devidos
        reg->idConecta = atoi(fields[0]) ? atoi(fields[0]) : -1;
        

        strcpy(reg->nomePoPs, fields[1]);
        
        strcpy(reg->nomePais, fields[2]);

        strcpy(reg->siglaPais, fields[3]);

        reg->idPoPsConectado = atoi(fields[4]) ? atoi(fields[4]) : -1;

        strcpy(&reg->unidadeMedida, fields[5]);

        reg->velocidade = atoi(fields[6]) ? atoi(fields[6]) : -1;

        //calcula o tamanho de todos os campos juntos
        int len_reg = 22 + strlen(reg->nomePoPs) + strlen(reg->nomePais);

        //escreve no arquivo de saida o reg de dados e a quantidade certa de lixo
        write_reg(reg, file_output);
        insert_garbage(file_output, (LEN_REG - len_reg));

        //cada reg de dados representa um rrn e 64 bytes
        header->proxRRN++;
        num_bytes += 64;

        //desaloca memoria do vetor dinamico
        for(int i = 0; i < 7; i++){
            free(fields[i]);
        }
        free(fields);

        release_reg(reg);
    }

    //calcula a quantidade de pags de disco usadas no arquivo de saida
    if(num_bytes > LEN_DISC_PAG){
        header->nroPagDisco += num_bytes / LEN_DISC_PAG;
        if(num_bytes % LEN_DISC_PAG != 0){
            header->nroPagDisco++;
        }
    } else if (num_bytes > 0){
        header->nroPagDisco++;
    }

    //retorna ao inicio do arquivo e atualiza o reg de cabecalho
    fseek(file_output, 0, SEEK_SET);
    header->status = '1';
    write_header2(header, file_output);

    //fecha os arquivos e desaloca as memorias usadas
    close_file(file_input);
    close_file(file_output);
    release_header(header);

    return 1;
}