#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "skiplist.h"
#define SKIPLIST_NIVEL_MAXIMO 6

struct no{
	int valor;
	struct no *prox;
	struct no *desce;
};

struct lista{
	struct no **vetor;
};

Lista cria_lista(){ /*/ retorna vetor de ponteiros de tamanho SKIPLIST_NIVEL_MAXIMO, retorna NULL se falhar*/

	int j=0, i;
	No aux;
	Lista Vetorzin = (Lista) malloc(sizeof(Lista));
	Vetorzin->vetor = (No*) malloc(SKIPLIST_NIVEL_MAXIMO * sizeof(No)); /*/ cria vetor de ponteiros do tipo Lista (alocando todos os niveis de 1 vez)*/
	for(i = 0; i<SKIPLIST_NIVEL_MAXIMO; i++){
		Vetorzin->vetor[i] = (No) malloc(sizeof(No)); /*/ aloca um nó e coloca em cada posição dp vetor*/
		if(Vetorzin->vetor[i]!=NULL){ /*/ verificando se o nó foi alocado*/
			Vetorzin->vetor[i]->valor = INT_MIN; /*/ ajustando os cabeçalhos (INT_MIN = - infinito)*/
            if(i==0)
                Vetorzin->vetor[i]->desce = NULL;
            else
                Vetorzin->vetor[i]->desce=aux;
			Vetorzin->vetor[i]->prox = NULL;
            aux= Vetorzin->vetor[i];/*ajustando os campos '->desce'*/

			if(j==SKIPLIST_NIVEL_MAXIMO-1) return Vetorzin;
			j++;
		}
	}
	return NULL;
}

int lista_vazia(Lista Vetorzin){ /*/ return 1 para lista vazia e 0 para nao vazia*/
	if(Vetorzin->vetor[0]->prox == NULL||Vetorzin==NULL) return 1;
	else return 0;
}

int num_aleatorio(){ /*/ retorna 0 ou 1*/
	int x = rand()%2;
	//printf("%d",x);
	return x;
}

int busca_elem(Lista Vetorzin, int x){ /*/ retorna 1 para elemento encontrado 0 para falha*/
	int nivel_comeco = SKIPLIST_NIVEL_MAXIMO-1;

	if(lista_vazia(Vetorzin)) return 0;

	while(1){ /*/ encontra o primeiro nivel com elementos para começar a busca*/
		if(Vetorzin->vetor[nivel_comeco]->prox==NULL)
            nivel_comeco--;
		else
            break;
    }
    while(1){
        if(Vetorzin->vetor[nivel_comeco]->prox->valor>x&&x>0)
            nivel_comeco--;
        else
            break;
    }

    No aux = Vetorzin->vetor[nivel_comeco]; /*/ variavel auxiliar para percorrer a skiplist*/
    while(1){
        if(aux->prox!=NULL&&x>=aux->prox->valor){
            aux=aux->prox;
            continue;
        }
        if(aux->prox!=NULL){
             if(aux->valor==x){
                return 1;
            }else{
                if(aux->desce!=NULL){
                   // printf("desceu no end %x\n",aux->desce);
                    aux=aux->desce;
                    continue;
                }else
                    return 0;
            }
        }else
            if(aux->prox==NULL&&aux->desce!=NULL){
                //printf("desceu no end %x\n",aux->desce);
                if(aux->valor!=x)
                    aux=aux->desce;
                else if(aux->valor==x)
                    return 1;
                continue;
            }else
                return 0;

    }
}

int imprime_lista(Lista Vetorzin, int nivel){ /*/ usuario escreve qual nivel ele quer imprimir e retorna 1 se tem sucesso, retorna 0 se fracasso*/
	if(lista_vazia(Vetorzin)){
		printf("{}\n");
		return 1;
	}
    if(Vetorzin->vetor[nivel]->prox==NULL){
        printf("{}\n");
        return 1;
    }
    No aux;
	if(nivel <= SKIPLIST_NIVEL_MAXIMO-1){ /*/ verifica se o nivel existe*/
        aux = Vetorzin->vetor[nivel]->prox; /*/ variavel auxiliar para percorrer o nivel*/

		printf("{");
		while(aux->prox!=NULL){ /*/ loop para imprimir o nivel*/
			printf("%d, ", aux->valor);
			aux = aux->prox;
		}
		printf("%d}\n", aux->valor); /*/ perfumaria e imprimindo o ultimo elem do nivel*/
		return 1;
	}else return 0;
}

int tamanho_lista(Lista Vetorzin){
	if(lista_vazia(Vetorzin)){
		printf("Tamnho lista: 0");
		return 1;
	}

	int tamanho_max = 0;
	int tamanho_por_nivel = 0;
	int nivel_comeco = SKIPLIST_NIVEL_MAXIMO-1;

	while(1){
		if(Vetorzin->vetor[nivel_comeco]->prox==NULL) nivel_comeco--;
		else break;
	}

	while(1){
		No aux = Vetorzin->vetor[nivel_comeco]->prox;
		while(aux->prox!=NULL){
			tamanho_por_nivel++;
			aux = aux->prox;
		}
		tamanho_por_nivel++;
		printf("Tamanho do nivel[%d]: %d\n", nivel_comeco, tamanho_por_nivel);
		tamanho_max = tamanho_max+tamanho_por_nivel;
		tamanho_por_nivel = 0;
		nivel_comeco--;
		if(nivel_comeco==-1){
			printf("Tamanho lista total: %d", tamanho_max);
			return 1;
		}
		continue;
	}
}

