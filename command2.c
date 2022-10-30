#include "command2.h"

void comando_2(char filename[]) {
    FILE* file = open_file(filename, FILE_READB);
    if (file == NULL) {
        return;
    }
    Data_reg *registro = malloc(sizeof(Data_reg));
    Header_reg *header = malloc(sizeof(Header_reg));
    if(read_header(header, file) == 0) {
        return;
    }

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

    release_header(header);
    release_reg(registro);
    fclose(file);
}