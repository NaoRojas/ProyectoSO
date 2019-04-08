
#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    Rama dato;
    Nodo* izq;
    Nodo* der;
    Nodo() {
        izq = der = nullptr;
    }
};

struct Cola_con_Prioridad{
    struct Nodo* ppio;
    Cola_con_Prioridad(){
        ppio = null;
    }
};

/*
void enqui
*/
