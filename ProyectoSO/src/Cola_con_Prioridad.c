
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Auto.h"

struct Cola_con_Prioridad {
    Auto cola[300];
    int final;

    Cola_con_Prioridad() {
        ppio = null;
        inicio = 0;
        final = 0;
    }
};

void enQueue(Cola_con_Prioridad* c, Auto a) {
    if (c->final) {
        struct Nodo* aux = c->ppio;
        while (aux->sig) {
            aux = aux->sig;
        }

    }
}
