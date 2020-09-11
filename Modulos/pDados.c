/*
 * JULIANA DE FÁTIMA OVÍDIO ARAÚJO
 *
 * ESTRATÉGIA2T.C
 *
 * TRABALHO PRÁTICO IV
 *
 * CIÊNCIA DA COMPUTAÇÃO
 * ALGORITMOS E ESTRUTURAS DE DADOS III
 * 2/2016
 *
*/

#include "pDados.h"

#define n_elevadores 3

pthread_t THREADS[n_elevadores];
pthread_mutex_t mutex;

int andarA[n_elevadores], porta[n_elevadores], distTotal[n_elevadores], marcd = 0, ocup[n_elevadores], andarA[n_elevadores];
int tForaTotal[n_elevadores], tempoTotalF[n_elevadores], tempoTotalD[n_elevadores], portaAberta[n_elevadores];

void *subir (void *arg){
	ptr_thread_arg argumento = (ptr_thread_arg) arg;
	int i = argumento->elevador, prim, ult, nPessoas = argumento->L->tamanho;

	lno *aux, *aux2;
	aux = argumento->L->primeira;
	aux2 = argumento->L->primeira;

	//define o intervalo de cada thread
	prim = (i * nPessoas)/n_elevadores;
	ult = (((i + 1) * nPessoas)/n_elevadores) - 1;

	while (listVaziaL(argumento->L) == 0){

		/*           SUBINDO O ELEVADOR        */
		while (andarA[i] < argumento->andares){
			//verifica se alguem desse elevador pode descer
			aux = argumento->L->primeira;
			while (aux != NULL && (argumento->L->tamanho != 0)){
				if ((aux->passageiro.marcador == 1) && (andarA[i] == aux->passageiro.destino) && (aux->passageiro.elev == i)){
					ocup[i] --;
					aux->passageiro.tDentro = tForaTotal[i] - aux->passageiro.tFora;
					aux->passageiro.id = marcd;
					tempoTotalD[i] += aux->passageiro.tDentro;
					marcd ++;
					tForaTotal[i] ++;
					pthread_mutex_lock(&mutex);
					removerL(argumento->L, aux->passageiro);
					pthread_mutex_unlock(&mutex);

					//verificar se a porta já está aberta
					if (portaAberta[i] == 0)
						porta[i] ++;
					portaAberta[i] = 1;
				}

				//aponta-se para o próximo passageiro, caso a lista não esteja vazia
				if (listVaziaL (argumento->L) == 0)
					aux = aux->proxima;
				else
					aux = argumento->L->primeira;
		}

			//faz o ponteiro voltar para onde estava antes
			aux = aux2;

			//pegar os passageiros daquele andar
			while ((aux != NULL) && (argumento->L->tamanho != 0) && (andarA[i] == aux->passageiro.chamada)){
				if ((ocup[i] < argumento->capacidade) && (aux->passageiro.destino > andarA[i])
										&& (aux->passageiro.marcador == 0) && (aux->passageiro.id >= prim && aux->passageiro.id <= ult)){
					aux->passageiro.marcador = 1;
					aux->passageiro.elev = i;
					ocup[i] ++;
					aux->passageiro.tFora = tForaTotal[i];
					tempoTotalF[i] = tempoTotalF[i] + tForaTotal[i];
					tForaTotal[i] ++;

					//verificar se a porta já está aberta
					if (portaAberta[i] == 0)
						porta[i] ++;
					portaAberta[i] = 1;
				}

				//aponta para o proximo se a lista nao esta vazia
				if (listVaziaL (argumento->L) == 0)
					aux = aux->proxima;
				else
					aux = argumento->L->primeira;
			}

			//elevador vai para o proximo andar
			andarA[i] ++;
			portaAberta[i] = 0;
			distTotal[i] ++;
			tForaTotal[i] ++;
		}

		//Para começar a descer os andares, os auxiliares são apontados pra a ultima pessoa da lista
		aux = argumento->L->ultima;
		aux2 = argumento->L->ultima;


		/*							DESCENDO O ELEVADOR                  */
	 	while (andarA[i] > 1 && (listVaziaL(argumento->L) == 0)){

			//percorre toda a lista para verificar se alguem pode descer
			while (aux != NULL && argumento->L->tamanho != 0){
				if ((aux->passageiro.marcador == 1) && (andarA[i] == aux->passageiro.destino) && (aux->passageiro.elev == i)){
					ocup[i] --;
					aux->passageiro.tDentro = tForaTotal[i] - aux->passageiro.tFora;
					marcd ++;
					aux->passageiro.id = marcd;
					tempoTotalD[i] += aux->passageiro.tDentro;
					tForaTotal[i] ++;
					pthread_mutex_lock(&mutex);
					removerL (argumento->L, aux->passageiro);
					pthread_mutex_unlock(&mutex);

					//verificar se a porta já está aberta
					if (portaAberta[i] == 0)
						porta[i] ++;
					portaAberta[i] = 1;
				}

				//aponta-se para o próximo passageiro, caso a lista não esteja vazia
				if (listVaziaL(argumento->L) == 0)
					aux = aux->proxima;
				else
					aux = argumento->L->primeira;
			}

			//faz o ponteiro voltar para a pessoa em questão
			if (listVaziaL (argumento->L) == 0)
				aux = aux2;

			//pegar os passageiros daquele andar
			while ((aux != NULL) && (argumento->L->tamanho != 0) && (andarA[i] == aux->passageiro.chamada)){
				if ((ocup[i] < argumento->capacidade) && (aux->passageiro.destino < andarA[i]) && (aux->passageiro.marcador == 0)
				                     && (aux->passageiro.id >= prim && aux->passageiro.id <= ult)){
					aux->passageiro.marcador = 1;
					aux->passageiro.elev = i;
					ocup[i] ++;
					aux->passageiro.tFora = tForaTotal[i];
					tempoTotalF[i] = tempoTotalF[i] + tForaTotal[i];
					tForaTotal[i] ++;

					//verificar se a porta já está aberta
					if (portaAberta[i] == 0)
						porta[i] ++;
					portaAberta[i] = 1;
				}

				//aponta-se para o proximo passageiro, caso a lista não esteja vazia
				if (listVaziaL (argumento->L) == 0){
					aux2 = aux->anterior;
					aux = aux->anterior;
				}
			}

			//Elevador vai para andar anterior, e a distância percorrida é acrescida
			andarA[i] --;
			portaAberta[i] = 0;
			distTotal[i] ++;
			tForaTotal[i] ++;
		}
	}
}

