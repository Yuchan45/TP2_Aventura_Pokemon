#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "heap.h"
#include "lista.h"
#include "batallas.h" //Aca esta el pokemon_t

#define MAX_NOMBRE 50
#define MAX_RUTA 100

typedef struct personaje{
    char nombre[50];
    lista_t* pokemon_para_combatir;
    lista_t* pokemon_obtenidos;
}personaje_t;

personaje_t* crear_protagonista(char ruta[MAX_RUTA]);





#endif /* __JUEGO_H__ */