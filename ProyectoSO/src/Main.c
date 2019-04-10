/*
 ============================================================================
 Name        : ProyectoSO.c
 Author      : Nao Diego
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "Auto.c"
#include "Puente.c"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct Puente p;
struct PuntosCardinales o;
struct PuntosCardinales e;

void* semaforo(void* arg) {
    while (1) {
        if (p.direccion) {
            p.direccion = 0;
            sleep(p.ladoOeste.tie_sem);
        } else {
            p.direccion = 1;
            sleep(p.ladoEste.tie_sem);
        }
    }
}

void encenderSemaforo() {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, semaforo, NULL);
    pthread_join(tid, NULL);
}

void* Puente_A_Terabithia(void* a) {
    struct Auto* aux = (struct Auto*) a;
    struct Auto* aux2;
    if (p.direccion) {
        //Aqui va la cola del oeste
        //enQueue(&Cola_Oeste,&a);
        //pthread_mutex_lock(&mutex);
        //aux2 = deQueue(&Cola_Oeste);
        //printf("El auto va del Oeste al Este, %s, %d, %.2f\n",
        //        aux2->nombre, aux2->prioridad, aux2->velocidad);
        //sleep(aux2->velocidad);
    } else {
        //Aqui va la cola del Este
        //enQueue(&Cola_Este, &a);
        //pthread_mutex_lock(&mutex);
        //aux2 = deQueue(&Cola_Este);
        //printf("El auto va del Oeste al Este, %s, %d, %.2f\n",
        //        aux2->nombre, aux2->prioridad, aux2->velocidad);
        //sleep(aux2->velocidad);
    }
    pthread_mutex_unlock(&mutex);
}

void creandoHilos() {
    int num_pth = 588;
    int cont = 0;
    srand(time(NULL));
    double rand = drand48() * (1.0 + 1.0);
    pthread_t tids[num_pth - 1];
    for (int i = 0; i < num_pth; i++) {
        struct Auto* a = (struct Auto*) malloc(sizeof (struct Auto));
        if (p.direccion) {
            //Aca van los calculos
        } else {

        }
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, Puente_A_Terabithia, &a);
    }
    for (int i = 0; i < num_pth; i++) {
        pthread_join(tids[i], NULL);
    }
}

void La_Ladrona_de_Libros() {
    FILE *fichero;
    fichero = fopen("data/data.txt", "r");
    char textoExtraido[60];
    int number[15];
    if (fichero) {
        fgets(textoExtraido, 60, fichero);
        for (int i = 0; i < 15; i++)
            fscanf(fichero, "%d", &number[i]);
    }
    fclose(fichero);

    p.longitud = number[0]; //Longitud de puente
    //Datos este
    e.k_carros_e = number[1]; //Cantidad de carros
    e.pro_lle = number[2]; //Promedio de llegada
    e.tie_sem = number[3]; //Tiempo de Semaforo
    e.vel_min = number[4]; //Velocidad Minima
    e.vel_max = number[5]; //Velocidad Maxima
    e.k_veh_x_pas = number[6]; //Cantidad de vehiculos por paso
    e.k_amb = number[7]; //Prcentaje de ambulancias
    //Datos Oeste
    o.k_carros_e = number[1]; //Cantidad de carros
    o.pro_lle = number[2]; //Promedio de llegada
    o.tie_sem = number[3]; //Tiempo de Semaforo
    o.vel_min = number[4]; //Velocidad Minima
    o.vel_max = number[5]; //Velocidad Maxima
    o.k_veh_x_pas = number[6]; //Cantidad de vehiculos por paso
    o.k_amb = number[7]; //Prcentaje de ambulancias
    //Asignando los puntos de entrada
    p.ladoEste = e;
    p.ladoOeste = o;
    p.direccion = 0;
    /*
        printf("Longitud de Puente %d \n"
                "Datos Este  \n"
                "Cantidad de carros %d \n"
                "Promedio de llegada %d \n"
                "Tiempo de semaforo %d  \n"
                "Velocidad Maxima  %d \n"
                "Vecidad Minima %d  \n"
                "Cantidad de vehiculos por paso %d  \n"
                "Porcentaje de ambulancias %d \n",
                p.longitud, e.k_carros_e, e.pro_lle, e.tie_sem, e.vel_min, e.vel_max, e.k_veh_x_pas, e.k_amb);

        printf("Datos Oeste  \n"
                "Cantidad de carros %d \n"
                "Promedio de llegada %d \n"
                "Tiempo de semaforo %d  \n"
                "Velocidad Maxima  %d \n"
                "Vecidad Minima %d  \n"
                "Cantidad de vehiculos por paso %d  \n"
                "Porcentaje de ambulancias %d \n",
                o.k_carros_e, o.pro_lle, o.tie_sem, o.vel_min, o.vel_max, o.k_veh_x_pas, o.k_amb);
     */
}

int main() {
    encenderSemaforo();
    La_Ladrona_de_Libros();
    creandoHilos();
    return EXIT_SUCCESS;
}
