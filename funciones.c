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
/*
int consultarTLB(int numeroPagina, int** tlb){
	for(int i = 0; i < 16; i++){
		if(tlb[i][0] == numeroPagina){
			return tlb[i][0];
		}
	}
	return -1;
}

void actualizarTLB(int numeroPagina, int frame, int** tlb, int siguiente, int anterior){
	if(siguiente == -1){
		siguiente = 0;
		anterior = 0;
		tlb[anterior][0] = numeroPagina;
		tlb[anterior][1] = frame;
	}
	else{
		siguiente = (siguiente + 1) % 16;
		anterior = (anterior + 1) % 16;
		tlb[anterior][0] = numeroPagina;
		tlb[anterior][1] = frame;
	}
	return;
}
*/
