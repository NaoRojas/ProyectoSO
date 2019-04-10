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
#include <math.h>
#include "Auto.c"
#include "Puente.c"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct Puente p;
struct PuntosCardinales o;
struct PuntosCardinales e;

void bloquear() {
    pthread_mutex_lock(&mutex);
}

void desbloquear() {
    pthread_mutex_unlock(&mutex);
}

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
}

void* Puente_A_Terabithia(void* a) {
    struct Auto* aux0 = (struct Auto*) a;
    free(a);
    struct Auto* aux2;
    double t;
    if (aux0->direccion) {
        //enQueue(&Cola_Oeste,&a);
    } else {
        //enQueue(&Cola_Este, &a);
    }
    if(p.direccion){
        //aux2 = deQueue(&Cola_Oeste);
    }else{
        //aux2 = deQueue(&Cola_Eeste);
    }
    //printf("El auto va del Oeste al Este, %s, %d, %.2f\n",
    //        aux2->nombre, aux2->prioridad, aux2->velocidad);
    //t = p.longitud / aux2->velocidad;
    //sleep(t);
    desbloquear();
}

void* creandoAutosEste(void* arg) {
    int num_pth = 300;
    int cont = 0;
    srand(time(NULL));
    double randCrear;
    double rand;
    struct Auto* a[num_pth - 1];
    pthread_t tids[num_pth - 1];
    for (int i = 0; i < num_pth; i++) {
        a[i] = (struct Auto*) malloc(sizeof (struct Auto));
        if (cont == p.ladoEste.k_amb) {
            a[i]->prioridad = 1;
            a[i]->nombre = "Ambulancia";
            cont = 0;
        } else {
            a[i]->prioridad = 2;
            a[i]->nombre = "Automoviles";
            cont++;
        }
        a[i]->velocidad = (drand48() * 4 + 4);
        a[i]->direccion = 0;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, Puente_A_Terabithia, &a[i]);
        rand = drand48() * 2.0;
        randCrear = -p.ladoEste.pro_lle * log(1 - rand);
        sleep(randCrear);
    }
    for (int i = 0; i < num_args; i++) {
        pthread_join(tids[i], NULL);
    }
}

void* creandoAutosOeste(void* arg) {
    int num_pth = 288;
    int cont = 0;
    srand(time(NULL));
    double randCrear;
    double rand;
    struct Auto* a[num_pth - 1];
    pthread_t tids[num_pth - 1];
    for (int i = 0; i < num_pth; i++) {
        a[i] = (struct Auto*) malloc(sizeof (struct Auto));
        if (cont == p.ladoOeste.k_amb) {
            a[i]->prioridad = 1;
            a[i]->nombre = "Ambulancia";
            cont = 0;
        } else {
            a[i]->prioridad = 2;
            a[i]->nombre = "Automoviles";
            cont++;
        }
        a[i]->velocidad = (drand48() * 18 + 12);
        a[i]->direccion = 1;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, Puente_A_Terabithia, &a[i]);
        rand = drand48() * 2.0;
        randCrear = -p.ladoOeste.pro_lle * log(1 - rand);
        sleep(randCrear);
    }
    for (int i = 0; i < num_args; i++) {
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
    e.k_amb = e.k_amb * 100 / 300;
    //Datos Oeste
    o.k_carros_e = number[1]; //Cantidad de carros
    o.pro_lle = number[2]; //Promedio de llegada
    o.tie_sem = number[3]; //Tiempo de Semaforo
    o.vel_min = number[4]; //Velocidad Minima
    o.vel_max = number[5]; //Velocidad Maxima
    o.k_veh_x_pas = number[6]; //Cantidad de vehiculos por paso
    o.k_amb = number[7]; //Prcentaje de ambulancias
    o.k_amb = o.k_amb * 100 / 288;
    //Asignando los puntos de entrada
    p.ladoEste = e;
    p.ladoOeste = o;
    p.direccion = 0;
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
}

int main() {
    encenderSemaforo();
    La_Ladrona_de_Libros();
    creandoAutosEste();
    return EXIT_SUCCESS;
}
