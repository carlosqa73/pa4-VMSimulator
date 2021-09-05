#include "funciones.h"


int pageNumber(int dirvirtual){
	return (dirvirtual >> 8); //Desplazamiento de 8 bits hacia la derecha ya que 8 son los bits de page number
}

int getOffset(int dirvirtual){
	int mask = 255; 
	return dirvirtual & mask;
}

int direccionFisica(int dirvirtual){
	int dirfisica = pageNumber(dirvirtual) + getOffset(dirvirtual);
	return dirfisica;
}
