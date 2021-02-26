#include <stdio.h>
#include <string.h>
#include "pokemon_y_combate.h"

void mejorar_pokemon(pokemon_t* pokemon){
    if (!pokemon) return;
    if (pokemon->nivel >= 63){
        printf("%s ya alcanzo el nivel de mejora maximo. Sus estadisticas ya estan al limite.\n", pokemon->nombre);
        return;
    }
    printf(""VERDE"\n********************************");
    printf("\n"BLANCO"¡"CYAN"%s"BLANCO" HA SUBIDO DE NIVEL!\n", pokemon->nombre);
    printf(""AMARILLO"VEL"BLANCO": %i +1!\n"AMARILLO"ATTK"BLANCO": %i +1!\n"AMARILLO"DEF"BLANCO": %i +1!\n", pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    pokemon->ataque++;
    pokemon->velocidad++;
    pokemon->defensa++;
    pokemon->nivel++; //Le subo el lvl
    printf(""VERDE"********************************\n\n");
    //printf(""VERDE"-Todas las estadisticas de %s han sido mejoradas!.\n\n", pokemon->nombre);
}

void mostrar_info_combate(pokemon_t* pkm1, pokemon_t* pkm2){
    if (pkm1 && pkm2){
        printf("\n"AZUL"          %-20s"BLANCO" %-5s %-5s %-5s\n", "TU POKEMON", "VEL", "ATK", "DEF");
        printf(""CYAN"          %-20s"BLANCO" %-5i %-5i %-5i \n", pkm1->nombre, pkm1->velocidad, pkm1->ataque, pkm1->defensa);
        printf(""AMARILLO"                         ¡VS!"BLANCO"\n");
        printf(""AZUL"          %-20s"BLANCO" %-5s %-5s %-5s\n", "POKEMON RIVAL", "VEL", "ATK", "DEF");
        printf(""ROJO"          %-20s"BLANCO" %-5i %-5i %-5i \n\n", pkm2->nombre, pkm2->velocidad, pkm2->ataque, pkm2->defensa);
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
