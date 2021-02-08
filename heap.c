#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *   Recibe un puntero a un vector de punteros e intercambia la posicion de 2 elementos (punteros) que se encuentran el dicho vector.
 */
void swap(void** vector, size_t posicion_1, size_t posicion_2){
    void* puntero_aux = vector[posicion_1];
    vector[posicion_1] = vector[posicion_2];
    vector[posicion_2] = puntero_aux;
}
