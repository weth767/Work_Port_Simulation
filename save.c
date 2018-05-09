#include <stdio.h>
#include <stdlib.h>
#include "save.h"

/*função para inserir containers no arquivo*/
void insert_container_on_file(int container){
    /*ponteiro do tipo arquivo, para acessar esse arquivo*/
    FILE* arquivo;
    /*abre o arquivo*/
    arquivo = fopen("report/storage.txt","a+");
    /*se o ponteiro recebeu algo*/
    if(arquivo != NULL){
        /*salva no arquivo*/
        fprintf(arquivo,"Container: %u\n",container);
    }
    /*fecha o arquivo*/
    fclose(arquivo);
}