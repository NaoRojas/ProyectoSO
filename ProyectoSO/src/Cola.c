
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Auto.h"

struct Nodo {
    Nodo* sig;
    Auto* ptrObj;
};

struct Cola {
    struct Nodo* ppio;

    void enQueue(struct Auto* a) {
        struct Nodo* nuevo = (struct Nodo*) malloc(sizeof (struct Nodo));
        nuevo->ptrObj = a;
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

    struct Auto* deQueue() {
        struct Nodo* eliminar;
        struct Auto* aux = NULL;
        if (ppio) {
            aux = ppio->ptrObj;
            eliminar = ppio;
            ppio = ppio->sig;
            free(eliminar);
        }
        return aux;
    }

    void toString() {
        struct Nodo* actual = ppio;
        while (actual) {
            printf("%s, %d, %.2f\n",
                    actual->ptrObj->nombre, actual->ptrObj->prioridad, actual->ptrObj->velocidad);
            actual = actual->sig;
        }
        return r.str();
    }
};
