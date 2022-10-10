#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "comando2.h"
#include "funcoesDadas.h"

int main(void) {
    int command;
    char f_name_input[30];
    
    scanf("%d ", &command);

    switch (command){
        case 2:
            scanf("%s", f_name_input);
            comando_2(f_name_input);
            break;
    }
}
