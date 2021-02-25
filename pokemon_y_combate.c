#include <stdio.h>
#include <string.h>
#include "pokemon_y_combate.h"

void mejorar_pokemon(pokemon_t* pokemon){
    if (!pokemon) return;
    if (pokemon->nivel >= 63){
        printf("%s ya alcanzo el nivel de mejora maximo. Sus estadisticas ya estan al limite.\n", pokemon->nombre);
        return;
    }
    printf("\n\n%s SUBE DE NIVEL!\n", pokemon->nombre);
    printf("%s\nVEL: %i +1!\nATTK: %i +1!\nDEF: %i +1!\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    pokemon->ataque++;
    pokemon->velocidad++;
    pokemon->defensa++;
    pokemon->nivel++; //Le subo el lvl
    printf("Las estadisticas de %s han sido mejoradas!.\n\n", pokemon->nombre);
}

