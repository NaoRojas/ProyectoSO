#include <stdio.h>
#include <stdlib.h>
#include "Oeste.c"
#include "Este.c"

struct Puente
{
	Oeste ladoOeste;
	Este ladoEste;
    bool  direccion; //OE = 0, EO = 1;
    int LonPue = 10;
    Puente(bool d){ direccion =d;}

};

