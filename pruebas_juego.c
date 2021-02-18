#include <string.h>
#include "juego.h"
#include "pa2mm.h"

int main(){
    lista_iterador_t* iterador;

    personaje_t* entrenador = crear_protagonista("Protagonista/protagonista.txt");
    //pokemon_t* pokemon_ptr = lista_primero(entrenador->pokemon_obtenidos);
    //printf("NOMBRE: %s, VELOCIDAD: %i, ATAQUE: %i, DEFENSA: %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    iterador = lista_iterador_crear(entrenador->pokemon_obtenidos);
    printf("Recorro la lista usando el iterador externo: \n");
    while (lista_iterador_tiene_siguiente(iterador)){
        printf("     -Elemento: %c\n", *(char*)(lista_iterador_elemento_actual(iterador)));
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
}