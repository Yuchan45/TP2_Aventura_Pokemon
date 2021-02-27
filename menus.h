#ifndef __MENUS_H__
#define __MENUS_H__

#include <stdio.h>
#include <stdbool.h>
#include "heap.h"
#include "gimnasio_y_protagonista.h"

#define AZUL "\033[0;34m"
#define CYAN "\033[0;36m"
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define BLANCO "\033[0;37m"
#define VIOLETA "\033[0;35m"
#define AMARILLO "\033[0;33m"

#define ENTRENADOR 'E'
#define ENTRENADOR_MINUSCULA 'e'
#define AGREGAR_GIMNASIO 'A'
#define AGREGAR_GIMNASIO_MINUSCULA 'a'
#define INICIAR 'I'
#define INICIAR_MINUSCULA 'i'
#define SIMULAR 'S'
#define SIMULAR_MINUSCULA 's'
#define INFO_GIMNASIO 'G'
#define INFO_GIMNASIO_MINUSCULA 'g'
#define CAMBIAR_PKMN 'C'
#define CAMBIAR_PKMN_MINUSCULA 'c'
#define BATALLAR 'B'
#define BATALLAR_MINUSCULA 'b'
#define PROXIMO_COMBATE 'N'
#define PROXIMO_COMBATE_MINUSCULA 'n'
#define TOMAR_PRESTADO 'T'
#define TOMAR_PRESTADO_MINUSCULA 't'
#define REINTENTAR_GIMNASIO 'R'
#define REINTENTAR_GIMNASIO_MINUSCULA 'r'
#define FINALIZAR 'F'
#define FINALIZAR_MINUSCULA 'f'


/*
 * Pide un caracter por consola y repite hasta recibir un 
 * caracter solo (sin incluir los enters solos). Descarta los "GG" y los enters.
 */
char leer_letra();
/*
 *   Muestra el menu inicial del juego.
 */
void menu_inicio(juego_t* juego);
/*
 *   Muestra el menu de gimnasio.
 */
void menu_gimnasio(juego_t* juego);
/*
 *   Muestra el menu de victoria.
 */
void menu_victoria(juego_t* juego);
/*
 *   Muestra el menu de derrota.
 */
void menu_derrota(juego_t* juego);
/*
 *  Muestra un menu de combate y los detalles de este.
 */
void combate_pokemon(juego_t* juego);
/*
 *   Imprime el tipo de combate de dicho gimnasio.
 */
void tipo_de_combate_gimnasio(juego_t* juego);
/*
 *   Muestra por consola un ascii art de MAESTRO POKEMON.
 */
void eres_maestro_pokemon(juego_t* juego);






#endif /* __MENUS_H__ */