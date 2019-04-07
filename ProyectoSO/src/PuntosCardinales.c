#include <stdio.h>
#include <stdlib.h>

struct PuntosCardinales
{
    int direccion; //OE 0 y EO 1
    int k_carros_e ;
    int pro_lle ;
    int tie_sem ;
    int vel_min ;
    int vel_max;
    int k_veh_x_pas ;
    int k_amb ;

};
/*
struct Direccion *Direccion_new( bool direccion, int k_carros_e, int pro_lle, int tie_sem,
		int vel_min, int vel_max, int k_veh_x_pas, int k_amb) {
    struct example *p = malloc(sizeof *p);
   p->direccion=direccion;
   p->k_carros_e=k_carros_e;
   p->pro_lle=pro_lle;
   p->tie_sem=tie_sem;
   p->vel_min=vel_max;
   p->k_veh_x_pas=k_veh_x_pas;
   p->k_amb=k_amb;
    return p;
}
*/
