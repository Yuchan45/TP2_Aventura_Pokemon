#include <string.h>
#include "juego.h"
#include "pa2mm.h"


void pruebas_protagonista_crear(){
    /*
     * Las pruebas se realizan mediante el protagonista_1.txt
     */
    personaje_t* protagonista;
    pokemon_t* pokemon;
    pa2m_afirmar(protagonista_crear("Protagonista/protagonista_invalido.txt") == NULL, "protagonista_crear devuelve NULL si se le pasa un archivo cuyo protagonista de letra diferente a E.");
    protagonista = protagonista_crear("Protagonista/protagonista.txt");
    char nombre[10] = "Yuchan";
    
    pa2m_afirmar(strcmp(protagonista->nombre, nombre) == 0, "El nombre del protagonista es correcto.");
    pa2m_afirmar(lista_elementos(protagonista->pokemon_obtenidos) == 8, "La cantidad de pkmn obtenidos y de pkmn en el archivo coinciden.");
    pa2m_afirmar(lista_elementos(protagonista->pokemon_para_combatir) <= MAX_EQUIPO, "La cantidad de pkmn de la party es menor o igual a 6.");
    
    printf("\n    POKEMONES EN PARTY:\n\n");
    printf("%-15s %5s %5s %5s\n", "POKEMON", "VEL", "ATK", "DEF");
    pokemon = lista_primero(protagonista->pokemon_para_combatir);
    printf("1- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_para_combatir);

    pokemon = lista_primero(protagonista->pokemon_para_combatir);
    printf("2- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_para_combatir);

    pokemon = lista_primero(protagonista->pokemon_para_combatir);
    printf("3- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_para_combatir);

    pokemon = lista_primero(protagonista->pokemon_para_combatir);
    printf("4- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_para_combatir);

    pokemon = lista_primero(protagonista->pokemon_para_combatir);
    printf("5- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_para_combatir);

    pokemon = lista_primero(protagonista->pokemon_para_combatir);
    printf("6- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_para_combatir);
    
    
    printf("\n    POKEMONES OBTENIDOS:\n\n");
    printf("%-15s %5s %5s %5s\n", "POKEMON", "VEL", "ATK", "DEF");
    pokemon = lista_primero(protagonista->pokemon_obtenidos);
    printf("1- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_obtenidos);

    pokemon = lista_primero(protagonista->pokemon_obtenidos);
    printf("2- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_obtenidos);

    pokemon = lista_primero(protagonista->pokemon_obtenidos);
    printf("3- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_obtenidos);

    pokemon = lista_primero(protagonista->pokemon_obtenidos);
    printf("4- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_obtenidos);

    pokemon = lista_primero(protagonista->pokemon_obtenidos);
    printf("5- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_obtenidos);

    pokemon = lista_primero(protagonista->pokemon_obtenidos);
    printf("6- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_obtenidos);

    pokemon = lista_primero(protagonista->pokemon_obtenidos);
    printf("7- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_obtenidos);

    pokemon = lista_primero(protagonista->pokemon_obtenidos);
    printf("8- %-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
    lista_desencolar(protagonista->pokemon_obtenidos);

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
        pokemon = lista_primero(p_gimnasio->lider->pokemones);
        printf("%-15s %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
        lista_desencolar(p_gimnasio->lider->pokemones);
    }
    lista_iterador_destruir(iterador);

    //ENTRENADORES

    entrenador_t* p_entrenador = lista_primero(p_gimnasio->entrenadores);
    iterador = lista_iterador_crear(p_entrenador->pokemones);
    printf("\nEntrenador: %s \n", p_entrenador->nombre);

    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pokemon = lista_primero(p_entrenador->pokemones);
        //printf("POKEMON: %s\n", pokemon->nombre);
        printf("%-15s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
        printf("%-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
        lista_desencolar(p_entrenador->pokemones);
    }
    lista_iterador_destruir(iterador);

    
    lista_desencolar(p_gimnasio->entrenadores);
    p_entrenador = lista_primero(p_gimnasio->entrenadores);
    iterador = lista_iterador_crear(p_entrenador->pokemones);
    printf("\nEntrenador: %s \n", p_entrenador->nombre);
    
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pokemon = lista_primero(p_entrenador->pokemones);
        printf("%-15s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
        printf("%-15s %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
        lista_desencolar(p_entrenador->pokemones);
    }
    lista_iterador_destruir(iterador);
    
}


int main(){
    pa2m_nuevo_grupo("PRUEBAS PROTAGONISTA_CREAR()");
    pruebas_protagonista_crear();

    pa2m_nuevo_grupo("PRUEBAS GIMNASIO_CREAR()");
    pruebas_gimnasio_crear();

    
}