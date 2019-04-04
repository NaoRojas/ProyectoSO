#include <stdio.h>
#include <stdlib.h>

struct Direccion
{
	bool direccion; //OE 0 y EO 1
    int k_carros_e = 288;
    int pro_lle = 7;
    int tie_sem = 3;
    int vel_min = 12;
    int vel_max = 30;
    int k_veh_x_pas = 3;
    int k_amb = 40 * 288 / 100;

};
struct Direccion *Oeste_new( bool direccion, int k_carros_e, int pro_lle, int tie_sem,
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
