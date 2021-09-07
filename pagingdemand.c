#include "funciones.h"

char memoria[256*256];
int indicem = 0;
int tabladePagina[256];
int buffer[256];

int main(int argc, char* argv[]){

	//Se verifica el numero de argumentos
	if(argc != 3){
		printf("Uso: ./pagingdemand input_file output_file\n");
		exit(1);
	}

	else{

		//Se inicializa la tabla de pagina
		for(int i = 0; i < 256; i++){
			tabladePagina[i] = -1; //-1 quiere decir que esta vacio en esa posicion
		}

		//Punteros utilizados para abrir, leer y escribir archivos
		char* input = argv[1];
		char* output = argv[2];
		FILE* filein;
		FILE* fileout;
		FILE* filestore;

		//Abrir el archivo de entrada, validando que si se pueda abrir.
		if((filein = fopen(input, "r")) == NULL){
			printf("No se pudo abrir el archivo. \n");
			exit(1);
		}

		//Abrir el archivo de salida, validando que se pueda abrir.
		if((fileout = fopen(output, "w")) == NULL){
			printf("No se pudo abrir el archivo.\n");
			exit(1);
		}

		//Abrir el backing store
		if((filestore = fopen("BACKING_STORE.bin", "r")) == NULL){
			printf("No se pudo abrir el archivo.\n");
			exit(1);
		}

		int direccionv;
		int direccionf;
		int offset;
		int numeroPagina;
		int frame;
		int valor;
		char linea[10];

		//Leer el archivo input linea por linea
		while(fgets(linea, sizeof(linea), filein)){
			direccionv = atoi(linea);		//Leo la linea y convierto el valor a entero
			numeroPagina = pageNumber(direccionv);	//Uso la funcion pageNumber para obtener el numero de Pagina
			offset = getOffset(direccionv);		//Uso la funcion getOffset para obtener el offset
			frame = tabladePagina[numeroPagina];	//Busco en la tabla de Pagina el frame

			if(frame != -1){ 			//Si es distinto de -1 entonces es un hit.
				direccionf = frame + offset;	//direccion fisica es la suma del frame y el offset
				valor = memoria[direccionf];	//busco en la memoria el valor, indexando la direccion fisica
			}

			else{ 					//Ocurrio un miss
				if(indicem != -1){		//Pregunto si es que la memoria esta llena

					if(fseek(filestore, numeroPagina*256, SEEK_SET) != 0){			//salto a la posicion del numero de pagina multiplicado por 256 (tamano de una entrada)
                        			fprintf(stderr, "Error al leer el almacen de respaldo.\n");	//Informo si hay error.
	                		}
        	    			if(fread(buffer, sizeof(int), 256, filestore) == 0){			//Leo 256 bytes y los guardo en un buffer temporal
                	    			fprintf(stderr, "Error al escribir en buffer.\n");		//Informo si hay error.
                   			 }

					memcpy(memoria+indicem, buffer, 256);					//Copio el contenido del buffer a la memoria fisica en la posicion del indicem

					frame = indicem;			//El frame ahora es el indice de memoria (iteracion 1 sera = 0).
					direccionf = frame + offset;		//calculo la direccion fisica
					valor = memoria[direccionf];		//obtengo el valor almacenado en esa direccion
					tabladePagina[numeroPagina] = indicem;	//actualizo la tabla de pagina en la posicion del numero de pagina y asigno el frame actual.
					if(indicem < (256*256) - 256){		//Verifico que no se trate del ultimo indice posible
						indicem = indicem + 256;	//Incremento el valor del indice
					}
					else{
						indicem = -1;			//Si es el ultimo indice posible, ahora indicem = -1, indicando que ya no se puede guardar en memoria.
					}
				}
			}

			fprintf(fileout, "Virtual address: %d | ", direccionv);
            		fprintf(fileout, "Physical address: %d | ", direccionf);
            		fprintf(fileout, "Valor: %d", valor);
            		fprintf(fileout, "\n");
		}

		fclose(filein);
        	fclose(fileout);
        	fclose(filestore);

	}

	return 0;

}
