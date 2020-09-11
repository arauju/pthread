#ifndef PDADOS_H
#define PDADOS_H

#include "registro.h"

typedef struct {
  tlista *L;
	int elevador;
	int capacidade;
	int andares;
  int id;
} thread_arg, *ptr_thread_arg;

void *subir (void *arg);
void pDados (tlista *L2, int capacidadeD, int andaresD, char *saida);

#endif
