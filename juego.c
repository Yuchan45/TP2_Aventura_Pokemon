#include <stdio.h>
#include <string.h>
#include "juego.h"

#define ENTRENADOR 'E'
#define FORMATO_ENTRENADOR ";%49[^\n]\n"
#define POKEMON 'P'
#define FORMATO_POKEMON ";%49[^;];%i;%i;%i\n"


personaje_t* crear_protagonista(char ruta[100]){
    pokemon_t* p_pokemon;
    personaje_t* p_personaje;

    FILE* archivo_protagonista = fopen(ruta, "r");
    if (!archivo_protagonista){
        printf("Error al abrir el archivo del protagonista.\n");
        return NULL;
    }
    /* PERSONAJE */
    char letra = (char)fgetc(archivo_protagonista);
    printf("Letra leida: %c\n", letra);
    
    if (letra != ENTRENADOR){
        printf("Error al cargar el protagonista. Letra inicial invalida.\n");
        fclose(archivo_protagonista);
        return NULL;
    }

    personaje_t personaje;
    int leidos = fscanf(archivo_protagonista, FORMATO_ENTRENADOR, personaje.nombre);
    if (leidos != 1){
        printf("Error al cargar el nombre del protagonista.\n");
        fclose(archivo_protagonista);
        return NULL;
    }
    printf("%s\n", personaje.nombre);
 
    /* LINEAS POKEMON */
    pokemon_t pokemon;
    char letra = (char)fgetc(archivo_protagonista);
    printf("Letra leida: %c\n", letra);

    if (letra != POKEMON){
        printf("Error al cargar los pokemones del protagonista.\n");
        fclose(archivo_protagonista);
        return NULL;
    }else{
        int leidos = fscanf(archivo_protagonista, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            printf("Error al cargar los datos de los pokemones.\n");
            fclose(archivo_protagonista);
            return NULL;
        }
        p_pokemon = malloc(sizeof(pokemon_t));
        if (!p_pokemon){
            fclose(archivo_protagonista);
            return NULL;
        }
        p_personaje = malloc(sizeof(personaje_t));
        if (!p_personaje){
            fclose(archivo_protagonista);
            if (p_pokemon) free(p_pokemon); 
            return NULL;
        }
        /* INICIALIZACION DE LOS STRUCTS EN EL HEAP. */
        *p_pokemon = pokemon;
        *p_personaje = personaje;
        p_personaje->pokemon_para_combatir = lista_crear();
        if (!p_personaje->pokemon_para_combatir){
            if (p_pokemon) free(p_pokemon);
            if (p_personaje) free(p_personaje);
            fclose(archivo_protagonista);
            return NULL;
        }
        p_personaje->pokemon_obtenidos = lista_crear();
        if (!p_personaje->pokemon_obtenidos){
            if (p_pokemon) free(p_pokemon);
            if (p_personaje) free(p_personaje);
            if (p_personaje->pokemon_para_combatir) lista_destruir(p_personaje->pokemon_para_combatir);
            fclose(archivo_protagonista);
            return NULL;
        }



    }





    return NULL;
}