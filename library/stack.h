#ifndef STACK_H
#define STACK_H

#include "bool.h"

/*Estes ponteiros servirão para que o usuário consiga criar o tipo, entretanto se necessáriamente ver o que acontece na biblioteca,
tendo acesso apenas a esse arquivo.h
Um deles seria o alocador de memória para a criação das células da pilha*/
/*o outro a própria pilha*/
typedef struct STACK *stack;
typedef struct CELL *cell;
/*cabeçalhos das funções da pilha*/
/*função que retorna a alocação de memória para a pilha, para que ela possa ser trabalhada*/
stack create_stack();
/*função que coloca a posição do primeiro, último em null e tamanho igual a 0, para indicar pilha vazia*/
void stack_start_empty(stack);
/*função para verificar se a pilha está vazia, verificando se o primeiro e o ultimo estão apontando para null
e o tamanho é igual a 0*/
bool verify_stack_empty(stack);
/*funçao para empilhar, recebe a pilha e um valor que será empilhada dinamicamente*/
void stack_up(stack,int value);
/*função para desempilhar, recebe a pilha e retorna a celula desempilhada*/
cell unstack(stack);
/*função para desmontar a pilha, ou seja desaloca-la totalmente da memoria*/
void drop_stack(stack);
/*função que retorna o tamanho da pilha*/
int stack_length(stack);
/*função que busca um elemento na pilha e retorna seu indice na pilha, recebe a pilha e o valor*/
int search_value_on_stack(stack,int value);
/*função para mostrar os elementos que estão na pilha*/
void show_stack(stack);



#endif