/*
 * JULIANA DE FÁTIMA OVÍDIO ARAÚJO
 *
 * MAIN.C
 *
 * TRABALHO PRÁTICO IV
 *
 * CIÊNCIA DA COMPUTAÇÃO
 * ALGORITMOS E ESTRUTURAS DE DADOS III
 * 2/2016
 *
 * */

#include "registro.h"
#include "pControle.h"
#include "pDados.h"
#include "tempo.h"

int main(int argc, char const *argv[]) {
	FILE *entradaD, *ambienteD, *entradaC, *ambienteC;
  entradaD = fopen(argv[1], "r");
	ambienteD = fopen (argv[2], "r");
	entradaC = fopen(argv[3], "r");
	ambienteC = fopen (argv[4], "r");
	char* saida = argv[5];

	// guarda quantos elementos estão inseridos na fila
	int qtd = 0, a;
	int capacidadeD, andaresD, capacidadeC, andaresC;
	elem l;

	//Variaveis para calcular tempo
	double tempoU,tempoS;
	struct rusage resources;
	struct timeval inicioU, inicioS, fimU, fimS;

	Tempo t;
	Elementob v;
	tlista *L1, *L2;

	L1 = (tlista*) malloc(sizeof(tlista));
	L2 = (tlista*) malloc(sizeof(tlista));
	criaListaL(L1);
	criaListaL(L2);

	//lendo o arquivo de DADOS  e adicionando os numeros na lista
	while (fscanf(entradaD, "%d", &l.chamada) && fscanf(entradaD, "%d", &l.destino) != EOF){
	  l.marcador = 0;
	  l.tDentro = 0;
	  l.tFora = 0;
	  inserirL(L1,l);
	  qtd++;
	}
	qtd = 0;

	//lendo o arquivo de CONTROLE e adicionando os numeros na lista
	while (fscanf(entradaC, "%d", &l.chamada) && fscanf(entradaC, "%d", &l.destino) != EOF){
		l.marcador = 0;
		l.tDentro = 0;
		l.tFora = 0;
		inserirL(L2,l);
		qtd++;
	}

	//ambiente do elevador
	fscanf(ambienteD, "%d", &capacidadeD), fscanf (ambienteD, "%d", &andaresD);
	fscanf(ambienteC, "%d", &capacidadeC), fscanf (ambienteC, "%d", &andaresC);

  /*		PARALELISMO DE DADOS		*/
	iniciaTempo(&t);
	Ordena (L1);
  pDados (L1, capacidadeD, andaresD, saida);
	finalizaTempo(&t, &tempoU, &tempoS);
	printf("Tempo de sistema Paralelismo de Dados: %.9f\n",tempoS);
	printf("Tempo de usuário Paralelismo de Dados: %.9f\n",tempoU);

	/*		PARALELISMO DE CONTROLE		*/
	iniciaTempo(&t);
	Ordena (L2);
  pControle (L2, capacidadeC, andaresC, saida);
	finalizaTempo(&t, &tempoU, &tempoS);
	printf("Tempo de sistema Paralelismo de Controle: %.9f\n",tempoS);
	printf("Tempo de usuário Paralelismo de Controle: %.9f\n",tempoU);

	free(L1);
	free(L2);
	fclose(ambienteD);
	fclose(entradaD);
	fclose(ambienteC);
	fclose(entradaC);

  return 0;
}
