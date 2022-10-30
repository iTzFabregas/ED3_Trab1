#include "command6.h"

//executa o comando 6, realiza uma compactacao eficiente,
//ou seja, retira os registros removidos do arquivo de dados
int comando_6(char filename[]) {
    FILE* file = open_file(filename, FILE_READB);
    if (file == NULL) {
        return 0;
    }
    FILE* file_write = open_file("compacto.bin", FILE_WRITEB);
    if (file == NULL) {
        return 0;
    }

    Data_reg *registro = malloc(sizeof(Data_reg) * 1);
    Header_reg *header = malloc(sizeof(Header_reg) * 1);

    if(read_header(header, file) == 0) {
        return 0;
    }

    write_header(file_write, header); // reserva espaço para o header no começo do arquivo

    int reg_removidos = 0;
    for (size_t i = 0; i < header->proxRRN; i++)
    {
        fseek(file, LEN_DISC_PAG+(i*LEN_REG), SEEK_SET);
        if (read_register(file, registro) == 0) { // se o regsitro esta removido
            header->nroRegRem--;
            reg_removidos++;
            continue;
        }

        write_register(file_write, registro);
    }
    header->status = '1';
    header->topo = -1;
    header->qttCompacta++;
    //header->nroPagDisco = (int) (ceil(((double) header->proxRRN / (double) 15))) + 1;
    header->nroPagDisco = truncf((header->proxRRN-reg_removidos) / 15) + 1;
    if (header->nroPagDisco % 15 != 0) {
        header->nroPagDisco++;
    }
    header->proxRRN -= reg_removidos;

    write_header(file_write, header);
    
    free(header);
    free(registro);
    fclose(file);
    fclose(file_write);

    remove(filename); // deleta o arquivo antigo
    rename("compacto.bin", filename); // renomeia o aqruivo compactado com o nome do antigo
    return 1;
}