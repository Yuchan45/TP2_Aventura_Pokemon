#include <stdio.h>
#include <string.h>
#include "juego.h"

#define ENTRENADOR 'E'
#define FORMATO_ENTRENADOR ";%49[^\n]\n"

#define POKEMON 'P'
#define FORMATO_POKEMON ";%49[^;];%i;%i;%i\n"

#define LIDER 'L'
#define GIMNASIO 'G'
#define FORMATO_GIMNASIO ";%49[^;];%i;%i\n"


personaje_t* protagonista_crear(char ruta[100]){
    pokemon_t* p_pokemon;
    personaje_t* p_personaje;

    FILE* archivo_protagonista = fopen(ruta, "r");
    if (!archivo_protagonista){
        printf("Error al abrir el archivo del protagonista.\n");
        return NULL;
    }
    /* PERSONAJE */
    char letra = (char)fgetc(archivo_protagonista);
    //printf("Letra leida: %c\n", letra);
    
    if (letra != ENTRENADOR){
        //printf("Error al cargar el protagonista. Letra inicial invalida.\n");
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
    //printf("Protagonista: %s\n\n", personaje.nombre);
 
    /* ENCUENTRO PRIMER POKEMON */
    pokemon_t pokemon;
    letra = (char)fgetc(archivo_protagonista);
    //printf("Letra leida: %c\n", letra);

    if (letra != POKEMON){
        printf("Error al cargar los pokemones del protagonista.\n");
        fclose(archivo_protagonista);
        return NULL;
    }else{
        leidos = fscanf(archivo_protagonista, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            printf("Error al cargar los datos de los pokemones.\n");
            fclose(archivo_protagonista);
            return NULL;
        }
        //printf("POKEMON: %s, VEL: %i, ATK: %i, DEF: %i\n", pokemon.nombre, pokemon.velocidad, pokemon.ataque, pokemon.defensa);
        
        p_pokemon = malloc(sizeof(pokemon_t));
        if (!p_pokemon){
            fclose(archivo_protagonista);
            return NULL;
        }
        p_personaje = malloc(sizeof(personaje_t));
        if (!p_personaje){
            fclose(archivo_protagonista);
            if (p_pokemon) free(p_pokemon); 
            free(p_pokemon);
            return NULL;
        }
        /* INICIALIZACION DE LA ESTRUCTURA (Y agregando el 1º pkmn)*/
        
        *p_pokemon = pokemon;
        *p_personaje = personaje;
        p_personaje->pokemon_para_combatir = lista_crear();
        if (!p_personaje->pokemon_para_combatir){
            //if (p_pokemon) free(p_pokemon);
            //if (p_personaje) free(p_personaje);
            free(p_pokemon);
            free(p_personaje);
            fclose(archivo_protagonista);
            return NULL;
        }
        p_personaje->pokemon_obtenidos = lista_crear();
        if (!p_personaje->pokemon_obtenidos){
            //if (p_pokemon) free(p_pokemon);
            //if (p_personaje) free(p_personaje);
            free(p_pokemon);
            if (p_personaje->pokemon_para_combatir) lista_destruir(p_personaje->pokemon_para_combatir);
            free(p_personaje);
            fclose(archivo_protagonista);
            return NULL;
        }

        //printf("Agrego a la lista de obtenidos a: %s\n", p_pokemon->nombre);
        lista_insertar(p_personaje->pokemon_obtenidos, p_pokemon);
        p_pokemon = NULL;
    }
    /* AGREGAR EL RESTO DE LOS POKEMONS */

    letra = (char)fgetc(archivo_protagonista);
    bool error = false;
    while (letra == POKEMON && !error){
        leidos = fscanf(archivo_protagonista, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            error = true;
        } else{
            p_pokemon = malloc(sizeof(pokemon_t));
            if (!p_pokemon){
                error = true;
            }else{
                *p_pokemon = pokemon;
                //printf("Agrego a la lista de obtenidos a: %s\n", p_pokemon->nombre);
                lista_insertar(p_personaje->pokemon_obtenidos, p_pokemon);
                p_pokemon = NULL;
            }
        }
        if (!error) letra = (char)fgetc(archivo_protagonista);
    }

    if (error){
        printf("Error al cargar los pokemones del protagonista.\n");
        if(p_pokemon) free(p_pokemon); 
        if(p_personaje && p_personaje->pokemon_obtenidos) lista_destruir(p_personaje->pokemon_obtenidos);
        if(p_personaje) free(p_personaje); 
        fclose(archivo_protagonista);
        return NULL;
    }

    /*  AGREGO A LOS PKMN A LA LISTA DE EQUIPO */
    lista_iterador_t* iterador = lista_iterador_crear(p_personaje->pokemon_obtenidos);
    //printf("\nRecorro la lista de pokemones obtenidos del entrenador usando el iterador externo: \n");
    while (lista_iterador_tiene_siguiente(iterador) && (lista_elementos(p_personaje->pokemon_para_combatir) < MAX_EQUIPO)){ 
        //printf(" -Agrego al pokemon: %s a la party de combate\n", (char*)(lista_iterador_elemento_actual(iterador)));
        lista_insertar(p_personaje->pokemon_para_combatir, lista_iterador_elemento_actual(iterador));
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
    //printf("pokemon party: %li\n", lista_elementos(p_personaje->pokemon_para_combatir));
    //printf("pokemon obtenidos: %li\n", lista_elementos(p_personaje->pokemon_obtenidos));
    fclose(archivo_protagonista);
    return p_personaje;
}


void pokemon_destruir(pokemon_t* pokemon){
    if (!pokemon) return;
    free(pokemon);
}

void protagonista_destruir(personaje_t* personaje){
    if (!personaje) return;
    while (!lista_vacia(personaje->pokemon_obtenidos)){
        pokemon_destruir(lista_ultimo(personaje->pokemon_obtenidos));
        lista_borrar(personaje->pokemon_obtenidos); //El lista_borrar borra el elemento en la ultima posicion;
    }
    lista_destruir(personaje->pokemon_obtenidos);
    lista_destruir(personaje->pokemon_para_combatir);
    free(personaje);
}


gimnasio_t* gimnasio_crear(char ruta[MAX_RUTA]){

    FILE* archivo_gimnasio = fopen(ruta, "r");
    if (!archivo_gimnasio){
        printf("Error al abrir el archivo gimnasio.\n");
        return NULL;
    }
    /* GIMNASIO */
    char letra = (char)fgetc(archivo_gimnasio);
    //printf("Letra leida: %c\n", letra);
    
    if (letra != GIMNASIO){
        printf("Error al cargar el gimnasio. Formato de datos de archivo incorrecto.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }

    gimnasio_t gimnasio;
    int leidos = fscanf(archivo_gimnasio, FORMATO_GIMNASIO, gimnasio.nombre, &(gimnasio.dificultad), &(gimnasio.puntero_a_combate));
    if (leidos != 3){
        printf("Eroor\n");
        fclose(archivo_gimnasio);
        return NULL;
    }
    //printf("%s, dificultad: %i, puntero: %i, leidos: %i\n", gimnasio.nombre, gimnasio.dificultad, gimnasio.puntero_a_combate, leidos);

    letra = (char)fgetc(archivo_gimnasio);
    if (letra != LIDER){
        printf("Error al cargar el gimnasio.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }

    entrenador_t entrenador_lider;
    leidos = fscanf(archivo_gimnasio, FORMATO_ENTRENADOR, entrenador_lider.nombre);
    if (leidos != 1){
        printf("ErRor\n");
        fclose(archivo_gimnasio);
        return NULL;
    }
    //printf("LIDER: %s\n", entrenador_lider.nombre);

    letra = (char)fgetc(archivo_gimnasio);
    if (letra != POKEMON){
        printf("Error al cargar el gimnasio.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon_t pokemon;
    leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
    if (leidos != 4){
        printf("Error\n");
        fclose(archivo_gimnasio);
        return NULL;
    }
    //printf("%s, vel: %i, atk: %i, def: %i\n", pokemon.nombre, pokemon.velocidad, pokemon.ataque, pokemon.defensa);
    

    /* CREO LOS STRUTS EN EL HEAP */
    gimnasio_t* p_gimnasio;
    p_gimnasio = malloc(sizeof(gimnasio_t));
    if (!p_gimnasio){
        fclose(archivo_gimnasio);
        return NULL;
    }
    entrenador_t* p_entrenador_lider;
    p_entrenador_lider = malloc(sizeof(entrenador_t));
    if (!p_entrenador_lider){
        free(p_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon_t* p_pokemon;
    p_pokemon = malloc(sizeof(pokemon_t));
    if (!p_pokemon){
        free(p_gimnasio);
        free(p_entrenador_lider);
        fclose(archivo_gimnasio);
        return NULL;
    }
    /* CARGO LOS STRUCTS EN EL HEAP */
    *p_gimnasio = gimnasio;
    *p_entrenador_lider = entrenador_lider;
    *p_pokemon = pokemon;

    p_gimnasio->lider = p_entrenador_lider;

    p_gimnasio->lider->pokemones = lista_crear();
    p_gimnasio->entrenadores = lista_crear();

    if (!(p_gimnasio->lider->pokemones)){
        free(p_gimnasio);
        free(p_entrenador_lider);
        free(p_pokemon);
        fclose(archivo_gimnasio);
    }

    lista_insertar(p_gimnasio->lider->pokemones, p_pokemon);
    p_pokemon = NULL;

    /*   AGREGO AL RESTO DE LOS PKMN   */
    letra = (char)fgetc(archivo_gimnasio);
    //printf("LETRAAAAAAAAAAAAA: %c\n\n\n", letra);
    bool error = false;
    while (letra == POKEMON && !error){
        leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            error = true;
        } else{
            p_pokemon = malloc(sizeof(pokemon_t));
            if (!p_pokemon){
                error = true;
            }else{
                *p_pokemon = pokemon;
                //printf("Agrego a la lista de obtenidos a: %s\n", p_pokemon->nombre);
                lista_insertar(p_gimnasio->lider->pokemones, p_pokemon);
                p_pokemon = NULL;
            }
        }
        if (!error) letra = (char)fgetc(archivo_gimnasio);
    }
    //printf("\n\n-CARGA DE LIDER COMPLETADA-\n");


    /*paso a leer el resto de los trainers*/
    entrenador_t* p_entrenador;
    while(letra == ENTRENADOR){
    /* NO necesariamente porque quiza hay un gimnasio sin entrenadoires, solo LIDER.
    if (letra != ENTRENADOR){
        printf("Error al cargar entrenador en gimnasio.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }*/
        //printf("LEEETRAA: %c\n", letra);
        
        entrenador_t entrenador;
        leidos = fscanf(archivo_gimnasio, FORMATO_ENTRENADOR, entrenador.nombre);
        if (leidos != 1){
            printf("Error de formato al cargar entrenador de gimnasio.\n");
            fclose(archivo_gimnasio);
            return NULL;
        }

        letra = (char)fgetc(archivo_gimnasio);
        if (letra != POKEMON){
            printf("Error. Deberia encontrar un pokemon, no otro entrenador o lo que sea.\n");
            fclose(archivo_gimnasio);
            return NULL;
        }

        //Ya tengo un pokemon_t pokemon; lo reutilizo.
        leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            printf("Error\n");
            fclose(archivo_gimnasio);
            return NULL;
        }
        
        p_entrenador = malloc(sizeof(entrenador_t));
        if (!p_entrenador){
            printf("Error al crear el entrenador de gimnasio en el heap. Devuelvo hasta lo que llegue a cargar.");
            return p_gimnasio;
        }
        
        p_pokemon = malloc(sizeof(pokemon_t));
        if (!p_entrenador){
            free(p_entrenador);
            printf("Error al crear el entrenador de gimnasio en el heap. Devuelvo hasta lo que llegue a cargar.");
            return p_gimnasio;
        }
        
        *p_entrenador = entrenador;
        *p_pokemon = pokemon;
        p_entrenador->pokemones = lista_crear();
        if (!(p_entrenador->pokemones)){
            free(p_entrenador);
            free(p_pokemon);
            fclose(archivo_gimnasio);
        }

        lista_insertar(p_entrenador->pokemones, p_pokemon);
        p_pokemon = NULL;

        /*   AGREGO AL RESTO DE LOS PKMN   */
        //printf("LEGUE ACAAA\n");
        letra = (char)fgetc(archivo_gimnasio);
        error = false;
        while (letra == POKEMON && !error){
            leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
            if (leidos != 4){
                error = true;
            } else{
                p_pokemon = malloc(sizeof(pokemon_t));
                if (!p_pokemon){
                    error = true;
                }else{
                    *p_pokemon = pokemon;
                    lista_insertar(p_entrenador->pokemones, p_pokemon);
                    p_pokemon = NULL;
                }
            }
            if (!error) letra = (char)fgetc(archivo_gimnasio);
        }

        /*APILO EL ENTRENADOR EN EL GIMNASIO*/
        lista_apilar(p_gimnasio->entrenadores, p_entrenador);
        p_entrenador = NULL;

    }
    //printf("\n\n-CARGA DE ENTRENADORES DEL GIMNASIO COMPLETADA-\n");

    fclose(archivo_gimnasio);

    return p_gimnasio;
}
