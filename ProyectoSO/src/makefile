compilar: semaforos.o algPeterson.o alg2.o alg1.o
	
semaforos.o:
	gcc semaforos.c -o semaforos -lpthread
algPeterson.o:
	gcc algPeterson.c -o algPeterson -lpthread
alg2.o:
	gcc alg2.c -o alg2 -lpthread
alg1.o:
	gcc alg1.c -o alg1 -lpthread
semaforos: semaforos.o
	./semaforos
algPeterson: algPeterson.o
	./algPeterson
alg2: alg2.o
	./alg2
alg1: alg1.o
	./alg1

