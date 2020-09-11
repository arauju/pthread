#ifndef PCONTROLE_H
#define PCONTROLE_H

#include "registro.h"

typedef struct {
  tlista *L;
	int elevador;
	int capacidade;
	int andares;
} Thread_arg, *pt_thread_arg;


void pControle (tlista *L2, int capacidadeP, int andaresP, char *saida);

#endif
