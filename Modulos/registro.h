#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

//FILA
typedef struct elementob{
	int chamada;
	int destino;
}Elementob;

typedef struct node {
	Elementob dado;
	struct node* prox;
}nodetype;

typedef struct neyfila {
	nodetype *inicio;
	nodetype *final;
}tneyfila;

typedef struct resultados {
	int tDentro;
	int tFora;
	int id;
}Resul;


void criarF (tneyfila *F);
int vaziaF (tneyfila F);
int inserirF (tneyfila *F, Elementob valor);
int removerF (tneyfila *F, Elementob *valor);
int exibirF (tneyfila *F);


//LISTA
typedef struct elem{// Descreve cada componente da célula
	int chamada;
	int destino;
	int marcador;
	int elev;
	int id;
	int tDentro;
	int tFora;
}elem;

typedef struct No{ //Compõe  a lista
  struct No *anterior;
  struct No *proxima;
  elem passageiro;
}lno;

typedef struct Lista{//Serve como um observador da lista, contando tamanaho e posições
  lno *primeira;
  lno *ultima;
  int tamanho;
}tlista;

void Ordena(tlista *lista);
void inserirL(tlista *lista, elem p);
void criaListaL(tlista *lista);
int removerL(tlista *lista,elem p);
void exibirL(tlista *lista);
int listVaziaL(tlista *lista);


#endif
