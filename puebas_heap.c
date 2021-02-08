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

void destructor_de_gimnasios(void* gimnasio){
    if (gimnasio)
        free((gimnasio_t*)gimnasio);
}

int main(){

    pa2m_nuevo_grupo("Pruebas heap crear");

}