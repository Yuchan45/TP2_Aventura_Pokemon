#ifndef __POKEMON_Y_COMBATE_H__
#define __POKEMON_Y_COMBATE_H__

#include <stdbool.h>
#include "batallas.h"
#include "lista.h"

#define AZUL "\033[0;34m"
#define CYAN "\033[0;36m"
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define BLANCO "\033[0;37m"
#define VIOLETA "\033[0;35m"
#define AMARILLO "\033[0;33m"

#define MAX_NOMBRE 80

/*
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 */
typedef int (*funcion_batalla)(void*, void*);

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int velocidad;
    int defensa;
    int ataque;
    int nivel; //Representa la cantidad de mejoras.
}pokemon_t;

/*
 * Recibe un pokemon y en caso de poder, le mejora las estadisticas. En caso de no poder, no se hace nada.
 */
void mejorar_pokemon(pokemon_t* pokemon);

/*
 * Recibe dos pokemones y se encarfa de mostrar sus datos. Simulando la pelea.
 */
void mostrar_info_combate(pokemon_t* pkm1, pokemon_t* pkm2);

/*
 * Se fija si el pokemon recibido por parametro se encuentra en la lista que 
 * tambien se le pasa por paramentro.
 */
bool pokemon_en_lista(lista_t* lista, pokemon_t* pokemon);










#endif /* __POKEMON_Y_COMBATE_H__ */