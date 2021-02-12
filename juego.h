#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "heap.h"
#include "lista.h"
#include "batallas.h" //Aca esta el pokemon_t

typedef struct personaje{
    char nombre[50];
    lista_t* pokemones_equipo;
    lista_t* pokemones_caja;
}personaje_t;

personaje_t* crear_personaje_princial(char ruta[100]);





#endif /* __JUEGO_H__ */