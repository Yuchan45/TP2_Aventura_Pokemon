#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Recibe un puntero a un vector de punteros e intercambia la posicion de 2 elementos (punteros) que se encuentran el dicho vector.
 */
void swap(void** vector, size_t posicion_1, size_t posicion_2){
    void* puntero_aux = vector[posicion_1];
    vector[posicion_1] = vector[posicion_2];
    vector[posicion_2] = puntero_aux;
}
/*
 * Recibe la posicion de un elemento y devuelve la posicion de su padre.
*/
size_t posicion_padre(size_t n){
    return (n-1)/ 2;
}

/*
 * Recibe la posicion de un elemento y devuelve la posicion de su hijo derecho.
*/
size_t posicion_hijo_derecho(size_t n){
    return 2*n+2;
}

/*
 * Recibe la posicion de un elemento y devuelve la posicion de su hijo izquierdo.
*/
size_t posicion_hijo_izquierdo(size_t n){
    return 2*n+1;
}

size_t heap_elementos(heap_t* heap){
    if (!heap) return 0;
    return heap->tope;
}

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){
    if (!comparador) return NULL;
    heap_t* heap = calloc(1, sizeof(heap_t));
    if(!heap) return NULL;

    heap->comparador = comparador;
    heap->destructor = destructor;
    heap->tope = 0;
    return heap;

}

void sift_up(heap_t* heap, size_t n){
    if (n==0) return;

    size_t padre = posicion_padre(n);
    int comparacion = heap->comparador(heap->vector[n], heap->vector[padre]); //1º elem < 2ºelem --> retorna 1.
    if(comparacion == 1){ 
        swap(heap->vector, n, padre);
        sift_up(heap, padre);
    }
}

/*
 * Recibe el puntero al arbol (heap) y el elemento a insertar en este.
 * Inserta el elemento en su correspondiente posicion.
 * Devuelve 0 si el elemento se inserta correctamente o -1 en caso de error.
 */

int heap_insertar_elemento(heap_t* heap, void* elemento){
    if (!heap) return -1;
    if (!heap->comparador) return -1;  

    void* vector_aux = realloc(heap->vector, sizeof(void*) * (heap->tope+1));  
    if (!vector_aux) return -1;
    heap->tope++;
    heap->vector = vector_aux;
    heap->vector[heap->tope-1] = elemento;
    //Ordenamiento

    sift_up(heap, heap->tope-1);

    return 0;
}

