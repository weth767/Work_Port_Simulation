#ifndef STACK_H
#define STACK_H
/*biblioteca para a simulação do tipo booleano*/
#include "bool.h"

/*ponteiro de estrutura para permitir a criação de variaveis com o tipo pilha*/
typedef struct STACK *stack;
/*ponteiro de estrutura para permitir a criação de variaveis com o tipo celula*/
typedef struct CELLULE *cellule;

/*cabeçalhos das funções da pilha*/
/*função que retorna a alocação de memória para a pilha, para que ela possa ser trabalhada*/
/*função que aloca memória para a estrutura de pilha, antes de se trabalhar com a pilha deve obrigatoriamente
atribuir essa função a uma variável do tipo pilha*/
stack create_stack();

/*função que inicia a pilha vazia, colocando seu topo como null e seu tamanho com 0*/
/*deve iniciar a pilha vazia para garantir seu total funcionamento*/
/*deve receber por parametro um variavel do tipo pilha*/
void stack_start_empty(stack);

/*função para verificar se a pilha está vazia, verificando se o topo esta apontando para null
e o tamanho é igual a 0*/
/*deve receber por parametro obrigatoriamente um variavel do tipo pilha*/
bool verify_stack_empty(stack);

/*funçao para empilhar, recebe a pilha e um valor que será empilhada dinamicamente*/
/*deve receber por parametro obrigatoriamente um variavel do tipo pilha e uma variavel do tipo int*/
void stack_up(stack,int value);

/*função para desempilhar, recebe a pilha e retorna a celula desempilhada*/
/*deve receber por parametro obrigatoriamente um variavel do tipo pilha*/
cellule unstack(stack);

/*função para desmontar a pilha, ou seja desaloca-la totalmente da memoria*/
/*deve receber por parametro obrigatoriamente um variavel do tipo pilha*/
void drop_stack(stack);

/*função que retorna o tamanho da pilha*/
/*deve receber por parametro obrigatoriamente um variavel do tipo pilha*/
int stack_length(stack);

/*função que busca um elemento na pilha e retorna seu indice na pilha*/
/*deve obrigatoriamente um variavel do tipo pilha e uma variavel do tipo int*/
int search_value_on_stack(stack,int value);

/*função para mostrar os elementos que estão na pilha*/
/*deve receber por parametro obrigatoriamente um variavel do tipo pilha */
void show_stack(stack);

/*função para retornar o valor int para ser usado*/
int return_int_value_of_stack_cell(cellule);
/*função para retornar o valor int da propria pilha*/
int return_int_value_of_stack(stack,int);

#endif