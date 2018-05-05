/*minhas bibliotecas*/
#include "queue.h"
#include "stack.h"
#include "bool.h"
#include "keyboard.h"
#include "save.h"
/*bibliotecas padrões do c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define TIMER 2000000 //2 segundos
#define TIMER_CARRIER 1000000 // 1 Segundo

/*criação da estrutura para o barco*/
/*deve ser possivel o posicionamento de N barco*/
/*são gerados 0-3 barcos a cada unidade de tempo(por enquanto 2 segundos)*/
typedef struct SHIP{
    unsigned int id;//identificação de cada barco
    stack containers[4];
    int amount_containers;//conteiners que ele carrega, cada pilha deve conter no máximo 4 containers
    /*um total de 16 containers*/
}ship;
/*criação da estrutura para a travessa, que seria o local onde destina-se os containers deepois de pegos
pela grua, onde ela pode suportar 5 pilhas de 5 containers cada, assim que estiver cheia, o straddle carrier
deve vir buscar e esvaziar a travessa*/
typedef struct DOCK{
    unsigned int id;/*identificação do navio que chega, entretanto tem que observar bem
    pois cada navio pode conter no maximo 16 container e cabem 25, ou seja tem que ser guardados os ids
    dos navios*/
    stack platter[5];//5 pilhas, que devem conter até 5 containers cada
}dock;
/*estrutura do carregador, vai guardar o id do container armazenado no porto*/
typedef struct CARRIER{
    unsigned id_container;//id do container retirado
    bool status;//status do carrier
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
    int total;
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
        total = 0;
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
                total++;
            }
        }
        watercraft.amount_containers = total;
        
        sh[i] = watercraft;
    }
    /*e retorna seu ponteiro*/
    return(sh);
}
/*função para contar o tempo, entra a quantidade em segundos*/
void chronometer(int seconds){
    /*pega o clock inicial*/
    int start_time,end_time;
    start_time = clock();
    while(1){
        /*atualiza a final ate que o tempo seja maior ou igual ao passado por parametro*/
        end_time = clock();
        if((end_time - start_time) >= (seconds * 1000000)){
            /*ai sai da função*/
            break;
        }
    }
}
/*função para teste*/
void teste(){
    stack t = create_stack();
    for(int i = 0; i < 3; i++){
        stack_up(t,i+1);
    }
    show_stack(t);
    printf("\n%i\n",return_int_value_of_stack(t,4));
}

