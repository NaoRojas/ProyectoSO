ejecutar: compilar
	@./proyecto
compilar: Main
	
Main: Puente.o PuntosCardinales.o Auto.o Main.o
	@gcc -o proyecto Main.o Puente.o PuntosCardinales.o Auto.o
Main.o: Main.c Puente.c PuntosCardinales.c Auto.c
	@gcc -c Main.c -lpthread
Auto.o: Auto.c
	@gcc -c Auto.c -lpthread
PuntosCardinales.o: PuntosCardinales.c
	@gcc -c PuntosCardinales.c -lpthread
Puente.o: Puente.c PuntosCardinales.c
	@gcc -c Puente.c -lpthread
clean:
	@rm -f proyecto *.o

