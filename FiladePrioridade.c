/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <2020294>  -   Prof. Luciano Antonio Digiampietri             **/
/**                                                                 **/
/**   EP1 - Fila de Prioridade                                      **/
/**                                                                 **/
/**   <Antonio garcia de souza Neto>            <11846501>          **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max){
    PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
    res->maxElementos = max;
    res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
    int i;
    for (i=0;i<max;i++) res->arranjo[i] = NULL;
    PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->fila = cabeca;
    cabeca->ant = cabeca;
    cabeca->prox = cabeca;
    cabeca->id = -1;
    cabeca->prioridade = 1000000;
    return res;
}

void exibirLog(PFILA f){
    printf("Log [elementos: %i (alem do no cabeca)]\n", tamanho(f));
    PONT atual = f->fila;
    printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
    atual = atual->prox;
    while (atual != f->fila){
        printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
        atual = atual->prox;
    }
    printf("\nElementos validos: ");
    atual = atual->prox;
    while (atual != f->fila){
        printf("[%i;%f;%p] ", atual->id, atual->prioridade, atual);
        atual = atual->prox;
    }

    printf("\nValores do arrajo:\n\[ ");
    int x;
    for (x=0;x<f->maxElementos;x++) printf("%p ",f->arranjo[x]);
    printf("]\n\n");
}



int tamanho(PFILA f){
	int tam = 0;
	PONT atual = f->fila;
	atual = atual->prox;
	while(atual != f->fila){
		tam++;
		atual = atual->prox;
	}
	return tam;
}



bool inserirElemento(PFILA f, int id, float prioridade){
	bool resposta = false;
	if(id < 0 || id >= f->maxElementos) return resposta;
	if(f->arranjo[id] != NULL) return resposta;
	resposta = true;

	PONT item = (PONT) malloc(sizeof(ELEMENTO));
	item->prioridade = prioridade;
	item->id = id;


	PONT atual = f->fila;
	atual = atual->prox;

	while(item->prioridade < atual->prioridade && atual->id != -1){
		atual = atual->prox;
	}

	item->ant = atual->ant;
	item->prox = atual;
	atual->ant->prox = item;
	atual->ant = item;
	

	f->arranjo[id] = item;

	return resposta;
}



bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
	bool resposta = false;
	if(id < 0 || id >= f->maxElementos) return resposta;
	if(f->arranjo[id] == NULL) return resposta;
	if(f->arranjo[id]->prioridade >= novaPrioridade) return resposta;
	resposta = true;

	PONT atual = f->fila;
	atual = atual->prox;
	f->arranjo[id]->prioridade = novaPrioridade;

	PONT item = f->arranjo[id];
	if(item->ant->prioridade > item->prioridade) return resposta;

	while(item->prioridade > atual->prioridade && atual->id != -1){
		atual = atual->ant;
	}
	item->prox->ant = item->ant;
	item->ant->prox = item->prox;
	item->ant = atual;
	item->prox = atual->prox;
	atual->prox->ant = item;
	atual->prox = item;


	return resposta;
}



bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
	bool resposta = false;
	if(id < 0 || id >= f->maxElementos) return resposta;
	if(f->arranjo[id] == NULL) return resposta;
	if(f->arranjo[id]->prioridade <= novaPrioridade) return resposta;
	resposta = true;

	PONT item = f->arranjo[id];
	item->prioridade = novaPrioridade;
	PONT atual = item->prox;

	if(item->prox->prioridade < item->prioridade) return resposta;

	while(atual->prioridade > item->prioridade && atual->id != -1){
		atual = atual->prox;
	}
	item->prox->ant = item->ant;
	item->ant->prox = item->prox;
	item->prox = atual;
	item->ant = atual->ant;
	atual->ant->prox = item;
	atual->ant = item;


	return resposta;
}


PONT removerElemento(PFILA f){
	PONT resposta = NULL;
	if(tamanho(f) == 0) return resposta;

	resposta = f->fila->prox;
	f->fila->prox = resposta->prox;
	resposta->prox->ant = f->fila; 
	f->arranjo[resposta->id] = NULL;
	return resposta;
}



bool consultarPrioridade(PFILA f, int id, float* resposta){
	bool resp = false;
	if(id < 0 || id >= f->maxElementos) return resposta;
	if(f->arranjo[id] != NULL) return resposta;	
	
	*resposta = f->arranjo[id]->prioridade;
	resp = true;

	return resp;
}

