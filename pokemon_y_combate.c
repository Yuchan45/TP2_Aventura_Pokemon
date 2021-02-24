#include <stdio.h>
#include <string.h>
#include "pokemon_y_combate.h"

void mejorar_pokemon(pokemon_t* pokemon){
    bool mejora = false;
    if(pokemon->ataque < 63){
        pokemon->ataque++;
        mejora = true;
    }
    if(pokemon->velocidad < 63){
        pokemon->velocidad++;
        mejora = true;
    }
    if(pokemon->defensa < 63){
        pokemon->defensa++;
        mejora = true;
    }
    if(mejora)
        printf("Las habilidades de %s han sido mejoradas.\n", pokemon->nombre);
    else
        printf("Las habilidades de %s ya no pueden ser mejoradas.\n", pokemon->nombre);
}