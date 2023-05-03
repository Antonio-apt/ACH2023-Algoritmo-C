#include <stdlib.h>
#include <stdio.h>

#define false 0
#define true 1

typedef int bool;

typedef struct {
	int nusp;
	int nota;
	int freq;
} ALUNO;

typedef struct aux{
	ALUNO* aluno;
	struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
	PONT listaNUSP;
	PONT listaNOTA;
} TURMA;


int tamanho(TURMA* turma);
ALUNO* buscarAluno(TURMA* turma, int nusp);
bool inserirAluno(TURMA* turma, int nusp, int nota, int frequencia);
bool excluirAluno(TURMA* turma, int nusp);
void print123();
TURMA inicializaTurma();
void reinicializaTurma(TURMA* turma);
void exibirTurma(TURMA* turma);