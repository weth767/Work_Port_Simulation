#ifndef QUEUE_H
#define QUEUE_H
/*biblioteca para a simulação do tipo booleano*/
#include "bool.h"
#include "stack.h"

/*ponteiro para a estrutura que representa a fila*/
typedef struct QUEUE * queue;
/*ponteiro para a estrutura da célula da fila*/
typedef struct CELL * cell;
/*funções referentes a fila*/

/*função para criar a fila, retornando a alocação da estrutura da fila*/
/*essa função não precisa de parametros, entretanto uma fila deve ser obrigatoriamente 
iniciada por essa função, para que seja asegurado seu funcionamento*/
queue create_queue();

/*função para inicia a fila vazia, garantirá a não presença de lixo na fila, é muito importate usar essa função
quando for querer esvaziar a fila(não limpa a memória, pra isso há a função drop_queue)*/
/*deve obrigatoriamente receber uma variavel do tipo fila por parametro*/
void queue_start_empty(queue);

/*função para verificar se a fila está vazia, retorna true caso o tamanho e o inicio e fim estejam apontados para NULL*/
/*deve obrigatoriamente receber por parametro uma variavel do tipo fila*/
bool verify_queue_empty(queue);

/*função para enfileirar os elementos na fila, deve obrigatoriamente receber por parametro uma variavel do tipo fila
e o elemento 'x' que será inserido na fila e as pilhas, não retorna nada ao usuário*/
void line_up(queue,int value,stack st[]);

/*função para desenfileirar elementos da fila, deve obrigatoriamente receber por parametro uma variavel do tipo fila*/
/*retornará como parametro o ponteiro para a célula desenfileirada*/
cell misalign(queue);

/*função para desmontar toda a fila, desaloca todas as células presentes e por fim desaloca a própria estrutura de fila*/
/*deve obrigatoriamente receber por parametro uma variavel do tipo fila*/
void drop_queue(queue);

/*função para retornar o tamanho da fila, simplesmente retorna o valor do inteiro que controla o tamanho da fila*/
/*deve obrigatoriamente receber por parametro uma variavel do tipo fila*/
int queue_length(queue);

/*função para buscar um determinado valor na fila, procura o id, se encontrar retorna a celula desse id
/*deve obrigatoriamente receber por parametro uma variavel do tipo fila e o valor int a ser buscado*/
cell search_value_on_queue(queue,int);

/*função para mostrar os elementos presentes na fila, deve receber por parametro obrigatoriamente
uma variavel do tipo fila*/
void show_queue(queue);

/*função para passar os valores da célula para outras variaveis*/
int save_on_other_local(cell);
/*função para retornar um pilha*/
stack save_on_other_stack(cell,int index);

#endif