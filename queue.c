#include "queue.h"
#include "bool.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

/*struct CELL, estrutura que representa as células da fila, tem um ponteiro para seu próximo similar e para um anterior,
realizando a ponte entre as próprias células. Cada célula guarda um valor inteiro(atualmente, pode haver mudanças conforme
necessidade futura).*/
struct CELL{
    unsigned int id;//identificação de cada barco
    stack st[4];//pilha de containers do barco
    cell next;//proximo
    cell previous;//anterior
};
/*struct QUEUE, estrutura que representa a própria fila, tem ponteiros do tipo célula para seu primeiro e seu ultimo,
os outros elementos as proprias células cuidam dessa conexão, além de uma variavel do tipo int para guardar seu tamanho*/
struct QUEUE{
    cell first;
    cell last;
    int length;
};
/*agora as funcionalidades da fila*/

/*função para iniciar a fila vazia*/
void queue_start_empty(queue q){
    /*inicia o primeiro e ultimo elementos apontados para null*/
    q->first = NULL;
    q->last = NULL;
    /*e seu tamanho como 0*/
    q->length = 0;
}
/*função para criar a fila*/
queue create_queue(){
    /*aloca memória para a estrutura de fila*/
    queue q = (queue)malloc(sizeof(struct QUEUE));
    /*inicia a fila vazia*/
    queue_start_empty(q);
    /*retorna seu ponteiro*/
    return(q);
}
/*função para verificar se a fila está vazia*/
bool verify_queue_empty(queue q){
    /*verifica se a fila está vazia*/
    /*verificando se o primeiro e o ultimo estão apontados para null*/
    /*e se o tamanho está igual a 0*/
    if(q->first == NULL && q->last == NULL && q->length == 0){
        /*se as condições forem compridas retorna true*/
        return(true);
    }
    /*senão retorna false*/
    else{
        return(false);
    }
}
/*função para enfileirar os elementos*/
void line_up(queue q,int value,stack st[]){
    /*cria uma célula para ser inserida na fila*/
    cell c = (cell)malloc(sizeof(struct CELL));
    /*cria uma auxiliar do tipo célula*/
    cell helper;
    /*atribui o valor na célula*/
    c->id = value;
    for(int i = 0; i < 4; i++){
        c->st[i] = st[i];
    }
    /*se a fila estiver vazia, é a primeira inserção, então não há preocupação com as ligações*/
    /*com o proximo e anterior*/
    if(verify_queue_empty(q)){
        c->previous = NULL;
        c->next = NULL;
        q->first = c;
        q->last = c;
    }
    /*já senão estiver, quer dizer que já tem elementos nela e então deve-se fazer as ligações*/
    /*de anterior e proximo*/
    else{
        /*faz o ultimo atual apontar para a proxima célula*/
        q->last->next = c;
        /*guarda esse ultimo com um auxiliar*/
        helper = q->last;
        /*faz o ultimo receber a nova célula, ou seja, há um novo ultimo*/
        q->last = c;
        /*agora com o ultimo sendo a célula nova, o anterior dessa célula apontará
        para o seu anterior que está guardado no helper*/
        q->last->previous = helper;
        /*e seu próximo será null*/
        q->last->next = NULL;
    }
    /*aumenta o tamanho da fila*/
    q->length++;
}
/*função para remover um elemento da fila, lembrando que na fila
a remoção sempre acontece no primeiro elemento*/
cell misalign(queue q){
    /*cria-se um auxiliar para guardar o valor do primeiro
    para poder retorna-lo*/
    cell helper = NULL;
    /*verifica se a lista não está vazia para poder retirar*/
    if(!(verify_queue_empty(q))){
        /*guarda o primeiro*/
        helper = q->first;
        /*verifica se a fila tem tamanho 1, nesse caso o primeiro e ultimo só apontam
        para nada/null*/
        if(q->length == 1){
            /*faz os dois apontar para null*/
            q->first = NULL;
            q->last = NULL;
        }
        /*se for diferente de 1*/
        else{
            /*faz o primeiro deslocar para o proximo elemento*/
            /*retirando o antigo primeiro da fila*/
            q->first = q->first->next;
        }
        /*diminui o tamanho da lista*/
        q->length--;
    }
    /*e retorna a célula removida*/
    return(helper);
}
/*função para desmontar a fila*/
void drop_queue(queue q){
    /*variavel auxiliar para a célula retirada em cada iteração*/
    cell helper;
    /*laço que itera o tamanho da fila*/
    for(int i = 0; i < q->length; i++){
        /*auxiliar recebe a célula removida*/
        helper = misalign(q);
        /*libera o espaço de memória dela*/
        free(helper);
    }
    /*por garantia coloca os ponteiros da fila como null*/
    queue_start_empty(q);
    /*por fim libera o espaço da estrutura da fila*/
    free(q);
}
/*função para retornar o tamanho da fila*/
int queue_length(queue q){
    /*retorna o tamanho da fila atraves do acesso direto com o ponteiro*/
    return(q->length);
}
/*função para procurar um elemento na fila*/
/*retorna o indice dele ou -1 em caso de erro*/
cell search_value_on_queue(queue q,int id){
    /*auxiliar do tipo célula para transitar entre as posições da fila*/
    cell helper;
    /*faz com que ele recebe a primeira posição*/
    helper = q->first;
    /*laço que itera do inicio ao fim da lista*/
    for(int i = 0; i < q->length; i++){
        /*verifica se o valor da posição atual é o mesmo que foi passado por parametro*/
        if(helper->id == id){
            /*se for, index recebe o i do da iteração*/
            return(helper);
        }
        /*pula para proxima célula*/
        helper = helper->next;
    }
    /*retorna o index*/
    return(NULL);
}

