/*
 ============================================================================
 Name        : ProyectoSO.c
 Author      : Nao Diego
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "Auto.c"
#include "Este.c"
#include "Oeste.c"
#include "Puente.c"

int main(int argc, char** argv)
{
	Auto a;
	a.prioridad = 0;
	a.direccion = false;

	printf("Informacion de auto %d %d", a.prioridad, a.direccion);

	//FILE *fichero;
	//fichero = fopen ("data/data.txt", "r" );
	//char caracter;
	//char textoExtraido[60];
	//int posicion = 0;
	//int number[15];
	//if (fichero) {
	//    fgets(textoExtraido, 60, fichero);
	//	for(int i =0; i < 15; i++){
	//		fscanf (fichero, "%d", &number[i]);

	//	}
	//}
	//else{
	//	printf("NO SIRVO");
	//	exit (1);
	//}
	//fclose(fichero);
	return EXIT_SUCCESS;
}
