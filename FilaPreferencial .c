/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <2020294>  -   Prof. Luciano Antonio Digiampietri             **/
/**                                                                 **/
/**   EP2 - Fila Preferencial                                       **/
/**                                                                 **/
/**   <Antonio garcia de souza Neto>            <11846501>          **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
  res->inicioPref = NULL;
  res->fimPref = NULL;
  res->inicioGeral = NULL;
  res->fimGeral = NULL;
  return res;
}

int tamanho(PFILA f){
  PONT atual = f->inicioGeral;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

int tamanhoFilaPreferencial(PFILA f){
  PONT atual = f->inicioPref;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

PONT buscarID(PFILA f, int id){
  PONT atual = f->inicioGeral;
   while (atual) {
    if (atual->id == id) return atual;
    atual = atual->prox;
  }
  return NULL;
}

void exibirLog(PFILA f){
  int numElementos = tamanho(f);
  printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
  PONT atual = f->inicioGeral;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n");
  numElementos = tamanhoFilaPreferencial(f);
  printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
  atual = f->inicioPref;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n\n");
}


bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial){
  bool resposta = false;
	if(id < 0 || buscarID(f, id) != NULL){
		return false;
	}
	PONT res = (PONT) malloc(sizeof(ELEMENTO));
	res->id = id;
	res->ehPreferencial = ehPreferencial;
	res->prox = NULL;
	if(tamanho(f) == 0){
		f->inicioGeral = res;
	}else{
		f->fimGeral->prox = res;
	}
	f->fimGeral = res;

	if(ehPreferencial == true){
		PONT resPref = (PONT) malloc(sizeof(ELEMENTO));
		resPref->id = id;
		resPref->ehPreferencial = ehPreferencial;
		resPref->prox = NULL;
		if(tamanhoFilaPreferencial(f) == 0){
			f->inicioPref = resPref;
		}else{
			f->fimPref->prox = resPref;
		}
		f->fimPref = resPref;
	}
  resposta = true;

  return resposta;
}



bool atenderPrimeiraDaFilaPreferencial(PFILA f, int* id){
  bool resposta = false;
	if(tamanho(f) == 0){
		return resposta;
	}
	resposta = true;
	if(tamanhoFilaPreferencial(f) == 0){
		*id = f->inicioGeral->id;
		PONT aux = f->inicioGeral;
		f->inicioGeral = aux->prox;
		PONT atual = f->inicioGeral;
		if(tamanho(f) == 0){
			f->fimGeral = NULL;
		}
		free(aux);
	}else{
		*id = f->inicioPref->id;
		PONT aux = f->inicioPref;
		f->inicioPref = aux->prox;
		PONT atual = f->inicioPref;
		if(tamanhoFilaPreferencial(f) == 0){
			f->fimPref = NULL;
		}
		free(aux);

		PONT atualGeral = f->inicioGeral;
		PONT secAux = NULL;
		if(f->inicioGeral->id == *id){
			secAux = f->inicioGeral;
			f->inicioGeral = f->inicioGeral->prox;
			if(f->fimGeral->id == *id){
				f->fimGeral = NULL;
			}
			free(secAux);
		}else{
			while (atualGeral) {
    		if(atualGeral->prox->id == *id){
					secAux = atualGeral->prox;
					atualGeral->prox = atualGeral->prox->prox;
					break;
				}
    		atualGeral = atualGeral->prox;
  		}
			free(secAux);
		}
	}
  return resposta;
}



bool atenderPrimeiraDaFilaGeral(PFILA f, int* id){
  bool resposta = false;
	if(tamanho(f) == 0){
		return resposta;
	}
	resposta = true;


	if(f->inicioGeral->ehPreferencial == true){
		PONT atualPref = f->inicioPref;
		PONT secAux = NULL;
		if(f->inicioPref->id == *id){
			secAux = f->inicioPref;
			f->inicioPref = f->inicioPref->prox;
			if(f->fimPref->id == *id){
				f->fimPref = NULL;
			}
			free(secAux);
		}else{
			while (atualPref) {
    		if(atualPref->prox->id == *id){
					secAux = atualPref->prox;
					atualPref->prox = atualPref->prox->prox;
					break;
				}
    		atualPref = atualPref->prox;
  		}
			free(secAux);
		}
	}

		*id = f->inicioGeral->id;
		PONT aux = f->inicioGeral;
		f->inicioGeral = aux->prox;
		PONT atual = f->inicioGeral;
		if(tamanho(f) == 0){
			f->fimGeral = NULL;
		}
		free(aux);

  return resposta;
}



bool desistirDaFila(PFILA f, int id){
  bool resposta = false;

  if(buscarID(f, id) == NULL) {
		return resposta;
	}
	resposta = true;
	
	PONT findId = buscarID(f, id);

	if(findId->ehPreferencial == true){
		PONT atual = f->inicioPref;
		PONT findPref = NULL;
   	while (atual) {
			if (atual->id == findId->id){
				findPref = atual;
				break;
			} 
			atual = atual->prox;
  	}
		if(f->inicioPref == findPref){
		PONT aux = f->inicioPref;
		f->inicioPref = aux->prox;
		PONT atual = f->inicioPref;
		if(tamanhoFilaPreferencial(f) == 0){
			f->fimPref = NULL;
		}
		free(aux);
	}else if(f->fimPref == findPref){
		PONT aux = f->fimPref;
		PONT atualPref = f->inicioPref;
		while (atualPref) {
    		if (atualPref->prox == f->fimPref){
					f->fimPref = atualPref;
					f->fimPref->prox = NULL;
				};
    		atualPref = atualPref->prox;
  		}
			free(aux);
	}
	}
	if(f->inicioGeral == findId){
		PONT aux = f->inicioGeral;
		f->inicioGeral = aux->prox;
		PONT atual = f->inicioGeral;
		if(tamanho(f) == 0){
			f->fimGeral = NULL;
		}
		free(aux);
	}else if(f->fimGeral == findId){
		PONT aux = f->fimGeral;
		PONT atualGeral = f->inicioGeral;
		while (atualGeral) {
    		if (atualGeral->prox == f->fimGeral){
					f->fimGeral = atualGeral;
					f->fimGeral->prox = NULL;
				};
    		atualGeral = atualGeral->prox;
  		}
			free(aux);
	}

  return resposta;
}
