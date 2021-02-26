#include "batallas.h"
#include "pokemon_y_combate.h"
#include <string.h>
#include <stdio.h>

int funcion_batalla_1(void* pkm_1, void* pkm_2){ //Batalla de dureza.
    //if (!pkm_1 || !pkm_2) return;
    if( ((pokemon_t*)pkm_1)->defensa >= ((pokemon_t*)pkm_2)->defensa )
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){ // Batalla de velocidad.
    //if (!pkm_1 || !pkm_2) return;
    if ( ((pokemon_t*)pkm_1)->velocidad >= ((pokemon_t*)pkm_2)->velocidad )
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){ //Batalla de ataque.
    //if (!pkm_1 || !pkm_2) return;
    if ( ((pokemon_t*)pkm_1)->ataque >= ((pokemon_t*)pkm_2)->ataque )
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){ //Batalla tiene mas stats generales (Suma de todas las estadisticas).
    //if (!pkm_1 || !pkm_2) return;
    int stats_pokemon_1 = ((pokemon_t*)pkm_1)->velocidad + ((pokemon_t*)pkm_1)->ataque + ((pokemon_t*)pkm_1)->defensa;
    int stats_pokemon_2 = ((pokemon_t*)pkm_2)->velocidad + ((pokemon_t*)pkm_2)->ataque + ((pokemon_t*)pkm_2)->defensa;

    if ( stats_pokemon_1 >= stats_pokemon_2)
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){ //Batalla largo de nombre(?).
    //if (!pkm_1 || !pkm_2) return;
    size_t largo_pk1 = strlen(((pokemon_t*)pkm_1)->nombre);
    size_t largo_pk2 = strlen(((pokemon_t*)pkm_2)->nombre);
    if (largo_pk1 >= largo_pk2)
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}