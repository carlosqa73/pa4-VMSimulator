#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>


int pageNumber(int dirvirtual){
	return (dirvirtual >> 8); //Desplazamiento de 8 bits hacia la derecha ya qe 8 son los bits de page number
}

int offset(int dirvirtual){
	int mask = 255; 
	return dirivirtual & mask;
}

int direccionFisica(int dirvirtual){
	int dirfisica = pageNumber(dirvirtual) + offset(dirvirtual);
	return dirfisica;
}


