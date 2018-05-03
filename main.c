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
    stack containers[4];//conteiners que ele carrega, cada pilha deve conter no máximo 4 containers
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
typedef struct DOCK{
    unsigned int id;//identificação de cada área de atracamento, são 4 ao todo, uma para cada área de atracamento
    stack platter[5];//5 pilhas, que devem conter até 5 containers cada
    bool status;//status da doca, que indica se ela está cheia ou não, estiver o carrier deve esvazia-la
}dock;

typedef struct CARRIER{
    unsigned id;
    unsigned id_container;
    bool status;
}carrier;


/*função para a criação do container, que seria apenas seu id*/
int container_generator(){
    /*retona um valor entre 1 e 1000*/
    int valor = (rand() % 1000) + 1;
    //printf("%i\n",valor);
    return(valor);
}

/*função que gera navios nas filas, pode gerar de 0 a 3 navios, eles serão colocados, um em cada fila*/
ship* ship_generator(int amount){
    srand(time(NULL));
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
            watercraft.containers[j] = create_stack();
            /*o mais interno é para a quantidade de containers de cada pilha*/
            for(int k = 0; k < (rand() % 4 + 1); k++){
                /*empilha uma quantidade aleatoria de containers na pilha atual da iteração*/
                stack_up(watercraft.containers[j],container_generator());
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
    int queue_control = 0;
    printf("Programa de Simulação de Funcionamento Portuário\n");
    time_t timer; //variável que guarda um tempo
    struct tm *ck;  //estrutura que guarda um tempo
    timer = time(NULL); //recebe tempo
    ck = localtime( &timer ); //seta o relogio como a hora local
    printf("Hora de Inicio: %i:%i:%i\n",ck->tm_hour,ck->tm_min,ck->tm_sec);/*mostra na tela a 
    hora, minutos e segundos*/
    start_time = clock();/*pega o clock inicial para ser usado como um comparador de tempo*/
    /*áreas de atracamento*/
    dock d[4];
    /*carregadores*/
    carrier car[4];
    /*guindastes*/
    crane cr[4];
    /*filas de atracamento*/
    queue q[4];
    /*criando as filas*/
    for(int i = 0; i < 4; i++){
        q[i] = create_queue();
    }
    /*loop que irá executar até que alguma tecla seja pressionado, função da lib keyboard.h*/
    while(!keyboard_pressed()){
        srand(time(NULL));
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
                /*já que houveram navios, distribui em cada fila*/
                /*variavel para o controle das filas*/
                
                /*e um for que itera a quantidade de navios gerados*/
                for(int i = 0; i < amount; i++){
                    /*enfileira os barcos que chegaram, de acordo o indice controlado 
                    pela variavel int acima*/
                    line_up(q[queue_control],sh[i].id,sh[i].containers);
                    printf("\n------------------------------------------------------\n");
                    printf("Fila: %i\n",queue_control);
                    show_queue(q[queue_control]);
                    /*se o valor dela for dois, soma mais um para fazer a terceira*/
                    /*e pula o restante do laço, para evitar o bug de não inserir
                    navios na fila 3*/
                    if(queue_control == 2){
                        queue_control++;
                        continue;
                    }
                    /*se o valor for igual a 3, zera o controlador*/
                    else if(queue_control == 3){
                        queue_control = 0;
                        /*e da um continue para já ir para o inicio do laço*/
                        continue;
                    }
                    /*por fim caso não ocorra alguma das condições, soma normalmente o controle*/
                    queue_control++;
                }
                /*no final, mostra as filas e quantos barcos tem*/
                /*for(int i = 0; i <= 3; i++){
                    printf("Fila %i\n",i);
                    show_queue(q[i]);
                }*/
            }
            /*caso não tiver algum barco, mostra mensagem na tela que não houveram barcos nesse momento*/
            else{
                printf("Não Houveram navios nesse período de tempo!\n");
            }

        } 
    }
    return(0);
}