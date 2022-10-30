#ifndef __PRINT_MSG_H__
#define __PRINT_MSG_H__

#include "register.h"

//mensagem de erro para erro ao tentar abrir um arquivo
void error_file();

//mensagem de erro para erro p/ registro inexistente
void error_reg();

void printar_registros(Data_reg *registro);

#endif