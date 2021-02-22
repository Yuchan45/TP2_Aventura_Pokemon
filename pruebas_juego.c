#include <string.h>
#include "juego.h"
#include "pa2mm.h"

int main(){
    personaje_t* protagonista = protagonista_crear("Protagonista/protagonista.txt");
    protagonista_destruir(protagonista);
    
    printf("\n/**********TERMINE DE CARGAR AL PROTAGONISTA***********/\n");

    gimnasio_crear("Gimnasios/gimnasio_1.txt");
}