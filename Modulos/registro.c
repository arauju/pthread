/*
 * JULIANA DE FÁTIMA OVÍDIO ARAÚJO
 *
 * REGISTRO.C
 *
 * TRABALHO PRÁTICO I
 *
 * CIÊNCIA DA COMPUTAÇÃO
 * ALGORITMOS E ESTRUTURAS DE DADOS III
 * 2/2016
 *
 * */

#include "registro.h"

//FILA
void criarF (tneyfila *F){
    F->inicio = F->final = NULL;
}

int vaziaF (tneyfila F){
    return (F.inicio == NULL && F.final == NULL);
}

int inserirF (tneyfila *F, Elementob valor){
	nodetype *novo;
    novo = (nodetype*) malloc(sizeof(nodetype));
    if (novo == NULL){
        return 0;
    }
    novo->dado.chamada = valor.chamada;
    novo->dado.destino = valor.destino;
    novo->prox = NULL;
    if (vaziaF(*F)){
        F->inicio = novo;
    } else
        (F->final)->prox = novo;
        F->final = novo;
        return 1;
}

int exibirF (tneyfila *F){
	if(F->inicio == NULL){
        printf("Fila vazia\n");
    }
    else {
        nodetype *aux;
        aux = F->inicio;
        printf("%d %d\n", aux->dado.chamada, aux->dado.destino);
        while (aux->prox != NULL){
          aux = aux->prox;
          printf("%d %d\n", aux->dado.chamada, aux->dado.destino);
        }
    }
}


//LISTA
void Ordena(tlista *lista){
  lno *aux, *aux2;
  elem k;
	aux = (lno*) malloc(sizeof(lno));
    aux2 = (lno*) malloc(sizeof(lno));
    for(aux = lista->primeira; aux != NULL; aux = aux->proxima){
       for(aux2 = aux->proxima; aux2 != NULL; aux2 = aux2->proxima){
           if((aux->passageiro.chamada) > (aux2->passageiro.chamada)){
                k = aux->passageiro;
                aux->passageiro = aux2->passageiro;
                aux2->passageiro = k;
           }
       }
    }
    free(aux);
    free(aux2);
}

int listVaziaL(tlista *lista){
	if(lista->tamanho == 0){
		return 1;
	 }
	 else {
		return 0;
	 }
}

void inserirL(tlista *lista, elem p){
	lno *temp = (lno*)malloc(sizeof(lno));
	temp->anterior = NULL;
	temp->proxima = NULL;
	temp->passageiro = p;
	if (listVaziaL(lista) == 1){
		lista->primeira = temp;
	}
	else {
		lista->ultima->proxima = temp;
		temp->anterior = lista->ultima;
	}
	lista->ultima = temp;
	lista->tamanho++;
}

void criaListaL(tlista *lista){
	lista->primeira = NULL;
	lista->ultima = NULL;
	lista->tamanho = 0;
}

int removerL(tlista *lista, elem p){
	if(listVaziaL(lista) == 1){
		return 1;
	}
    lno *temp = lista->primeira;
    temp = (lno*) malloc(sizeof(lno));

	if(lista->tamanho == 1){
		lista->primeira == NULL;
		lista->tamanho--;
		return 0;
	}else {
		while(temp != NULL){
			if( temp->passageiro.chamada == p.chamada && temp->passageiro.destino == p.destino){
				if(temp->proxima != NULL){
					temp->proxima->anterior = temp->anterior;
				}
				if(temp->anterior != NULL){
					temp->anterior->proxima = temp->proxima;
				}
				else {
					lista->primeira = temp->proxima;
				}
				if(temp->proxima != NULL){
					temp->proxima->anterior = temp->anterior;
				}
				else {
					lista->ultima = temp->anterior;
				}
				free(temp);
			}
			temp = temp->proxima;
		}
		lista->tamanho --;
		return 0;
	}
}

void exibirL(tlista *lista){
	if(listVaziaL(lista)){
		return;
	}
	lno *temp = lista->primeira;
	int i;
	for(i = 1; temp != NULL; i++){
		printf("%d %d %d\n",temp->passageiro.chamada,temp->passageiro.destino, temp->passageiro.marcador);
		 temp = temp->proxima;
	}
}
