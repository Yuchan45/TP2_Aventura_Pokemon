#ifndef __GIMNASIO_Y_PROTAGONISTA_H__
#define __GIMNASIO_Y_PROTAGONISTA_H__

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

typedef struct juego{
    personaje_t* protagonista;
    heap_t* gimnasios;
    bool simular;
    funcion_batalla tipo_batalla[MAX_BATALLAS];
}juego_t;

/*
 * Crea un gimnasio a partir de la ruta de un archivo que recibe por parametro. DEvuelve el puntero al gimnasio creado
 */
gimnasio_t* gimnasio_crear(char ruta[MAX_RUTA]);

/*
 * Solicita la ruta del archivo gimnasio, para luego crearlo junto con la funcion gimnasio_crear(). 
 * Y luego lo inserta un gimnasio en un heap recibido por parametro.
 */
int insertar_gimnasio(heap_t* heap_gimnasios);

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

bool mostrar_pokemon(void* pokemon, void* contador);

bool mostrar_id_pokemon(void* pokemon, void* contador);

void cambio_pokemon(personaje_t* personaje);

void tipo_de_combate(gimnasio_t* gimnasio);

/*
 * Recibe la lista de pokemones obtenidos del protagonista y la lista de pokemones del rival. 
 * Se encarga de preguntar y de tomar prestado el pokemon rival deseado.
 * Devuelve 0 en caso de exito y -1 en caso de error.
 */
int tomar_pokemon_prestado(lista_t* pokemones_obtenidos, lista_t* pokemones_rival);


#endif /* GIMNASIO_Y_PROTAGONISTA */