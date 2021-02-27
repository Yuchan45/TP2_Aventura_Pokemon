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

int tomar_pokemon_prestado(lista_t* pokemones_obtenidos, lista_t* pokemones_rival){
    //char continuar;
    int i = 1;
    printf("\n"AMARILLO"******"BLANCO"¿Que pokemon deseas tomar prestado?"AMARILLO"******"BLANCO"\n\n");
    printf(""VERDE"%-4s"BLANCO" %-20s %-5s %-5s %-5s %-5s\n", "ID", " POKEMON", " VEL", "  ATK", "  DEF", " LVL");
    lista_con_cada_elemento(pokemones_rival, &mostrar_id_pokemon, (void*)&i);

    printf("\nIngrese el "VERDE"ID"BLANCO" del pokemon rival que desee tomar prestado. (0 en caso de no querer ninguno): ");
    size_t id_rival = 0;
    scanf(" %lu", &id_rival);
    while (id_rival > lista_elementos(pokemones_rival)){
        printf("\nEl numero ingresado sobrepasa el nro de "VERDE"ID"BLANCO" de los pokemones en el equipo del rival.\n");
        printf("\nIngrese el "VERDE"ID"BLANCO" del pokemon rival que desee tomar prestado. (0 en caso de no querer ninguno): ");
        scanf(" %lu", &id_rival);
    }
    if (id_rival == 0) return -1;

    pokemon_t* pokemon_a_agregar = malloc(sizeof(pokemon_t));
    if (!pokemon_a_agregar) return -1;
    *pokemon_a_agregar = *(pokemon_t*)(lista_elemento_en_posicion(pokemones_rival, id_rival -1));
    lista_insertar(pokemones_obtenidos, pokemon_a_agregar);
    printf("\n -"VERDE"%s"BLANCO" ha sido añadido a tu equipo!\n", pokemon_a_agregar->nombre);
    return 0;
}

bool mostrar_pokemon(void* pokemon, void* contador){ //Pongo el contador para que no llore nomas.
    if (pokemon)
        printf(""CYAN"%-20s"BLANCO" %-5i  %-5i %-5i %-5i\n", ((pokemon_t*)pokemon)->nombre, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa, ((pokemon_t*)pokemon)->nivel);
    return true;
}

bool mostrar_id_pokemon(void* pokemon, void* contador){
    if (pokemon && contador)
        printf(""VERDE"[%-i]"BLANCO"   %-20s %-5i  %-5i %-5i %-5i\n", (*(int*)contador)++, ((pokemon_t*)pokemon)->nombre, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa, ((pokemon_t*)pokemon)->nivel);
    return true;
}