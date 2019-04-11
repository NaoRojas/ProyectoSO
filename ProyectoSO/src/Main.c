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
#include "Puente.c"
#include "Cola.c"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct Puente PUENTE;
struct PuntosCardinales OESTE;
struct PuntosCardinales ESTE;
struct Cola COLA_OESTE;
struct Cola COLA_ESTE;

void enQueue(struct Auto* a, struct Cola* c);

struct Auto* deQueue(struct Cola* c);

void bloquear();

void desbloquear();

void* semaforo(void* arg);

void encenderSemaforo();

void* Puente_A_Terabithia(void* arg);

void* creandoAutosEste(void* arg);

void* creandoAutosOeste(void* arg);

void La_Ladrona_de_Libros();

void creandoAutos();

void toString(struct Cola* c);

int main() {
    srand(time(NULL));
    La_Ladrona_de_Libros();

    pthread_t tid2;
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);
    pthread_create(&tid2, &attr2, semaforo, NULL);

    pthread_t tid0;
    pthread_attr_t attr0;
    pthread_attr_init(&attr0);
    pthread_create(&tid0, &attr0, creandoAutosEste, NULL);

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, Puente_A_Terabithia, NULL);

    /*
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, creandoAutosOeste, NULL);

        pthread_t tid2;
        pthread_attr_t attr2;
        pthread_attr_init(&attr2);
        pthread_create(&tid2, &attr2, semaforo, NULL);
     */

    pthread_join(tid2, NULL);
    pthread_join(tid0, NULL);
    pthread_join(tid, NULL);

    return EXIT_SUCCESS;
}

void toString(struct Cola* c) {
    struct Nodo* actual = c->ppio;
    while (actual) {
        printf("%s, %d, %.2f\n",
                actual->ptrObj->nombre, actual->ptrObj->prioridad, actual->ptrObj->velocidad);
        actual = actual->sig;
    }
    printf("------------------------------------------------------------\n");
}

struct Auto* deQueue(struct Cola* c) {
    struct Nodo* eliminar;
    struct Auto* aux = NULL;
    bloquear();
    struct Nodo* ppio = c->ppio;
    desbloquear();
    if (ppio) {
        aux = c->ppio->ptrObj;
        eliminar = c->ppio;
        c->ppio = c->ppio->sig;
        free(eliminar);
    }
    return aux;
}

void enQueue(struct Auto* a, struct Cola* c) {
    struct Nodo* nuevo = (struct Nodo*) malloc(sizeof (struct Nodo));
    nuevo->ptrObj = a;
    bloquear();
    struct Nodo* ppio = c->ppio;
    desbloquear();
    if (!ppio) {
        nuevo->sig = ppio;
        ppio = nuevo;
    } else {
        if (ppio->ptrObj->prioridad >= a->prioridad) {
            nuevo->sig = ppio;
            ppio = nuevo;
        } else {
            struct Nodo* actual = ppio;
            while (actual->sig) {
                if (actual->sig->ptrObj->prioridad >= a->prioridad)
                    break;
                actual = actual->sig;
            }
            nuevo->sig = actual->sig;
            actual->sig = nuevo;
        }
    }
}

void* Puente_A_Terabithia(void* arg) {
    struct Auto aux2;
    double t;
    int d;
    while (1) {
        bloquear();
        d = PUENTE.direccion;
        desbloquear();
        if (d) {
            aux2 = *deQueue(&COLA_OESTE);
        } else {
            aux2 = *deQueue(&COLA_ESTE);
        }
        if (!aux2) {
            printf("%s, %d, %f\n",
                    aux2.nombre, aux2.prioridad, aux2.velocidad);
            t = PUENTE.longitud / aux2.velocidad;
            sleep(t);
        }
    }
}

void creandoAutos() {
    printf("creandoAutos");
    pthread_t tid0;
    pthread_attr_t attr0;
    pthread_attr_init(&attr0);
    pthread_create(&tid0, &attr0, creandoAutosEste, NULL);

    /*
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, creandoAutosOeste, NULL);
     */

    pthread_join(tid0, NULL);
    /*
        pthread_join(tid, NULL);
     */
}

void* creandoAutosOeste(void* arg) {
    int num_pth = 288;
    int cont = 0;
    srand(time(NULL));
    double randCrear;
    double rand;
    struct Auto * a[num_pth - 1];
    pthread_t tids[num_pth - 1];
    for (int i = 0; i < num_pth; i++) {
        a[i] = (struct Auto*) malloc(sizeof (struct Auto));
        if (cont == PUENTE.ladoOeste.k_amb) {
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
        randCrear = -PUENTE.ladoOeste.pro_lle * log(1 - rand);
        sleep(randCrear);
    }
    for (int i = 0; i < num_pth; i++) {
        pthread_join(tids[i], NULL);
    }
}

void* creandoAutosEste(void* arg) {
    int num_pth = 300;
    int cont = 0;
    double randCrear;
    double rand;
    pthread_t tids[num_pth - 1];
    for (int i = 0; i < num_pth; i++) {
        struct Auto * a = (struct Auto*) malloc(sizeof (struct Auto));
        if (cont == PUENTE.ladoEste.k_amb) {
            a->prioridad = 1;
            a->nombre = "Ambulancia";
            cont = 0;
        } else {
            a->prioridad = 2;
            a->nombre = "Automoviles";
            cont++;
        }
        a->velocidad = (drand48() * 4 + 4);
        a->direccion = 0;
        enQueue(a, &COLA_ESTE);
        rand = drand48() * 2.0;
        randCrear = -PUENTE.ladoEste.pro_lle * log(1 - rand);
        sleep(randCrear);
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
    PUENTE.longitud = number[0]; //Longitud de puente
    //Datos este
    ESTE.k_carros_e = number[1]; //Cantidad de carros
    ESTE.pro_lle = number[2]; //Promedio de llegada
    ESTE.tie_sem = number[3]; //Tiempo de Semaforo
    ESTE.vel_min = number[4]; //Velocidad Minima
    ESTE.vel_max = number[5]; //Velocidad Maxima
    ESTE.k_veh_x_pas = number[6]; //Cantidad de vehiculos por paso
    ESTE.k_amb = number[7]; //Prcentaje de ambulancias
    ESTE.k_amb = ESTE.k_amb * 100 / 300;
    //Datos Oeste
    OESTE.k_carros_e = number[1]; //Cantidad de carros
    OESTE.pro_lle = number[2]; //Promedio de llegada
    OESTE.tie_sem = number[3]; //Tiempo de Semaforo
    OESTE.vel_min = number[4]; //Velocidad Minima
    OESTE.vel_max = number[5]; //Velocidad Maxima
    OESTE.k_veh_x_pas = number[6]; //Cantidad de vehiculos por paso
    OESTE.k_amb = number[7]; //Prcentaje de ambulancias
    OESTE.k_amb = OESTE.k_amb * 100 / 288;
    //Asignando los puntos de entrada
    PUENTE.ladoEste = ESTE;
    PUENTE.ladoOeste = OESTE;
    PUENTE.direccion = 0;
}

void* semaforo(void* arg) {
    while (1) {
        bloquear();
        PUENTE.direccion = 0;
        desbloquear();
        sleep(PUENTE.ladoOeste.tie_sem);
        bloquear();
        PUENTE.direccion = 1;
        desbloquear();
        sleep(PUENTE.ladoEste.tie_sem);
    }
}

void encenderSemaforo() {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, semaforo, NULL);
    pthread_join(tid, NULL);
}

void bloquear() {
    pthread_mutex_lock(&mutex);
}

void desbloquear() {
    pthread_mutex_unlock(&mutex);
}