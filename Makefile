pagingdemand: pagingdemand.o funciones.o
	gcc pagingdemand.o funciones.o -o pagingdemand

pagingdemand.o: pagingdemand.c funciones.h
	gcc -Wall -c pagingdemand.c -o pagingdemand.o

funciones.o: funciones.c funciones.h
	gcc -Wall -c funciones.c -o funciones.o

.PHONY: clean

clean:
	rm -rf pagingdemand *.o
