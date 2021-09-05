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

//Funcion para obtener el page number a partir de una direccion virtual
int pageNumber(int dirvirtual);

//Funcion para obtener el offset a partir de una direccion virtual
int getOffset(int dirvirtual);

//Funcion para obtener la direccion fisica a partir de una direccion virtual
int direccionFisica(int dirvirtual);

