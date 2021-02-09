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

/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
bool heap_vacio(heap_t* heap){
    if (!heap || heap->tope == 0) return true;
    return false;
}

void* heap_obtener_raiz(heap_t* heap){
    if (!heap || !heap->vector) return NULL;
    return heap->vector[0];
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

void sift_down(heap_t* heap, size_t n){
    


}

/*
 * Elimina el elemento que se encuentra en la raiz, devulve 0 en caso de exito y -1 en caso de error.
 */
int heap_eliminar_raiz(heap_t* heap){
    if (!heap || heap->tope == 0) return -1;

    if (heap_elementos(heap) == 1){
        if(heap->destructor) heap->destructor((heap->vector[0]));
        free(heap->vector);
        heap->vector = NULL;
        heap->tope = 0;
    }else{
        void* ultimo_elemento = heap->vector[heap->tope-1];
        void* vector_aux = realloc(heap->vector, sizeof(void*) * (heap->tope - 1));
        if(!vector_aux) return -1;
        heap->vector = vector_aux;
        if(heap->destructor) heap->destructor((heap->vector[0]));
        heap->vector[0] = ultimo_elemento;
        (heap->tope)--;

        sift_down(heap, 0);
    }
    return 0;
}

