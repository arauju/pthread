/*
 * JULIANA DE FÁTIMA OVÍDIO ARAÚJO
 *
 * PCONTROLE.C
 *
 * TRABALHO PRÁTICO IV
 *
 * CIÊNCIA DA COMPUTAÇÃO
 * ALGORITMOS E ESTRUTURAS DE DADOS III
 * 2/2016
 *
*/

#include "pControle.h"

#define n_andares 3

pthread_t THREADSC[n_andares];
pthread_mutex_t mutex2;

int Porta[n_andares], DistTotal[n_andares], Marcd, TForaTotal[n_andares], TempoTotalF[n_andares], TempoTotalD[n_andares];

void *elevadores (void *arg){
	pt_thread_arg argumento = (pt_thread_arg) arg;
	lno *aux, *aux2;
	aux = (lno*) malloc(sizeof(lno));
	aux2 = (lno*) malloc(sizeof(lno));
	int idThread = argumento->elevador, portaAberta = 0, ocup = 0, andarA;

	while (argumento->L->tamanho != 0){

		/*				SUBINDO					*/
		andarA = idThread + 1;
		aux = argumento->L->primeira;

		//encontra os passageiros daquele andar
		while ((aux != NULL) && (argumento->L->tamanho != 0) && (aux->passageiro.chamada != andarA)){
			aux = aux->proxima;
			if (aux == NULL)
				aux = argumento->L->primeira;
		}

		aux2 = aux;
		//pegar os passageiros daquele andar
		while ((aux != NULL) && (argumento->L->tamanho != 0) && (aux->passageiro.chamada == andarA)){
			if ((ocup < argumento->capacidade) && (aux->passageiro.marcador == 0) && (aux->passageiro.destino > andarA)){
				aux->passageiro.tFora += TForaTotal[idThread] - aux->passageiro.tFora;
				aux->passageiro.marcador = 1;
				aux->passageiro.elev = idThread;
				ocup ++;

				//verificar se a Portajá está aberta
				if (portaAberta == 0)
					Porta[idThread] ++;

				portaAberta = 1;
				TForaTotal[idThread] ++;
				//printf("pegou no andar %d subindo: %d %d %d\n", andarA, aux->passageiro.chamada, aux->passageiro. destino, aux->passageiro.marcador);
			}
			if (listVaziaL(argumento->L) == 0)
				aux = aux->proxima;
			else
				aux = argumento->L->primeira;
		}

		//atualiza variáveis
		aux = aux2;
		portaAberta = 0;
		andarA = idThread + 2;
		DistTotal[idThread] ++;
		TForaTotal[idThread] ++;

		//levar os passageiros
		while ((aux != NULL) && (argumento->L->tamanho != 0) && (aux->passageiro.chamada == (andarA - 1)) && (ocup != 0)){
			if ((aux->passageiro.marcador == 1) && (aux->passageiro.elev == idThread)){
				aux->passageiro.tDentro += TForaTotal[idThread] - aux->passageiro.tFora;
				aux->passageiro.marcador = 0;
				ocup --;

				//verificar se a Portajá está aberta
				if (portaAberta == 0)
					Porta[idThread] ++;

				portaAberta = 1;
				TForaTotal[idThread] ++;

				//desce o passageiro
				if (andarA == aux->passageiro.destino){
					TempoTotalD[idThread] += aux->passageiro.tDentro;
					TempoTotalF[idThread] += aux->passageiro.tFora;
					Marcd ++;
					aux->passageiro.id = Marcd;
					pthread_mutex_lock(&mutex2);
					removerL(argumento->L, aux->passageiro);
					pthread_mutex_unlock(&mutex2);
				} else
					aux->passageiro.chamada = andarA;
			}

			if (listVaziaL(argumento->L) == 0)
				aux = aux->proxima;
			else
				aux = argumento->L->primeira;
		}

		//atualiza variaveis
		DistTotal[idThread] ++;
		andarA = idThread + 1;
		portaAberta = 0;
		aux = argumento->L->primeira;

		/*		DESCENDO 		*/
		//encontra os passageiros do andar da thread
		while (aux != NULL && (argumento->L->tamanho != 0) && aux->passageiro.chamada != andarA){
			aux = aux->proxima;
			if (aux == NULL)
				aux = argumento->L->primeira;
		}

		if (andarA > 1){
			aux2 = aux;
			//pegar os passageiros daquele andar
			while ((aux != NULL) && (argumento->L->tamanho != 0) && (aux->passageiro.chamada == andarA)){
				if ((ocup < argumento->capacidade) && (aux->passageiro.destino < andarA) && (aux->passageiro.marcador == 0)){
					aux->passageiro.tFora += TForaTotal[idThread] - aux->passageiro.tFora;
					aux->passageiro.marcador = 1;
					aux->passageiro.elev = idThread;
					ocup ++;
					//verificar se a porta já está aberta
					if (portaAberta == 0)
						Porta[idThread]++;

					portaAberta = 1;
					TForaTotal[idThread] ++;
				}

				//aponta-se para o próximo passageiro, caso a lista não esteja vazia
				if (listVaziaL(argumento->L) == 0)
					aux = aux->proxima;
				else
					aux = argumento->L->primeira;
			}

			//levar os passageiros
			andarA = idThread;
			aux = aux2;
			while ((aux != NULL) && (argumento->L->tamanho != 0) && (aux->passageiro.chamada == andarA + 1) && (ocup != 0)){
				if (aux->passageiro.marcador == 1 && aux->passageiro.elev == idThread){
					aux->passageiro.marcador = 0;
					aux->passageiro.tDentro = TForaTotal[idThread] - aux->passageiro.tFora;
					ocup --;

					//verificar se a porta já está aberta
					if (portaAberta == 0)
						Porta[idThread]++;

					portaAberta = 1;
					TForaTotal[idThread] ++;

					//desce o passageiro
					if (andarA == aux->passageiro.destino){
						TempoTotalD[idThread] += aux->passageiro.tDentro;
						TempoTotalF[idThread] += aux->passageiro.tFora;
						Marcd ++;
						aux->passageiro.id = Marcd;
						pthread_mutex_lock(&mutex2);
						removerL(argumento->L, aux->passageiro);
						pthread_mutex_unlock(&mutex2);
					} else
						aux->passageiro.chamada = andarA;
				}

				//aponta-se para o próximo passageiro, caso a lista não esteja vazia
				if (listVaziaL(argumento->L) == 0)
					aux = aux->proxima;
				else
					aux = argumento->L->primeira;
			}
		}
		portaAberta = 0;
	}
}


