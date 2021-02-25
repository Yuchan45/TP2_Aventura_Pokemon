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

void mostrar_info_combate(pokemon_t* pkm1, pokemon_t* pkm2){
    if (pkm1 && pkm2){
        printf("\n%-20s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
        printf("%-20s %-5i %-5i %-5i \n", pkm1->nombre, pkm1->velocidad, pkm1->ataque, pkm1->defensa);
        printf("            VS\n");
        printf("%-20s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
        printf("%-20s %-5i %-5i %-5i \n\n", pkm2->nombre, pkm2->velocidad, pkm2->ataque, pkm2->defensa);
    }
}

bool pokemon_en_lista(lista_t* lista, pokemon_t* pokemon){
    bool devolver = false;
    if (lista && pokemon){
        pokemon_t* pokemon_lista;
        lista_iterador_t* iterador = lista_iterador_crear(lista);
        while (lista_iterador_tiene_siguiente(iterador)){
            pokemon_lista = (pokemon_t*)lista_iterador_elemento_actual(iterador);
            if (pokemon_lista == pokemon) devolver = true;
            lista_iterador_avanzar(iterador);
        }
        lista_iterador_destruir(iterador);
    }
    return devolver;
}
