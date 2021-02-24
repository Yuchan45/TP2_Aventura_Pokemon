#ifndef __POKEMON_Y_COMBATE_H__
#define __POKEMON_Y_COMBATE_H__

#include <stdbool.h>
#include "batallas.h"
#include "lista.h"

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int velocidad;
    int defensa;
    int ataque;
    int nivel; //Representa la cantidad de mejoras.
}pokemon_t;

























#endif /* __POKEMON_Y_COMBATE_H__ */