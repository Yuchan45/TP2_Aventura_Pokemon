#include <stdio.h>
#include <string.h>
#include "pokemon_y_combate.h"

void mejorar_pokemon(pokemon_t* pokemon){
    if (!pokemon) return;
    if (pokemon->nivel >= 63){
        printf("%s ya alcanzo el nivel de mejora maximo. Sus estadisticas ya estan al limite.\n", pokemon->nombre);
        return;
    }
    pokemon->ataque++;
    pokemon->velocidad++;
    pokemon->defensa++;
    
    pokemon->nivel++; //Le subo el lvl
    printf("Las estadisticas de %s han sido mejoradas!.\n", pokemon->nombre);
}