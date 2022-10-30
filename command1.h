#ifndef __COMMAND1_H__
#define __COMMAND1_H__

//retira o valor de um campo da linha
char* cut_field(char *line, int begin, int end);

//extrai de uma linha de texto todos os campos separados
char** parse_line(char* line, char sorter, int num_sorter);

//executa o comando 1, le registros e os grava no arquivo
int command1(char* f_name_input, char* f_name_output);

#endif