/*
 ============================================================================
 Name        : ProyectoSO.c
 Author      : Nao Diego
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include "Auto.c"
//#include "Este.c"
//#include "Oeste.c"
//#include "Puente.c"

int main(int argc, char** argv)
{
	FILE *fp;
	fp = fopen ("data/prueba.txt", "r" );
	char caracter;

	if (fp) {
		while((caracter = fgetc(fp)) != EOF){
			if(caracter != "#"){
				printf("%s",caracter);
			}else{

			}
		}
	}
	else{
		printf("NO SIRVO");
		exit (1);
	}
	fclose ( fp );
	return EXIT_SUCCESS;
}