void pControle (tlista *L2, int capacidadeC, int andaresC, char *saida){

	FILE *out;
	out = fopen(saida,"a");
	int nPessoas = L2->tamanho, k, mediaTempoTotalD = 0, mediaTempoTotalF = 0,
	mediaPorta = 0, mediaDistTotal = 0;

	//THREADS
	Thread_arg argumento[andaresC];

	if (andaresC != n_andares)
		printf("Numero de andares não correspondem.\n");

	for (k = 0; k < andaresC; k++){
		Porta[k] = 0;
		DistTotal[k] = 0;
		TForaTotal[k] = 0;
		TempoTotalF[k] = 0;
		TempoTotalD[k] = 0;

		argumento[k].andares = andaresC;
		argumento[k].capacidade = capacidadeC;
		argumento[k].L = L2;
	}

	pthread_mutex_init(&mutex2, NULL);

	//cria threads
	for (k = 0; k < andaresC; k++){
		argumento[k].elevador = k;
		pthread_create(&(THREADSC[k]), NULL, elevadores, &argumento[k]);
	}

	for(k = 0; k < andaresC; k++){
		pthread_join(THREADSC[k], NULL);
	}

	//Calcula e e imprimir os resultados no arquivo de saída
	for (k = 0; k < n_andares; k++){
		mediaTempoTotalD += TempoTotalD[k];
		mediaTempoTotalF += TempoTotalF[k];
		mediaPorta += Porta[k];
		mediaDistTotal += DistTotal[k];
	}

	//Imprimir os resultados no arquivo de saída
		fprintf(out, "\n\n---------------------------------------------------------------------------------------------\n" );
	fprintf (out, "\n\nPARALELISMO DE CONTROLE");
	fprintf(out, "\nNúmero de elevadores: %d, número de passageiros: %d\n", n_andares, nPessoas);
	fprintf (out, "\nPassageiros\n");
	fprintf (out, "\nTempo médio total de cada pessoa DENTRO: %d Jepslons, FORA: %d Jepslons\n",
													mediaTempoTotalD/(nPessoas * n_andares), mediaTempoTotalF/(nPessoas * n_andares));
	fprintf (out, "\n Elevador\n");
	fprintf (out, "Numero médio de vezes que a porta abriu: %d \nDistancia total percorrida media: %d andares\n\n",
													mediaPorta/n_andares, mediaDistTotal/n_andares);
}
