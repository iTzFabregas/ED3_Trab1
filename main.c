/*
Fabricio Sampaio [runcodes] - 12547423 - participacao: 100%
Pedro Lucas Castro de Andrade - 11212289 - participacao: 100%
*/

#include<stdio.h>

#include "command1.h"
#include "command2.h"
#include "command3.h"
#include "command4.h"
#include "command5.h"
#include "command6.h"
#include "funcoesDadas.h"

int main(void) {
    //variaveis p/ entrada do teclado
    int command;
    char f_name_input[30];
    char f_name_output[30];
    int num_searches;
    int num_insertions;

    //le do teclado qual o comando sera acionado
    scanf("%d ", &command);

    //aciona a execucao do comando lido
    switch (command){
        case 1:
            //le os nomes dos arquivos que serao usados no comando 1
            scanf("%s %s", f_name_input, f_name_output);
            
            //executa o comando 1
            if(command1(f_name_input, f_name_output)){
                binarioNaTela(f_name_output);
            }
            break;
        case 2:
            // le o nome do arquivo
            scanf("%s", f_name_input);

            // executa comando 2
            comando_2(f_name_input);
            break;
        case 3:
            //le o nome do arquivo e o numero de buscas p/ o comando 3
            scanf("%s %d", f_name_input, &num_searches);
            
            //executa o comando 3
            command3(f_name_input, num_searches);
            break;
        case 4:
            // le nome arquivo de entrada
            scanf("%s", f_name_input);

            // execurta comando 4
            if(comando_4(f_name_input) == 1) { // se o programa terminou certinho
                binarioNaTela(f_name_input);
            }
            break;
        case 5:
            //le o nome do arquivo e o numero de insercoes p/ o comando 5
            scanf("%s %d", f_name_input, &num_insertions);
            
            //executa o comando 5
            if(command5(f_name_input, num_insertions)){
                binarioNaTela(f_name_input);
            }
            break;
        case 6:
            scanf("%s", f_name_input);
            if(comando_6(f_name_input) == 1) {
                binarioNaTela(f_name_input);
            }
            break;
    }
}