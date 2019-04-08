/*
 ============================================================================
 Name        : ProyectoSO.c
 Author      : Nao Diego
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Auto.c"
#include "Puente.c"

void* Puente_A_Terabithia(){
    
}


void* La_Ladrona_de_Libros(){
     FILE *fichero;
    fichero = fopen("data/data.txt", "r");

    char textoExtraido[60];
    int posicion = 0;
    int number[15];
    if (fichero) {
        fgets(textoExtraido, 60, fichero);
        for (int i = 0; i < 15; i++) {
            fscanf(fichero, "%d", &number[i]);

        }
    } else {
        printf("NO SIRVO");
        exit(1);
    }
    fclose(fichero);
    p.longitud = number[0];
    e.k_carros_e = number[1];
    e.pro_lle = number[2];
    e.tie_sem = number[3];
    e.vel_min = number[4];
    e.vel_max = number[5];
    e.k_veh_x_pas = number[6];
    e.k_amb = number[7];
    e.k_carros_e = number[1];
    o.pro_lle = number[2];
    o.tie_sem = number[3];
    o.vel_min = number[4];
    o.vel_max = number[5];
    o.k_veh_x_pas = number[6];
    o.k_amb = number[7];
}

int main() {
    La_Ladrona_de_Libros();
    Puente_A_Terabithia();
    return EXIT_SUCCESS;
}
