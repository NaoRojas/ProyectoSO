#include <stdio.h>
#include <stdlib.h>

#include "PuntosCardinales.c"

struct Puente {
/*
    struct Direccion ladoOeste;
    struct Direccion ladoEste;
*/
    int direccion; //OE = 0, EO = 1;
    int longitud;
};

