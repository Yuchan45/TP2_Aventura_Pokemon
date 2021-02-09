#include "heap.h"
#include "pa2mm.h"

typedef struct gimnasio{
    char nombre;
    size_t dificultad;
}gimnasio_t;

int comparador(void* elemento_1, void* elemento_2){
    if ( ((gimnasio_t*)elemento_1)->dificultad < ((gimnasio_t*)elemento_2)->dificultad )
        return 1;
    if ( ((gimnasio_t*)elemento_1)->dificultad > ((gimnasio_t*)elemento_2)->dificultad )
        return -1;
    return 0;
}
int comparador_numeros(void* elemento_1, void* elemento_2){
    if ( (*(int*)elemento_1) < (*(int*)elemento_2) )
        return 1;
    if ( (*(int*)elemento_1) > (*(int*)elemento_2) )
        return -1;
    return 0;
}

void destructor_de_gimnasios(void* gimnasio){
    if (gimnasio)
        free((gimnasio_t*)gimnasio);
}

void probar_insertar_en_heap_numeros(){
    heap_t* heap = heap_crear(comparador, NULL);
    /*
    int a = 5, b = 3, c = 1, d = 4;
    pa2m_afirmar(heap_insertar_elemento(heap, &a) == 0, "Puedo insertar un elemento en el heap. Inserte un '5'.");
    pa2m_afirmar(heap_insertar_elemento(heap, &b) == 0, "Puedo insertar un elemento en el heap. Inserte un '3'.");
    pa2m_afirmar(comparador_numeros(heap->vector[0], &b) == 0, "El elemento '5' se inserto correctamente.");
    pa2m_afirmar(comparador_numeros(heap->vector[1], &a) == 0, "El elemento '3' se inserto correctamente.");
    */
    gimnasio_t* elemento;
    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'A';
    gimnasio->dificultad = 10;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == 0, "Puedo insertar un gimnasio en el heap. Dificultad 10.");
    elemento = heap->vector[0];
    pa2m_afirmar(elemento->dificultad == 10, "La dificultad del primer gimnasio del array es 10.");

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'B';
    gimnasio->dificultad = 5;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == 0, "Puedo insertar un gimnasio en el heap. Dificultad 5.");
    elemento = heap->vector[0];
    pa2m_afirmar(elemento->dificultad == 5, "La dificultad del primer gimnasio del array ahora es 5.");

   // printf("Elemento en la primer posicion: %li\n", elemento->dificultad);
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'C';
    gimnasio->dificultad = 1;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == 0, "Puedo insertar un gimnasio en el heap. Dificultad 1.");
    elemento = heap->vector[0];
    pa2m_afirmar(elemento->dificultad == 1, "La dificultad del primer gimnasio del array ahora es 1.");
    
   // elemento = heap->vector[0];
   // printf("Elemento en la primer posicion: %li\n", elemento->dificultad);
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'D';
    gimnasio->dificultad = 3;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == 0, "Puedo insertar un gimnasio en el heap. Dificultad 3.");
    elemento = heap->vector[0];
    pa2m_afirmar(elemento->dificultad == 1, "La dificultad del primer gimnasio del array sigue siendo 1.");
   // elemento = heap->vector[0];
   // printf("Elemento en la primer posicion: %li\n", elemento->dificultad);



    destructor_de_gimnasios(gimnasio);
    free(heap->vector);
    free(heap);
}

int main(){

    pa2m_nuevo_grupo("Pruebas heap crear");

    heap_t* heap = heap_crear(NULL, NULL);

    pa2m_afirmar(heap == NULL, "Devuelve null si no recibe comparador válido");
    heap = heap_crear(comparador, NULL);
    pa2m_afirmar(heap, "Crea el heap aunque no reciba destructor");
    pa2m_afirmar(heap_elementos(heap) == 0, "Hay 0 elementos en el heap");

    free(heap);
    pa2m_nuevo_grupo("Pruebas heap insertar");
    probar_insertar_en_heap_numeros();
}