void libera_lista(Lista Vetorzin){

     if(lista_vazia(Vetorzin)){
        printf("ERRO tamanho lista: 0");
        return;
     }

     int nivel_comeco = SKIPLIST_NIVEL_MAXIMO-1;
     while(1){/*//acha primeiro nivel com elementos começando por cima*/
        if(Vetorzin->vetor[nivel_comeco]->prox==NULL)
                nivel_comeco--;
        else
            break;
     }
     while(1){/*//loop que percorre os niveis*/
        No aux=Vetorzin->vetor[nivel_comeco]->prox;/*//duas variaveis auxiliares para percorrer o nivel*/
        No aux2=Vetorzin->vetor[nivel_comeco]->prox->prox;
        while(aux2!=NULL){/*//loop que libera os elementos do nivel*/
            free(aux);
            aux=aux2;
            aux2=aux2->prox;
        }
        free(aux);/*//remove ultimo elem do nivel*/
        nivel_comeco--;
        if(nivel_comeco==-1){
            break;
        }
     }
        int i;
     for(i=0;i<SKIPLIST_NIVEL_MAXIMO;i++){
        free(Vetorzin->vetor[i]);/*//libera nós com menos infinito dentro*/
     }
     free(Vetorzin);/*//libera ponteiro Lista*/
     return;
}

int remove_elem(Lista Vetorzin,int x){

    if(lista_vazia(Vetorzin)){
        printf("Tamanho lista: 0");
        return 1;
    }

    int nivel_comeco = SKIPLIST_NIVEL_MAXIMO-1;

    while(1){/*//encontra o primeiro nivel com elementos para começar a busca*/
        if(Vetorzin->vetor[nivel_comeco]->prox!=NULL)
            nivel_comeco--;
        else{
            No aux=Vetorzin->vetor[nivel_comeco]->prox;/*//variavel auxiliar para percorrer a skiplist*/
            while(1){
            if(nivel_comeco==-1)/*//elemento foi removido ou nao existe na lista*/
                return 1;
            if(aux->prox!=NULL&&aux->prox->valor<x)/*//enquanto tiver elementos no mesmo nivel percorre a lista quando puder*/
                aux=aux->prox;
            else if(aux->prox->valor>=x||(aux->prox==NULL&&aux->desce!=NULL)){/*//se o proximo valor for igual ou maior ou prox =NULL e desce diferente de NULL entre no if*/
                    if(aux->prox->valor==x){/*//encontrou elemento*/
                        No aux2=aux->prox;/*//elem salvado no aux2*/
                        aux->prox=aux->prox->prox;/*//ajustando o ponteiro aux->prox*/
                        free(aux2);
                        nivel_comeco--;
                        aux=Vetorzin->vetor[nivel_comeco]->prox;/*//percorrendo cada nivel e removendo*/
                        continue;
                    }
                    aux=aux->desce;
                    continue;
                 }else
                      return 1;

            }

        }

    }

}

int insere_elem(Lista Vetorzin, int x){

    int nivel;
    No aux2;
    No aux;/*declarando fora para garantir o scopo*/

    for(nivel=0;nivel<SKIPLIST_NIVEL_MAXIMO;nivel++){
        No novo=(No)malloc(sizeof(struct no));
        if(novo==NULL)
            return 0;
        if(nivel==0)
            novo->desce=NULL;
        novo->prox=NULL;
        novo->valor=x;
        if(nivel>0){
            aux2=aux->prox;/*salva ultima endereço do ultimo elem inserido*/
        }
         aux=Vetorzin->vetor[nivel];

        while(aux->prox!=NULL&&aux->prox->valor<x)/*encontrando a posição na lista*/
            aux=aux->prox;
        if(aux->prox==NULL){/*parou pq a lista chegou no fim*/

            aux->prox=novo;

            if(nivel>0)/*se nivel eh maior que 0 entao ele teve que inserir acima*/
                aux->prox->desce=aux2;

            if(num_aleatorio())/*decide se vai pro andar de cima*/
               continue;/*vai para proxima iteração do for */
            else
                return 1;
        }else{
            novo->prox=aux->prox;/*inserindo no meio de dois elems*/
            aux->prox=novo;

            if(nivel>0)
                aux->prox->desce=aux2;

            if(num_aleatorio())/*decide se vai pro proximo andar*/
                continue;
            else
                return 1;
        }
    }
    return 1;
}


int remove_lista(Lista Vetorzin, int x){
    int nivel = SKIPLIST_NIVEL_MAXIMO-1;

    // Se lista estiver vazia, remoção falha
    if(lista_vazia(Vetorzin))
        return 0;

    // encontra o primeiro nível com elementos
    while(Vetorzin->vetor[nivel]->prox==NULL){
        nivel--;
    }

    No aux = Vetorzin->vetor[nivel];
    // do primeiro nível com elementos, verifica se possui o elemento
    while(aux->prox->valor < x){
        aux = aux->prox;
        if(aux->prox==NULL){
            nivel--;
            aux = Vetorzin->vetor[nivel];
        }
    }

    // variavel auxiliar para percorrer skiplist
    No aux2;

    // percorre os niveis para remover o elemento em todos
    while(nivel >= 0){
        aux = Vetorzin->vetor[nivel];

        // procura o elemento na lista
        while(aux->prox != NULL && aux->prox->valor < x){
            aux = aux->prox;
        }
        // encontrou o elemento, arruma ponteiros e libera no
        if(aux->prox->valor==x){
           aux2 = aux->prox;
           aux->prox = aux2->prox;
           free(aux2);
        }

        nivel--;
    }

    return 1;
}
