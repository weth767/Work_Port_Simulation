#include <stdio.h>
#include <stdlib.h>
#include "save.h"

/*função para salvar o navio no arquivo*/
void insert_ship_on_file(int ship){
    /*ponteiro do tipo arquivo, para acessar esse arquivo*/
    FILE* arquivo;
    /*abre o arquivo*/
    arquivo = fopen("report/report.txt","a+");
    /*verificar se o fim do arquivo foi associado, ou seja tem algo no arquivo*/
    if(feof(arquivo) != 0){
        /*senão conter nada, insere da seguinte forma*/
        if(arquivo != NULL){
            fprintf(arquivo,"Relatório portuário\n\n");
            fprintf(arquivo,"Navio: %u\n",ship);
        }
    }
    /*se estiver com dados, salva da forma abaixo*/
    else{
        if(arquivo != NULL){
            fprintf(arquivo,"\n\nNavio: %u\n",ship);
        }
    }
    /*fecha o arquivo*/
    fclose(arquivo);
}
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