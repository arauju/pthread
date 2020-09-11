# pthread
O programa é compilado pelo utilitário Make.

Devido ao padrão de entradas criado, além dos módulos utilizados um arquivo de entrada aleatória e ambiente pré-definido também está incluído.
Ainda, o programa que gera as entradas também foi enviado. Porém, ele não se encontra no make, sendo opcional sua utilização. Para executá-lo é necessário o seguinte comando:
	gcc entradas.c -o main
	./main entradaD.txt ambienteD.txt entradaC.txt ambienteC.txt
