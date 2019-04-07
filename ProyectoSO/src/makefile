compilar: Main
	
Main: Main.o Puente.o Direccion.o Auto.o
	gcc -o proyecto Main.o Puente.o Direccion.o Auto.o
Main.o: Puente.c Direccion.c Auto.c
	gcc Main.c -o Main -lpthread
Auto.o:
	gcc Auto.c -o Auto
Direccion.o:
	gcc Direccion.c -o Direccion
Puente.o: Direccion.c
	gcc Puente.c -o Puente

