#ifndef __GIMNASIO_Y_PROTAGONISTA_H__
#define __GIMNASIO_Y_PROTAGONISTA_H__

#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "heap.h"
#include "lista.h"
#include "pokemon_y_combate.h"
#include "batallas.h" 

#define AZUL "\033[0;34m"
#define CYAN "\033[0;36m"
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define BLANCO "\033[0;37m"
#define VIOLETA "\033[0;35m"
#define AMARILLO "\033[0;33m"

#define MAX_NOMBRE 80
#define MAX_RUTA 150
#define MAX_EQUIPO 6
#define MAX_BATALLAS 5


typedef struct personaje{
    char nombre[MAX_NOMBRE];
    lista_t* pokemon_para_combatir; //lista
    lista_t* pokemon_obtenidos; //lista
}personaje_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* pokemones; //lista
}entrenador_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    int puntero_a_combate;
    entrenador_t* lider;
    lista_t* entrenadores; //Pila de entrenadores.
}gimnasio_t;

typedef struct juego{
    personaje_t* protagonista;
    heap_t* gimnasios; //heap
    bool simular;
    funcion_batalla tipo_batalla[MAX_BATALLAS];
}juego_t;

/*
 * Crea gimnasios a partir de la ruta de un archivo que recibe por parametro. Puede recibir un gimnasio por archivo como varios dentro del mismo.
 */
void gimnasio_crear(char ruta[MAX_RUTA], FILE* archivo_gimnasio, heap_t* heap_gimnasios);

/*
 * Solicita mediante un print la ruta del archivo de gimnasios. Recibe por parametro el arbol heap en donde se almacenaran los gimnasios.
 */
void insertar_gimnasio(heap_t* heap_gimnasios);

/*
 * Crea un protagonista a partir de la ruta de un archivo que recibe por parametro. DEvuelve el puntero al protagonista creado
 */
personaje_t* protagonista_crear(char ruta[MAX_RUTA]);

/*
 * Solicita la ruta del archivo protagonista, para luego crearlo y finalmente agregarlo a la estructura juego_t. 
 * Devuelve 0 en caso de exito y -1 en caso de error.
 */
int agregar_personaje(juego_t* juego);

/*
 * Carga los id de batalla (los tipos de batalla) del batalla.c en el vector recibido.
 */
void cargar_tipo_batalla(funcion_batalla id_batalla[MAX_BATALLAS]);

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

/*
 * Recibe un gimnasio y muestra a su lider, entrenadores y pokemones.
 */
void gimnasio_mostrar(gimnasio_t* gimnasio);

/*
 * Recibe un personaje y muestra sus datos y pokemones.
 */
void protagonista_mostrar(personaje_t* protagonista);

/*
 * Recibe el protagonista y se encarga de hacer una interfaz mediante la cual el usuario
 * pueda cambiar pokemones entre el equipo y los obtenidos
 */
void cambio_pokemon(personaje_t* personaje);

/*
 * Muestra por pantalla el tipo de combate que realiza dicho gimnasio.
 */
void tipo_de_combate(gimnasio_t* gimnasio);



#endif /* GIMNASIO_Y_PROTAGONISTA */