#include <string.h>
#include "gimnasio_y_protagonista.h"
#include "pa2mm.h"


void pruebas_protagonista_crear(){
    /*
     * Las pruebas se realizan mediante el protagonista_1.txt
     */
    personaje_t* protagonista;
    pa2m_afirmar(protagonista_crear("Enunciados/2020_2C_TP2_Algo2.pdf") == NULL, "protagonista_crear devuelve NULL si se le pasa un archivo que no es txt.");
    pa2m_afirmar(protagonista_crear("Protagonista/protagonista_invalido.txt") == NULL, "protagonista_crear devuelve NULL si se le pasa un archivo cuyo protagonista de letra diferente a E.");
    pa2m_afirmar(protagonista_crear("Protagonista/protagonista_invalido_2.txt") == NULL, "protagonista_crear devuelve NULL si se le pasa un archivo cuyo protagonista no tiene PKMNs.");
    pa2m_afirmar(protagonista_crear("Gimnasios/gimnasio_1.txt") == NULL, "protagonista_crear devuelve NULL si se le pasa un archivo invalido (gimnasio).");
    protagonista = protagonista_crear("Protagonista/protagonista.txt");
    char nombre[10] = "Yuchan";
    
    pa2m_afirmar(strcmp(protagonista->nombre, nombre) == 0, "El nombre del protagonista es correcto.");
    pa2m_afirmar(lista_elementos(protagonista->pokemon_obtenidos) == 8, "La cantidad de pkmn obtenidos y de pkmn en el archivo coinciden.");
    pa2m_afirmar(lista_elementos(protagonista->pokemon_para_combatir) <= MAX_EQUIPO, "La cantidad de pkmn de la party es menor o igual a 6.");
    
    pokemon_t* pokemon;
    
    /* EQUIPO */
    lista_iterador_t* iterador = lista_iterador_crear(protagonista->pokemon_para_combatir);
    printf("\nProtagonista: %s \n", protagonista->nombre);
    printf("\nPokemones en el equipo: \n");
    printf("%-15s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf("%-15s %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        //printf("-Pokemon: %s\n", pokemon->nombre);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);


    /*  OBTENIDOS */
    
    lista_iterador_t* it = lista_iterador_crear(protagonista->pokemon_obtenidos);
    printf("\nPokemones obtenidos: \n");
    printf("%-15s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
    while (lista_iterador_tiene_siguiente(it)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(it);
        printf("%-15s %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(it);
    }
    lista_iterador_destruir(it);
    
    
    protagonista_destruir(protagonista);
}


void pruebas_gimnasio_crear(){
    gimnasio_t* p_gimnasio = gimnasio_crear("Gimnasios/gimnasio_1.txt");
    pokemon_t* pokemon;

    /****** VERIFICO QUE SE HAYA CARGADO CORRECTAMENTE *******/
    printf("GIMNASIO: %s\nLIDER: %s\nDIFICULTAD: %i, PUNTERO_COMBATE: %i\n", p_gimnasio->nombre, p_gimnasio->lider->nombre, p_gimnasio->dificultad, p_gimnasio->puntero_a_combate);
    
    //LIDER
    lista_iterador_t* iterador = lista_iterador_crear(p_gimnasio->lider->pokemones);
    printf("\nLider: %s \n", p_gimnasio->lider->nombre);
    printf("%-15s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf("%-15s %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);


    //ENTRENADOR 1
    entrenador_t* p_entrenador = lista_primero(p_gimnasio->entrenadores);
    iterador = lista_iterador_crear(p_entrenador->pokemones);
    printf("\nEntrenador: %s \n", p_entrenador->nombre);

    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf("%-15s %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);


    //ENTRENADOR 2
    p_entrenador = lista_elemento_en_posicion(p_gimnasio->entrenadores, 1);
    iterador = lista_iterador_crear(p_entrenador->pokemones);
    printf("\nEntrenador: %s \n", p_entrenador->nombre);
    
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf("%-15s %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
    

    gimnasio_destruir(p_gimnasio);
}

void pruebas_gimnasio_destruir(){
    gimnasio_t* gimnasio = gimnasio_crear("Gimnasios/gimnasio_1.txt");
    gimnasio_destruir(gimnasio);
}

void pruebas_gimnasio_mostrar(){
    gimnasio_t* gimnasio = gimnasio_crear("Gimnasios/gimnasio_1.txt");
    gimnasio_mostrar(gimnasio);
    gimnasio_destruir(gimnasio);
}


void pruebas_protagonista_mostrar(){
    personaje_t* protagonista = protagonista_crear("Protagonista/protagonista.txt");
    protagonista_mostrar(protagonista);
    protagonista_destruir(protagonista);
}

int main(){
    
    pa2m_nuevo_grupo("PRUEBAS PROTAGONISTA_CREAR()");
    pruebas_protagonista_crear();

    pa2m_nuevo_grupo("PRUEBAS GIMNASIO_CREAR()");
    pruebas_gimnasio_crear();

    pa2m_nuevo_grupo("PRUEBAS GIMNASIO_DESTRUIR()");
    pruebas_gimnasio_destruir();
    
    pa2m_nuevo_grupo("PRUEBAS GIMNASIO_MOSTRAR()");
    pruebas_gimnasio_mostrar();
    
    pa2m_nuevo_grupo("PRUEBAS PROTAGONISTA_MOSTRAR()");
    pruebas_protagonista_mostrar();

    
}