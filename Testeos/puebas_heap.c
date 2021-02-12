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

void probar_heap_obtener_raiz(){
    heap_t* heap = heap_crear(comparador, destructor_de_gimnasios);

    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'A';
    gimnasio->dificultad = 10;
    printf("Inserto el gimnasio A de dificultad 10\n");
    heap_insertar_elemento(heap, gimnasio);
    printf("La raiz actual es: %c, de dificultad: %li\n", ((gimnasio_t*)heap_obtener_raiz(heap))->nombre, ((gimnasio_t*)heap_obtener_raiz(heap))->dificultad);

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'B';
    gimnasio->dificultad = 5;
    printf("Inserto el gimnasio B de dificultad 5\n");
    heap_insertar_elemento(heap, gimnasio);
    printf("(Ahora la raiz correcta deberia ser 5)\n");
    printf("La raiz actual es: %c, de dificultad: %li\n", ((gimnasio_t*)heap_obtener_raiz(heap))->nombre, ((gimnasio_t*)heap_obtener_raiz(heap))->dificultad);

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'C';
    gimnasio->dificultad = 1;
    printf("Inserto el gimnasio C de dificultad 1\n");
    heap_insertar_elemento(heap, gimnasio);
    printf("(Ahora la raiz correcta deberia ser 1)\n");
    printf("La raiz actual es: %c, de dificultad: %li\n", ((gimnasio_t*)heap_obtener_raiz(heap))->nombre, ((gimnasio_t*)heap_obtener_raiz(heap))->dificultad);

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'D';
    gimnasio->dificultad = 3;
    printf("Inserto el gimnasio D de dificultad 3\n");
    heap_insertar_elemento(heap, gimnasio);
    printf("(Ahora la raiz correcta deberia seguir siendo D de dificultad 1)\n");
    printf("La raiz actual es: %c, de dificultad: %li\n", ((gimnasio_t*)heap_obtener_raiz(heap))->nombre, ((gimnasio_t*)heap_obtener_raiz(heap))->dificultad);

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'E';
    gimnasio->dificultad = 8;
    printf("Inserto el gimnasio E de dificultad 8\n");
    heap_insertar_elemento(heap, gimnasio);
    printf("(Ahora la raiz correcta deberia seguir siendo E de dificultad 1)\n");
    printf("La raiz actual es: %c, de dificultad: %li\n", ((gimnasio_t*)heap_obtener_raiz(heap))->nombre, ((gimnasio_t*)heap_obtener_raiz(heap))->dificultad);

    heap_destruir(heap);

}

void probar_insertar_en_heap_numeros(){
    heap_t* heap = heap_crear(comparador, destructor_de_gimnasios);
    /*
    int a = 5, b = 3, c = 1, d = 4;
    pa2m_afirmar(heap_insertar_elemento(heap, &a) == 0, "Puedo insertar un elemento en el heap. Inserte un '5'.");
    pa2m_afirmar(heap_insertar_elemento(heap, &b) == 0, "Puedo insertar un elemento en el heap. Inserte un '3'.");
    pa2m_afirmar(comparador_numeros(heap->vector[0], &b) == 0, "El elemento '5' se inserto correctamente.");
    pa2m_afirmar(comparador_numeros(heap->vector[1], &a) == 0, "El elemento '3' se inserto correctamente.");
    */
    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'A';
    gimnasio->dificultad = 10;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == 0, "Puedo insertar un gimnasio en el heap. Dificultad 10.");
    //printf("Gimnasio: %c", ((gimnasio_t*)heap_obtener_raiz(heap))->nombre);
    pa2m_afirmar(heap_vacio(heap) == false, "El heap ya NO se encuentra vacio.")
    pa2m_afirmar(((gimnasio_t*)heap_obtener_raiz(heap))->dificultad == 10, "La dificultad del primer gimnasio (valor raiz) del array es 10.");

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'B';
    gimnasio->dificultad = 5;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == 0, "Puedo insertar un gimnasio en el heap. Dificultad 5.");
    pa2m_afirmar(((gimnasio_t*)heap_obtener_raiz(heap))->dificultad == 5, "La dificultad del primer gimnasio (valor raiz) del array ahora es 5.");

   // printf("Elemento en la primer posicion: %li\n", elemento->dificultad);
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'C';
    gimnasio->dificultad = 1;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == 0, "Puedo insertar un gimnasio en el heap. Dificultad 1.");
    pa2m_afirmar(((gimnasio_t*)heap_obtener_raiz(heap))->dificultad == 1, "La dificultad del primer gimnasio (valor raiz) del array ahora es 1.");

   // printf("Elemento en la primer posicion: %li\n", elemento->dificultad);
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'D';
    gimnasio->dificultad = 3;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == 0, "Puedo insertar un gimnasio en el heap. Dificultad 3.");
    pa2m_afirmar(((gimnasio_t*)heap_obtener_raiz(heap))->dificultad == 1, "La dificultad del primer gimnasio (valor raiz) del array sigue siendo 1.");
   // printf("Elemento en la primer posicion: %li\n", elemento->dificultad);


    heap_destruir(heap);
}

void probar_heap_crear(){
    heap_t* heap = heap_crear(NULL, NULL);

    pa2m_afirmar(heap == NULL, "NO crea el heap si no recibe un comparador.");
    pa2m_afirmar(heap_vacio(heap) == true, "Como el heap es NULL, el heap se encuentra vacio");
    heap = heap_crear(comparador, NULL);
    pa2m_afirmar(heap, "Crea el heap aunque no reciba destructor");
    pa2m_afirmar(heap_vacio(heap) == true, "El heap se crea vacio (tope 0)");
    pa2m_afirmar(heap_elementos(heap) == 0, "Hay 0 elementos en el heap");

    free(heap);
}

void probar_heap_eliminar_raiz(){
    heap_t* heap = heap_crear(comparador, destructor_de_gimnasios);

    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'A';
    gimnasio->dificultad = 10;
    heap_insertar_elemento(heap, gimnasio);

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'B';
    gimnasio->dificultad = 5;
    heap_insertar_elemento(heap, gimnasio);

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'C';
    gimnasio->dificultad = 1;
    heap_insertar_elemento(heap, gimnasio);

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'D';
    gimnasio->dificultad = 3;
    heap_insertar_elemento(heap, gimnasio);

    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'E';
    gimnasio->dificultad = 8;
    heap_insertar_elemento(heap, gimnasio);
    pa2m_afirmar(heap_elementos(heap) == 5, "Hay 5 elementos en el heap de dificultades: 10, 5, 1, 3, 8");

    /*  Termine de insertar elementos  */
    printf("(El orden de eliminacion de raices en un arbol minimal deberia ser: 1, 3, 5, 8, 10)\n");
    printf("Orden en el que se eliminan las raices en un arbol minimal:\n");
    while (heap->tope != 0){
        printf("   Saco la raiz: %li\n", ((gimnasio_t*)heap->vector[0])->dificultad);
        heap_eliminar_raiz(heap);
    }

    heap_destruir(heap);

}

int main(){

    pa2m_nuevo_grupo("Pruebas heap crear");
    probar_heap_crear();
    
    pa2m_nuevo_grupo("Pruebas heap insertar");
    probar_insertar_en_heap_numeros();

    pa2m_nuevo_grupo("Pruebas heap obtener raiz");
    probar_heap_obtener_raiz();

    pa2m_nuevo_grupo("Pruebas heap eliminar raiz");
    probar_heap_eliminar_raiz();



}