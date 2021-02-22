#include <string.h>
#include "juego.h"
#include "pa2mm.h"

int main(){
    personaje_t* protagonista = protagonista_crear("Protagonista/protagonista.txt");
    protagonista_destruir(protagonista);
    
    printf("\n/**********TERMINE DE CARGAR AL PROTAGONISTA***********/\n");

    gimnasio_t* p_gimnasio = gimnasio_crear("Gimnasios/gimnasio_1.txt");

    /****** VERIFICO QUE SE HAYA CARGADO CORRECTAMENTE *******/
    printf("\n\n/*******VERIFICACION*******/\n");
    printf("GIMNASIO: %s\nLIDER: %s\nDIFICULTAD: %i, PUNTERO_COMBATE: %i\n", p_gimnasio->nombre, p_gimnasio->lider->nombre, p_gimnasio->dificultad, p_gimnasio->puntero_a_combate);

    lista_iterador_t* iterador = lista_iterador_crear(p_gimnasio->lider->pokemones);
    printf("\nPokemones del lider %s: \n", p_gimnasio->lider->nombre);
    while (lista_iterador_tiene_siguiente(iterador)){
        printf(" -%s\n", (char*)(lista_iterador_elemento_actual(iterador)));
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);

    iterador = lista_iterador_crear(p_gimnasio->entrenadores);
    entrenador_t* p_entrenador = lista_ultimo(p_gimnasio->entrenadores);
    printf("\nPokemones del entrenador: %s \n", p_entrenador->nombre);
    while (lista_iterador_tiene_siguiente(iterador)){
        printf(" -%s \n", (char*)(lista_iterador_elemento_actual(iterador)));
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
}