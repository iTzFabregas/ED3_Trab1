#ifndef __REGISTER_H__
#define __REGISTER_H__

#define LEN_DISC_PAG 960
#define LEN_REG 64
#define DELIMITER '|'
#define GARBAGE '$'

typedef struct{
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} Header_reg;

typedef struct{
    //campos de controle
    char removido;
    int encadeamento;

    //campos de tamanho fixo
    int idConecta;
    char siglaPais[3];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;

    //campos de tamanho variavel
    char* nomePoPs;
    char* nomePais;
} Data_reg;

Header_reg* create_header();

void liberar_header(Header_reg* header);

Data_reg* create_reg();

void liberar_reg(Data_reg* reg);

#endif