#include <stdio.h>
#include <stdbool.h>
#include "menus.h"

/*
 * Devuelve:
 * 1 si el primer gimnasio es menor
 * -1 si el segundo gimnasio es menor
 * 0 si son de igual dificultad
 */
int comparador(void* gimnasio1, void* gimnasio_2){
    gimnasio_t* gim_1 = (gimnasio_t*)gimnasio1;
    gimnasio_t* gim_2 = (gimnasio_t*)gimnasio_2;

    if(gim_1->dificultad < gim_2->dificultad)
        return 1;
    else if(gim_1->dificultad > gim_2->dificultad)
        return -1;
    else
        return 0;
}

void destructor_de_gimnasio(void* gimnasio){
    gimnasio_destruir(gimnasio);
}

int main(){
    juego_t juego;
    juego.protagonista = NULL;
    juego.simular = false;
    cargar_tipo_batalla(juego.tipo_batalla);
    juego.gimnasios = heap_crear(&comparador, &destructor_de_gimnasio);
    if (!juego.gimnasios){
        printf("Error al cargar el juego. Reintente pls.\n");
        return 0;
    } 

    //agregar_personaje(&juego); //PA AGILIZAR (dsp hay que descomentar el agregar pj y insertar gim)!!
    //insertar_gimnasio(juego.gimnasios); //PA AGILIZAR
    //menu_gimnasio(&juego);

    menu_inicio(&juego);
    return 0;
}