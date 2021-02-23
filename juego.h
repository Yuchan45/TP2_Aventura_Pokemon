#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "stdlib.h"
#include "heap.h"
#include "lista.h"
#include "batallas.h" //Aca esta el pokemon_t

#define MAX_NOMBRE 80
#define MAX_RUTA 150
#define MAX_EQUIPO 6

typedef struct juego{
    
    personaje_t* personaje_principal;
    heap_t* gimnasios;
    bool simular;
}juego_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    lista_t* pokemon_para_combatir;
    lista_t* pokemon_obtenidos;
}personaje_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* pokemones;
}entrenador_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    int puntero_a_combate;
    entrenador_t* lider;
    lista_t* entrenadores; //Pila de entrenadores.
}gimnasio_t;


gimnasio_t* gimnasio_crear(char ruta[MAX_RUTA]);

personaje_t* protagonista_crear(char ruta[MAX_RUTA]);

/*
 * Recibe un pokemon y se encarga de liberarlo.
 */
void pokemon_destruir(pokemon_t* pokemon);

/*
 * Recibe un personaje protagonista (NO ENTRENADOR) y se encarga de liberar toda la memoria que utiliza.
 */
void protagonista_destruir(personaje_t* personaje);

/*
 * Recibe un gimnasio y libera la memoria que utiliza.
 */
void gimnasio_destruir(gimnasio_t* gimnasio);

/*
 * Recibe un entrenador (por ej, un lider) y libera la memoria que ocupa.
 */
void entrenador_destruir(entrenador_t* entrenador);

/*
 * Recibe una lista de entrenadores y la libera.
 */
void entrenadores_destruir(lista_t* lista_entrenadores);


#endif /* __JUEGO_H__ */