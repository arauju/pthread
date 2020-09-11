#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {

  FILE *entradaD = fopen("entradaD.txt","w");
  FILE *ambienteD = fopen("ambienteD.txt", "w");
  FILE *entradaC = fopen("entradaC.txt","w");
  FILE *ambienteC = fopen("ambienteC.txt","w");

  int chamada, destino, i;
  srand((unsigned)time(NULL));

  //Variaveis DADOS
  int capD = 15, andaresD = 3, pessoasD = 1000;

  //Variaveis CONTROLE
  int capC = 15, andaresC = 3 , pessoasC = 1000;

  //ambiente
  fprintf(ambienteD, "%d\n%d", capD, andaresD);
  fprintf(ambienteC, "%d\n%d", capC, andaresC);

  //entrada DADOS
  for (i = 0; i < pessoasD; i++) {
      chamada = rand() % andaresD;
      destino = rand() % andaresD;
      while (chamada == destino || chamada == 0 || destino == 0){
          chamada = rand() % andaresD;
          destino = rand() % andaresD;
      }
          fprintf(entradaD, "%d %d\n", chamada, destino);
  }

  //entrada CONTROLE
  for (i = 0; i < pessoasC; i++) {
      chamada = rand() % andaresC+1;
      destino = rand() % andaresC+1;
      while (chamada == destino || chamada == 0 || destino == 0){
          chamada = rand() % andaresC+1;
          destino = rand() % andaresC+1;
      }
          fprintf(entradaC, "%d %d\n", chamada, destino);
  }
    return 0;
}
