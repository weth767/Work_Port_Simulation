#include "stack.h"
#include "bool.h"
#include <stdlib.h>
#include <stdio.h>

/*struct cellule, representa a célula da pilha, tem um ponteiro para seu próximo similar e para um anterior,
realizando a ponte entre as próprias células. Cada célula guarda um valor inteiro(atualmente, pode haver mudanças conforme
necessidade futura).*/
struct CELLULE{
    int value;
    cellule next;
    cellule previous;
};
/*struct stack, é a própria pilha, tem ponteiros dos tipo célula para guardar o prímeiro e o ultimo, sendo que o resto
, as próprias células cuidam. Além disso tem um váriavel int, para guardar seu tamanho*/
struct STACK{
    cellule top;
    int length;
};
/*Agora abaixo as funções referentes a pilha*/
/*função para iniciar a pilha vazia, colocando o top como null*/
void stack_start_empty(stack st){
    /*coloca o top como null, indicando que a pilha está vazia*/
    st->top = NULL;
    st->length = 0;
}
/*função para criar a pilha, retorna um ponteiro com a alocação da pilha*/
stack create_stack(){
    /*aloca memória para essa pilha*/
    stack st = (stack)malloc(sizeof(struct STACK));
    /*inicia a pilha vazia*/
    stack_start_empty(st);
    /*retorna seu ponteiro*/
    return(st);
}
/*função para verificar se a pilha está vazia, retornando true se o top for igual a null
e o tamanho for igual a 0*/
bool verify_stack_empty(stack st){
    /*verifica então as condições de nulidade da pilha*/
    /*se forem compridas, retorna true*/
    if(st->top == NULL && st->length == 0){
        return(true);
    }
    /*senao forem compridas, retorna false*/
    else{
        return(false);
    }
}
/*função para empilhar itens na pilha, no parametro, está a pilha, e o elemento a ser empilhado*/
void stack_up(stack st,int value){
    /*cria uma célula para ser colocada na pilha*/
    cellule c = (cellule)malloc(sizeof(struct CELLULE));
    /*cria uma auxiliar do tipo célula*/
    cellule helper;
    /*atribui o valor na célula*/
    c->value = value;
    /*se a pilha estiver vazia, quer dizer que é o primeiro elemento a ser empilhando
    então não tem anterior nem próximo*/
    if(verify_stack_empty(st)){
        c->previous = NULL;
        c->next = NULL;
    }
    /*já se a pilha não estiver vazia, o elemento que é o top agora, linka com esse elemento o top atual linka como proximo o elemento que será inserido
    */
    else{
        /*o próximo do topo atual, aponta pra próxima célula*/
        st->top->next = c;
        /*e o anterior da célula aponta para o topo atual*/
        c->previous = st->top;
        /*e como o que foi inserido agora é o ultimo, ele apontará para null no seu proximo*/
        c->next = NULL;
    }
    /*em seguida o topo é atualizado*/
    st->top = c;
    /*e o tamanho também*/
    st->length++;
}
/*função para desempilhar itens da pilha, passando apenas a pilha como parametro*/
cellule unstack(stack st){
    cellule helper = NULL;
    /*verifica inicialmente se a pilha não está vazia, para poder desempilhar*/
    if(!verify_stack_empty(st)){
        /*guarda o valor do topo atual*/
        helper = st->top;
        /*faz com que o topo aponta para o elemento de trás*/
        if(st->length == 1){
            st->top = NULL;
        }else{
            st->top = st->top->previous;
            /*e faz o próximo do novo topo ser null*/
            st->top->next = NULL;
        }
        st->length--;
    }
    /*retorna a célula deslocada da pilha*/
    return(helper);
    /*essa função exige muito cuidado, pois como ela retorna a alocação da célula, quem a manipula deve usar o valor e depois
    desalocar esse ponteiro, para que não fica espaço solto alocado na memória*/
}
/*função para desmontar a pilha, que recebe a pilha como parametro*/
void drop_stack(stack st){
    /*um contador, que vai incrementar para comparar com a quantidade de elementos na pilha*/
    int count = 0;
    /*um auxiliar que vai guardar a célula para desaloca-la da memória*/
    cellule helper;
    /*um laço enquanto que vai rodar até que o count seja igual ao tamanho da pilha*/
    while(count != st->length){
        /*o helper guarda o ponteiro da célula*/
        helper = unstack(st);
        /*libera esse espaço de memória*/
        free(helper);
        /*incrementa o count*/
        count++;
    }
    /*esvazia literalmente a pilha novamente por garantia*/
    stack_start_empty(st);
    /*por fim depois de ter liberados todas as células*/
    /*libera a propria estrutura de pilha*/
    free(st);
}
/*função para retornar um int que representa o tamanho da pilha*/
int stack_length(stack st){
    return(st->length);
}
/*função que busca um elemento na pilha e retorna seu indice na pilha, recebe a pilha e o valor*/
int search_value_on_stack(stack st,int value){
    /*duas variáveis inteiras, uma para controlar o laço*/
    int count = 0;
    /*e outra para fazer o controle do indice*/
    int control = (st->length - 1);
    /*e um auxiliar para acessar os valores*/
    cellule helper = st->top;
    /*um laço que irá executar até que o count seja igual ao tamanho da pilha*/
    while(count != st->length){
        /*se o valor no auxiliar for igual ao passado pelo parametro*/
        if(helper->value == value){
            /*retorna o indice*/
            return(control);
        }
        /*senão encontrou*/
        /*atualiza o indice de busca do auxiliar*/
        helper = helper->previous;
        /*decrementa o controle em 1*/
        control--;
        /*e incrementa o contador*/
        count++;
    }
    /*senão encontrar retorna o erro, -1, indicando que o elemento não está na pilha*/
    return(-1);
}
/*função para mostrar os elementos que estão na pilha*/
void show_stack(stack st){
    /*verifica se a pilha está vazia*/
    if(st->length == 0 && st->top == NULL){
        /*mostra mensagem de erro em caso verdadeiro*/
        printf("\nStack is empty. There is no item!\n");
    }
    /*senão estiver vazia, continua para a parte de leitura dos dados na pilha*/
    else{
        /*um array para guardar os dados, de forma que fiquem em ordem*/
        int help_array[st->length];
        /*auxiliar para guardar as células que já foram */
        cellule helper = st->top;
        /*a variavel count, faz o controle do laço*/
        int count = 0;
        /*já a control faz o posicionamento no array*/
        int control = st->length - 1;
        /*laço que executa até que count seja igual ao tamanho do vetor*/
        while(count != st->length){
            /*posiconado o value no auxiliar dentro do vetor, invertendo a ordem*/
            help_array[control] = helper->value;
            /*salta de célula*/
            helper = helper->previous;
            /*incrementa o count*/
            count++; 
            /*e decrementa o control, já que ele está invertendo*/
            control--;
        }
        /*for pra mostrar o vetor*/
        for(int i = 0; i < st->length; i++){
            printf("%i ",help_array[i]);
        }
    }
}
/*função para retornar um valor inteiro da celula para ser utilizado*/
int return_int_value_of_stack_cell(cellule c){
    /*retorna o valor int*/
    return(c->value);
}
/*função para retornar um valor inteiro da pilha para ser utilizado*/
int return_int_value_of_stack(stack st,int index){
    cellule helper = st->top;
    int count = 0;
    if(!(verify_stack_empty(st))){
        while(helper->previous != NULL){
            if(count == index){
                return(helper->value);
            }
            else{
                count++;
                helper = helper->previous;
            }
        }
    }
    /*erro*/
    return(-1);
}
