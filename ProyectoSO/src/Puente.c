

#include "PuntosCardinales.c"

struct Puente {
    struct PuntosCardinales ladoOeste;
    struct PuntosCardinales ladoEste;
    int direccion; //OE = 0, EO = 1;
    int longitud;
};