void pDados (tlista *L1, int capacidadeD, int andaresD, char *saida){
	FILE *out;
	out = fopen(saida, "w");

	int k, nPessoas = L1->tamanho, mediaTempoTotalD = 0, mediaTempoTotalF = 0, mediaPorta = 0, mediaDistTotal = 0, intervalo;

	//THREADS
	thread_arg argumento[n_elevadores];

	lno *aux;
	aux = L1->primeira;
	for (k = 0; aux != NULL; k++){
		aux->passageiro.id = k;
		aux = aux->proxima;
	}

	//zera variaveis
	for (k = 0; k < n_elevadores; k++){
		porta[k] = 0;
		portaAberta[k] = 0;
		ocup[k] = 0;
		distTotal[k] = 0;
		tForaTotal[k] = 0;
		tempoTotalF[k] = 0;
		tempoTotalD[k] = 0;

		argumento[k].andares = andaresD;
		argumento[k].capacidade = capacidadeD;
		argumento[k].L = L1;
	}

	pthread_mutex_init(&mutex, NULL);

	//cria threads
	for (k = 0; k < n_elevadores; k++){
		argumento[k].elevador = k;
		pthread_create(&(THREADS[k]), NULL, subir, &argumento[k]);
	}

	for(k = 0; k < n_elevadores; k++){
		pthread_join(THREADS[k], NULL);
	}

	//Calcula os resultados finais
	for (k = 0; k < n_elevadores; k++){
		mediaTempoTotalD += tempoTotalD[k];
		mediaTempoTotalF += tempoTotalF[k];
		mediaPorta += porta[k];
		mediaDistTotal += distTotal[k];
	}

	//Imprimir os resultados no arquivo de saída
	fprintf(out, "\nPARALELISMO DE DADOS");
	fprintf(out, "\nNúmero de elevadores: %d, número de passageiros: %d\n", n_elevadores, nPessoas);
	fprintf(out, "\nPassageiros\n");

	fprintf (out, "\nTempo médio total de cada pessoa DENTRO: %d Jepslons, FORA: %d Jepslons\n",
													mediaTempoTotalD/(nPessoas * n_elevadores), mediaTempoTotalF/(nPessoas * n_elevadores));
	fprintf (out, "\n Elevador\n");
	fprintf (out, "Numero médio de vezes que a porta abriu: %d \nDistancia total percorrida media: %d andares\n\n",
													mediaPorta/n_elevadores, mediaDistTotal/n_elevadores);
	fclose (out);
}
