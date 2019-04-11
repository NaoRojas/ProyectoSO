
#include "Auto.c"

struct Nodo {
    struct Nodo* sig;
    struct Auto* ptrObj;
};

struct Cola {
    struct Nodo* ppio;
};

void enQueue(struct Cola* c, struct Auto* a) {
    struct Nodo* nuevo = (struct Nodo*) malloc(sizeof (struct Nodo));
    nuevo->ptrObj = a;
    if (!c->ppio) {
        nuevo->sig = c->ppio;
        c->ppio = nuevo;
    } else {
        if (c->ppio->ptrObj->prioridad >= a->prioridad) {
            nuevo->sig = c->ppio;
            c->ppio = nuevo;
        } else {
            struct Nodo* actual = c->ppio;
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

struct Auto* deQueue(struct Cola* c) {
    struct Nodo* eliminar;
    struct Auto* aux = NULL;
    if (c->ppio) {
        aux = c->ppio->ptrObj;
        eliminar = c->ppio;
        c->ppio = c->ppio->sig;
        free(eliminar);
    }
    return aux;
}

void toString(struct Cola* c) {
    struct Nodo* actual = c->ppio;
    while (actual) {
        printf("%s, %d, %.2f\n",
                actual->ptrObj->nombre, actual->ptrObj->prioridad, actual->ptrObj->velocidad);
        actual = actual->sig;
    }
}
