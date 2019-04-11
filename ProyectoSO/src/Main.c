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
static struct Puente PUENTE;
static struct PuntosCardinales OESTE;
static struct PuntosCardinales ESTE;
static struct Cola COLA_OESTE;
static struct Cola COLA_ESTE;

void enQueue(struct Auto* a, struct Cola* c);

struct Auto* deQueue(struct Cola* c);

void bloquear();

void desbloquear();

void* semaforo(void* arg);

void* Puente_A_Terabithia(void* arg);

void* creandoAutosEste(void* arg);

void* creandoAutosOeste(void* arg);

void La_Ladrona_de_Libros();

void toString(struct Cola* c);

int main() {

    srand(time(NULL));
    La_Ladrona_de_Libros();

    pthread_t tid0;
    pthread_attr_t attr0;
    pthread_attr_init(&attr0);
    pthread_create(&tid0, &attr0, creandoAutosEste, NULL);

/*
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, Puente_A_Terabithia, NULL);
*/

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

    pthread_join(tid0, NULL);
/*
    pthread_join(tid, NULL);
*/

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
    pthread_mutex_lock(&mutex);
    struct Nodo* ppio = c->ppio;
    pthread_mutex_unlock(&mutex);
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
    pthread_mutex_lock(&mutex);
    struct Nodo* ppio = c->ppio;
    pthread_mutex_unlock(&mutex);
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
    struct Auto* aux2;
    double t;
    int d;
    while (1) {
        pthread_mutex_lock(&mutex);
        d = PUENTE.direccion;
        pthread_mutex_unlock(&mutex);
        if (d) {
            aux2 = deQueue(&COLA_OESTE);
        } else {
            aux2 = deQueue(&COLA_ESTE);
        }
        if (!aux2) {
            printf("%s, %d, %f\n",
                    aux2->nombre, aux2->prioridad, aux2->velocidad);
            t = PUENTE.longitud / aux2->velocidad;
            sleep(t);
        } else {
            printf("El Puente esta vacio\n");
        }
    }
}

void* creandoAutosOeste(void* arg) {
    int num_pth = 288;
    int cont = 0;
    double randCrear;
    double rand;
    pthread_mutex_lock(&mutex);
    struct Cola* colita = &COLA_OESTE;
    int k_amb = OESTE.k_amb;
    int pro_lle = OESTE.pro_lle;
    pthread_mutex_unlock(&mutex);
    for (int i = 0; i < num_pth; i++) {
        struct Auto * a = (struct Auto*) malloc(sizeof (struct Auto));
        if (cont == k_amb) {
            a->prioridad = 1;
            a->nombre = "Ambulancia";
            cont = 0;
        } else {
            a->prioridad = 2;
            a->nombre = "Automoviles";
            cont++;
        }
        a->velocidad = (drand48() * 18 + 12);
        a->direccion = 0;
        enQueue(a, colita);
        rand = drand48() * 2.0;
        randCrear = -pro_lle * log(1 - rand);
        sleep(randCrear);
    }
}

void* creandoAutosEste(void* arg) {
    int num_pth = 300;
    int cont = 0;
    double randCrear;
    double rand;
    pthread_mutex_lock(&mutex);
    struct Cola* colita = &COLA_ESTE;
    int k_amb = ESTE.k_amb;
    int pro_lle = ESTE.pro_lle;
    pthread_mutex_unlock(&mutex);
    for (int i = 0; i < num_pth; i++) {
        struct Auto * a = (struct Auto*) malloc(sizeof (struct Auto));
        if (cont == k_amb) {
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
        enQueue(a, colita);
        rand = drand48() * 2.0;
        randCrear = -pro_lle * log(1 - rand);
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
    PUENTE.direccion = 0;
    //Datos este
    ESTE.k_carros_e = number[1]; //Cantidad de carros
    ESTE.pro_lle = number[2]; //Promedio de llegada
    ESTE.tie_sem = number[3]; //Tiempo de Semaforo
    ESTE.vel_min = number[4]; //Velocidad Minima
    ESTE.vel_max = number[5]; //Velocidad Maxima
    ESTE.k_veh_x_pas = number[6]; //Cantidad de vehiculos por paso
    ESTE.k_amb = number[7]; //Prcentaje de ambulancias
    //ESTE.k_amb = ESTE.k_amb * 100 / 300;
    ESTE.k_amb = 14;
    //Datos Oeste
    OESTE.k_carros_e = number[1]; //Cantidad de carros
    OESTE.pro_lle = number[2]; //Promedio de llegada
    OESTE.tie_sem = number[3]; //Tiempo de Semaforo
    OESTE.vel_min = number[4]; //Velocidad Minima
    OESTE.vel_max = number[5]; //Velocidad Maxima
    OESTE.k_veh_x_pas = number[6]; //Cantidad de vehiculos por paso
    OESTE.k_amb = number[7]; //Prcentaje de ambulancias
    //OESTE.k_amb = OESTE.k_amb * 100 / 288;
    OESTE.k_amb = 14;
    COLA_OESTE.ppio = NULL;
    COLA_ESTE.ppio = NULL;
}

void* semaforo(void* arg) {
    pthread_mutex_lock(&mutex);
    int tie_semE = ESTE.k_amb;
    int tie_semO = OESTE.pro_lle;
    pthread_mutex_unlock(&mutex);
    while (1) {
        pthread_mutex_lock(&mutex);
        PUENTE.direccion = 0;
        pthread_mutex_unlock(&mutex);
        sleep(tie_semE);
        pthread_mutex_lock(&mutex);
        PUENTE.direccion = 1;
        pthread_mutex_unlock(&mutex);
        sleep(tie_semO);
    }
}