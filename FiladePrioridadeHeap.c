/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <Turma94> - Prof. Luciano Antonio Digiampietri                **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   <Antonio Garcia de Souza Neto>            <11846501>          **/
/**                                                                 **/
/*********************************************************************/

#include "turma.h"
#include <math.h>

PFILA criarFila(int max)
{
    PFILA res = (PFILA)malloc(sizeof(FILADEPRIORIDADE));
    res->maxElementos = max;
    res->arranjo = (PONT *)malloc(sizeof(PONT) * max);
    res->heap = (PONT *)malloc(sizeof(PONT) * max);
    int i;
    for (i = 0; i < max; i++)
    {
        res->arranjo[i] = NULL;
        res->heap[i] = NULL;
    }
    res->elementosNoHeap = 0;
    return res;
}

void exibirLog(PFILA f)
{
    printf("Log [elementos: %i]\n", f->elementosNoHeap);
    PONT atual;
    int i;
    for (i = 0; i < f->elementosNoHeap; i++)
    {
        atual = f->heap[i];
        printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
    }
    printf("\n\n");
}

int tamanho(PFILA f)
{
    int tam = 0;

    for (int i = 0; i < f->maxElementos; i++)
    {
        if (f->heap[i] != NULL)
            tam++;
    }

    return tam;
}

bool verificarElemento(PFILA f, int id, bool existe)
{
    if (existe)
    {
        return (id < 0 || f->arranjo[id] != NULL || id >= f->maxElementos);
    }
    else
    {
        return (id < 0 || f->arranjo[id] == NULL || id >= f->maxElementos);
    }
}

void organizarPosicao(PFILA f, int index)
{
    int filhoEsquerda = (int)floor((2 * index) + 1);
    int filhoDireita = (int)floor((2 * index) + 2);
    PONT item = f->heap[index];

    if (f->heap[filhoDireita] != NULL && f->heap[filhoDireita]->prioridade > item->prioridade)
    {
        f->heap[index] = f->heap[filhoDireita];
        f->heap[filhoDireita] = item;
        f->heap[index]->posicao = index;
        f->heap[filhoDireita]->posicao = filhoDireita;

        organizarPosicao(f, filhoDireita);
    }
    if (f->heap[filhoEsquerda] != NULL && f->heap[filhoEsquerda]->prioridade > item->prioridade && index != 0)
    {
        f->heap[index] = f->heap[filhoEsquerda];
        f->heap[filhoEsquerda] = item;
        f->heap[index]->posicao = index;
        f->heap[filhoEsquerda]->posicao = filhoEsquerda;

        organizarPosicao(f, filhoEsquerda);
    }
}

bool inserirElemento(PFILA f, int id, float prioridade)
{
    bool res = false;
    if (verificarElemento(f, id, true))
        return res;
    PONT novo = malloc(sizeof(PONT));
    novo->prioridade = prioridade;
    novo->posicao = 0;
    novo->id = id;
    f->arranjo[id] = novo;
    res = true;

    if (f->elementosNoHeap == 0)
    {
        f->elementosNoHeap = f->elementosNoHeap + 1;
        f->heap[0] = novo;
        return res;
    }
    int index = f->elementosNoHeap;
    int indexPai = 0;

    if (!((index - 1) < 0))
    {
        indexPai = (int)floor((index - 1) / 2);
    }
    f->heap[index] = novo;

    while (f->heap[indexPai]->prioridade < novo->prioridade)
    {
        f->heap[index] = f->heap[indexPai];
        f->heap[indexPai] = novo;
        f->heap[index]->posicao = index;
        f->heap[indexPai]->posicao = indexPai;

        index = indexPai;
        indexPai = (int)floor((index - 1) / 2);
    }

    f->heap[index]->posicao = index;
    f->heap[indexPai]->posicao = indexPai;
    f->elementosNoHeap = f->elementosNoHeap + 1;

    return res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
    bool res = false;
    if (verificarElemento(f, id, false) || f->arranjo[id]->prioridade >= novaPrioridade)
        return res;
    PONT item = f->arranjo[id];
    item->prioridade = novaPrioridade;
    int index = item->posicao;
    int indexPai = 0;
    res = true;

    if (!((index - 1) < 0))
    {
        indexPai = (int)floor((index - 1) / 2);
    }

    while (f->heap[indexPai]->prioridade < item->prioridade)
    {
        f->heap[index] = f->heap[indexPai];
        f->heap[indexPai] = item;
        f->heap[index]->posicao = index;
        f->heap[indexPai]->posicao = indexPai;

        index = indexPai;
        indexPai = (int)floor((index - 1) / 2);
    }

    return res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
    bool res = false;
    if (verificarElemento(f, id, false) || f->arranjo[id]->prioridade <= novaPrioridade)
        return res;
    f->arranjo[id]->prioridade = novaPrioridade;
    organizarPosicao(f, f->arranjo[id]->posicao);
    return res = true;
}

PONT removerElemento(PFILA f)
{
    PONT res = NULL;
    if (tamanho(f) == 0)
        return res;
    PONT removido = f->heap[0];
    f->heap[0] = f->heap[f->elementosNoHeap - 1];
    f->heap[f->elementosNoHeap - 1] = NULL;

    organizarPosicao(f, 0);

    f->elementosNoHeap = f->elementosNoHeap - 1;
    f->arranjo[removido->id] = NULL;
    res = removido;
    return res;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{
    bool res = false;
    if (verificarElemento(f, id, false))
        return res;
    *resposta = f->arranjo[id]->prioridade;
    res = true;
    return res;
}