ejecutar: clean compilar
	./Proyecto

compilar: Puente.o PuntosCardinales.o Auto.o Main.o
	gcc -o Proyecto Main.o Puente.o PuntosCardinales.o Auto.o -lpthread

Main.o: Main.c Puente.c PuntosCardinales.c Auto.c
	@gcc -c Main.c -lpthread

Auto.o: Auto.c
	@gcc -c Auto.c

PuntosCardinales.o: PuntosCardinales.c
	@gcc -c PuntosCardinales.c

Puente.o: Puente.c PuntosCardinales.c
	@gcc -c Puente.c

clean: 
	@rm -f Proyecto *.o