/*função principal*/
int main(){
    /*variaveis de uso geral na aplicação*/
    srand(time(NULL)); 
    int amount;
    int queue_control = 0;
    int remove_control;
    int stack_ship_control;
    int stack_platter_control;
    int remove_platter_control;
    int remove_platter_height_control;
    /*células auxiliares*/
    cell helper;
    /*pilha auxiliar para receber a pilha tirada do navio*/
    stack stack_helper;
    /**************************************/
    /*Estruturas para que são usadas na aplicação*/
    /*áreas de atracamento*/
    dock d[4];
    /*criar as pilhas das áreas de atracamento*/
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
             d[i].platter[j] = create_stack();
        }
    }
    /*carregadores*/
    carrier car[4];
    /*filas de atracamento*/
    queue q[4];
    /*criando as filas*/
    /**************************************/
    /*inicio efetivo da aplicação*/
    printf("Programa de Simulação de Funcionamento Portuário\n");
    time_t timer; //variável que guarda um tempo
    struct tm *ck;  //estrutura que guarda um tempo
    timer = time(NULL); //recebe tempo
    ck = localtime( &timer ); //seta o relogio como a hora local
    printf("Hora de Inicio: %i:%i:%i\n",ck->tm_hour,ck->tm_min,ck->tm_sec);/*mostra na tela a 
    hora, minutos e segundos*/
    for(int i = 0; i < 4; i++){
        /*criação das filas*/
        q[i] = create_queue();
    }
    /*loop que irá executar até que alguma tecla seja pressionado, função da lib keyboard.h*/
    while(!keyboard_pressed()){
        srand(time(NULL));
        /*gera um numero aleatorio para criar os barcos*/
        amount = rand() % 4;
        /*passa para a função de criação de barcos, ela retornará um vetor de barcos*/
        ship* sh = NULL;
        chronometer(2);
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
            for(int i = 0; i <= 3; i++){
                printf("-------------------------------------------\n");
                printf("Atracamento: %i\n",i);
                printf("Fila %i\n\n",i);
                show_queue(q[i]);
            }
            printf("-------------------------------------------\n");
        }
        /*caso não tiver algum barco, mostra mensagem na tela que não houveram barcos nesse momento*/
        else{
            printf("Não Houveram navios nesse período de tempo!\n");
        }
        /*agora tenho que retirar os navios da fila, atracando eles e usando a grua para retirar os
        containers do navio*/
        /*enquanto que irá rodar até que o navio termine de ser atracado*/
        remove_control = 0;
        while(remove_control != 4){
            /*verifica se a fila dos navios não está vazia*/
            if(!(verify_queue_empty(q[remove_control]))){
                /*recebe a célula que foi removida para pegar o id e as pilhas*/
                helper = misalign(q[remove_control]);
                /*insere o id do navio no arquivo*/
                save_cell_on_file(helper,remove_control);
                /*começa pelo primeiro atracamento, é necessário coloca-lo na doca*/
                /*variavel de controle das pilhas do navio sendo zerada*/
                stack_ship_control = 0;
                while(stack_ship_control != 4){
                    /*o primeiro navio da fila agora vai ser esvaziado*/
                    /*utilizarei uma pilha auxiliar para guardar cada pilha do navio*/
                    /*e nesse ponto, que precisarei de uma variavel de controle para qual pilha estou
                    acessando*/
                    stack_helper = save_on_other_stack(helper,stack_ship_control);
                    /*verifico se essa pilha não esta vazia*/
                    if(!(verify_stack_empty(stack_helper))){
                        /*a partir desse momento já tenho umas das pilhas do navio, preciso 
                        agora descarrega-las na travessa*/
                        /*a dock que vou descarregar é a mesma que trabalho com a variavel remove control
                        então posso aproveita-la para realizar isso*/
                        /*agora vem um laço que itera até o tamanho da pilha salva em stack helper*/
                        /*zera a variavel de controle da pilhas das travessas*/
                        stack_platter_control = 0;
                        /**
                         * DANDO FALHA DE SEGMENTAÇÃO BEM NESSA PARTE
                         * **/
                        for(int k = 0; k < stack_length(stack_helper); k++){
                            /*agora para inserir na pilha das travessas, preciso controlar qual pilha estou 
                            acessando e por isso precisarei de uma variavel de controle para as pilhas da
                            travessa*/
                            /*além disso preciso verificar se as travessas estão cheias, ou seja tamanho igual a
                            5*/
                            if(stack_length(d[remove_control].platter[stack_platter_control]) == 5){
                                /*incrementa o controle de travessa*/
                                stack_platter_control++;
                            }
                            printf("%i\n",stack_platter_control);
                            /*e por fim, se todas as travessas estão cheias, devo desempilha-las com o carrier*/
                            if(stack_platter_control == 5){
                                /*aqui começa o desempilhamento do carrier*/
                                /*como preciso de uma variavel que controle a pilha que o carrier trabalha*/
                                remove_platter_control = 0;
                                /*e uma que controle o indice da pilha sendo trabalhado*/
                                remove_platter_height_control = 0;
                                /*onde o laço vai executar até esvaziar todas as pilhas do carrier*/
                                while(remove_platter_control != 5){
                                    /*verifica se ainda há itens na pilha, senão forem encontrados valores pelo 
                                    indice passado por parametro, retornará -1, ou seja é hora de passar para proxima pilha
                                    */
                                    if(return_int_value_of_stack(d[remove_control].platter[stack_platter_control],remove_platter_height_control) == -1){
                                        remove_platter_control++;
                                        remove_platter_height_control = 0;
                                    }
                                    /*como o proprio laço controla se já passou pelas travessas, agora só é colocar a pilha no carrier*/
                                    car[remove_control].id_container = return_int_value_of_stack(d[remove_control].platter[stack_platter_control],remove_platter_height_control);
                                    /*tempo de trabalho do carreir*/
                                    chronometer(1);
                                    /*insere o container em uma arquivo de armazenamento de containers*/
                                    insert_container_on_file(car[remove_control].id_container);
                                    /*e ele a armazena-la*/
                                    /*ai incrementa a variavel de controle do indice da pilha das travessas*/
                                    remove_platter_height_control++;
                                }
                            }
                            /*caso já tenha passado por esses condições, ou não precisou ainda passar, insere containers na travessa*/
                            stack_up(d[remove_control].platter[stack_platter_control],return_int_value_of_stack(stack_helper,k));
                            /*e incrementa o controle da pilha da travessa, ou seja de qual pilha das travessas está sendo trabalhada*/
                        }
                        /**
                         * ATÉ AQUI, ESTÁ DANDO FALHA DE SEGMENTAÇÃO
                         * **/
                    }/*assim que foir finalizado o processo de desempilhamento ou a pilha estiver vazia*/
                    /*incrementa o variavel de controle de pilhas do navio*/
                    stack_ship_control++;
                }
            }
            /*e se já acabou de desempilhar o navio dessa fila, vai para a proxima*/
            remove_control++;
            /*quando já tiver passado pelas quatro filas, sai do laço e volta a por navios na fila*/
        }
    }
    /*no fim da aplicação, mostra o relatorio aberto no editor de texto, e mostra os navios que ainda estão na fila*/
    printf("Navios ainda na fila: \n");
    for(int i = 0; i < 4; i++){
        printf("-------------------------------------------\n");
        printf("Fila: %i\n",i);
        show_queue(q[i]);
    }
    printf("-------------------------------------------\n");
    //system("gedit report/report.txt");
    return(0);
}