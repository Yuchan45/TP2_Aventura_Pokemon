#ifndef __POKEMON_Y_COMBATE_H__
#define __POKEMON_Y_COMBATE_H__

#include <stdbool.h>
#include "batallas.h"
#include "lista.h"


#define MAX_NOMBRE 80

/*
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 */
//typedef int (*funcion_batalla)(void*, void*);

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int velocidad;
    int defensa;
    int ataque;
    int nivel; //Representa la cantidad de mejoras.
}pokemon_t;

/*
 * Recibe un pokemon y en caso de poder, le mejora las estadisticas. En caso de no poder, noa hce nada.
 */
void mejorar_pokemon(pokemon_t* pokemon);

int tomar_pokemon_prestado(lista_t* pokemones_obtenidos, lista_t* pokemones_rival);















#endif /* __POKEMON_Y_COMBATE_H__ */