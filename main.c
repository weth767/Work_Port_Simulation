/*minhas bibliotecas*/
#include "stack.h"
#include "queue.h"
#include "bool.h"
#include "keyboard.h"
/*bibliotecas padrões do c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define TIMER 2000000 //2 segundos

/*criação da estrutura para o barco*/
/*deve ser possivel o posicionamento de N barco*/
/*são gerados 0-3 barcos a cada unidade de tempo(por enquanto 2 segundos)*/
typedef struct SHIP{
    unsigned int id;//identificação de cada barco
    stack st[4];//conteiners que ele carrega, cada pilha deve conter no máximo 4 containers
    /*um total de 16 containers*/
}ship;
/*criação da estrutura do guindaste, que pega os containers do navio, e leva para uma área destinada
cada área de atracamento tem sua própria grua*/
typedef struct CRANE{
    unsigned int id;//identificação da grua 0-3 ou 1-4
    bool status;//status para verificar se a grua está cheia 
}crane;
/*criação da estrutura para a travessa, que seria o local onde destina-se os containers deepois de pegos
pela grua, onde ela pode suportar 5 pilhas de 5 containers cada, assim que estiver cheia, o straddle carrier
deve vir buscar e esvaziar a travessa*/
typedef struct PLATTER{
    unsigned int id;//identificação de cada travessa, são 4 ao todo, uma para cada área de atracamento
    stack st[5];//5 pilhas, que devem conter até 5 containers cada
    bool status;//status da travessa, que indica se ela está cheia ou não, estiver o carrier deve esvazia-la
}platter;


/*função para a criação do container, que seria apenas seu id*/
int container_generator(){
    /*retona um valor entre 1 e 1000*/
    int valor = (rand() % 1000) + 1;
    //printf("%i\n",valor);
    return(valor);
}

/*função que gera navios nas filas, pode gerar de 0 a 3 navios, eles serão colocados, um em cada fila*/
ship* ship_generator(int amount){
    /*verifica se a quantidade é igual a zero, e como assim não precisará alocar nada*/
    /*já retorna null*/
    if(amount == 0){
        return(NULL);
    }
    /*se for diferente de 0, aloca memoria para um vetor de navios*/
    ship* sh = (ship*)malloc(amount * sizeof(ship));
    /*cria uma variavel do tipo barco*/
    ship watercraft;
    /*o primeiro laço, é para inserir os navios no vetor*/
    for(int i = 0; i < amount; i++){
        /*gera um id, entre 1 e 1000*/
        watercraft.id = rand() % 1000 + 1;
        /*o segundo laço é para as pilhas de containers*/
        for(int j = 0; j < 4; j++){
            /*cria a pilha*/
            watercraft.st[j] = create_stack();
            /*o mais interno é para a quantidade de containers de cada pilha*/
            for(int k = 0; k < (rand() % 4 + 1); k++){
                /*empilha uma quantidade aleatoria de containers na pilha atual da iteração*/
                stack_up(watercraft.st[j],container_generator());
            }
        }
        sh[i] = watercraft;
    }
    /*e retorna seu ponteiro*/
    return(sh);
}



int main(){
    srand(time(NULL)); 
    int start_time,end_time;
    int amount;
    printf("Programa de Simulação de Funcionamento Portuário\n");
    time_t timer; //variável que guarda um tempo
    struct tm *ck;  //estrutura que guarda um tempo
    timer = time(NULL); //recebe tempo
    ck = localtime( &timer ); //seta o relogio como a hora local
    printf("Hora de Inicio: %i:%i:%i\n",ck->tm_hour,ck->tm_min,ck->tm_sec);/*mostra na tela a 
    hora, minutos e segundos*/
    start_time = clock();/*pega o clock inicial para ser usado como um comparador de tempo*/
    /*loop que irá executar até que alguma tecla seja pressionado, função da lib keyboard.h*/
    while(!keyboard_pressed()){
        /*agora pega o clock final*/
        end_time = clock();
        /*e faz a diferença, se for maior ou igual a constante TIMER(2 segundos)*/
        if((end_time - start_time) >= TIMER){
            /*renova o clock inicial*/
            start_time = clock();
            /*gera um numero aleatorio para criar os barcos*/
            amount = rand() % 4;
            /*passa para a função de criação de barcos, ela retornará um vetor de barcos*/
            ship* sh = NULL;
            sh = ship_generator(amount);
            /*verifica se o vetor é diferente de NULL, ou seja tem conteudo*/
            if(sh != NULL){
                /**/
                printf("%i\n",amount);
                printf("%i\n",sh[0].id);
                show_stack(sh[0].st[0]);
                show_stack(sh[0].st[1]);
                show_stack(sh[0].st[2]);
                show_stack(sh[0].st[3]);
            }
            else{
                printf("Não Houveram navios nesse período de tempo!\n");
            }
        } 
    }
    return(0);
}