#include "command2.h"

//executa o comando 2, imprime todos os registros de um arq binario
void comando_2(char filename[]) {
    //abre arquivo p/ leitura
    FILE* file = open_file(filename, FILE_READB);
    if (file == NULL) {
        return;
    }

    //cria cabecalho e registro em memoria primaria
    Data_reg *registro = malloc(sizeof(Data_reg));
    Header_reg *header = malloc(sizeof(Header_reg));

    //le o cabecalho e pula seu lixo
    if(read_header(header, file) == 0) {
        return;
    }

    //percorre todos os registros de dados do arquivo
    int cnt = 0;
    for (size_t i = 0; i < header->proxRRN; i++) {

        fseek(file, LEN_DISC_PAG + (i*LEN_REG),SEEK_SET); // vai para o começo de cada registro

        if (read_register(file, registro)) { // se o registro n tiver sido deletado, printar
            printar_registros(registro);
        }
    }

    if (header->proxRRN == 0) { // verifica se tem registro para ser lido ou nao
        error_reg();
    }

    printf("Numero de paginas de disco: %d\n\n", header->nroPagDisco);

    //libera memoria utilizada
    release_header(header);
    release_reg(registro);
    fclose(file);
}