/*função para mostrar os elementos presentes na fila*/
void show_queue(queue q){
    cell helper;
    /*verifica se a fila está vazia*/
    if(verify_queue_empty(q)){
        /*mostra mensagem de erro em caso verdadeiro*/
        printf("This queue is empty. There is no item!\n");
    }
    /*senão estiver vazia*/
    else{
        /*o auxiliar recebe o primeiro elemento da fila*/
        helper = q->first;
        /*laço que roda de 0 até o tamanho da fila - 1*/
        for(int i = 0; i < q->length; i++){
            /*mostra o elemento*/
            printf("--------------------------\n");
            printf("Navio: %i\n\n",helper->id);
            for(int j = 0; j < 4; j++){
                printf("Pilha: %i: ",j);
                show_stack(helper->st[j]);
                printf("\n");
            }
            printf("\n");
            /*depois vai para seu próximo*/
            helper = helper->next;
        }
    }
}
/*função para salvar valores da célula numa variavel int*/
int save_on_other_local(cell c){
    /*return o id da célula*/
    return(c->id);
}
/*função para salvar em outra pilha, os valores pegos pela célula*/
stack save_on_other_stack(cell c,int index){
    /*return a pilha de acordo com o index*/
    return(c->st[index]);
}

/*função de montar o relatorio*/
/*recebe a celula e seu atracamento*/
void save_cell_on_file(cell c, int dock){
    FILE *arquivo;
    /*abre o arquivo de relatorios*/
    arquivo = fopen("report/report.txt","a+"); 
    /*verifica se o ponteiro recebeu o arquivo*/
    if(arquivo != NULL){
        /*verifica a nulidade de dados no arquivos*/
        if(feof(arquivo) != 0){
            /*para escrever o título*/
            fprintf(arquivo,"Relatório Portuário \n\n");
        }
        /*salva os dados normalmente*/
        fprintf(arquivo,"\nAtracamento: %i / Navio: %i\n",dock,c->id);
        for(int i = 0; i < 4; i++){
            fprintf(arquivo,"Pilha %i\n",i);
            for(int j = 0; j < stack_length(c->st[i]);j++){
                if(return_int_value_of_stack(c->st[i],j) != -1){
                    fprintf(arquivo,"Container: %i\n",return_int_value_of_stack(c->st[i],j));
                }
            }
            fprintf(arquivo,"\n");
        }
    }
}