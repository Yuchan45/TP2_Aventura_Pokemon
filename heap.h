#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>
#include <stddef.h>

/*
 * Comparador de elementos. Recibe dos elementos del arbol (heap) y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es menor al
 * segundo o -1 si el primer elemento es mayor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el arbol (heap)
 * (    ) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);

typedef struct heap {
    void** vector;
    size_t tope;
    heap_comparador comparador;
    heap_liberar_elemento destructor;

}heap_t;




























#endif /* __HEAP_H__ */