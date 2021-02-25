#include <stdio.h>
#include <string.h>
#include "gimnasio_y_protagonista.h"

#define ENTRENADOR 'E'
#define FORMATO_ENTRENADOR ";%49[^\n]\n"

#define POKEMON 'P'
#define FORMATO_POKEMON ";%49[^;];%i;%i;%i\n"

#define LIDER 'L'
#define GIMNASIO 'G'
#define FORMATO_GIMNASIO ";%49[^;];%i;%i\n"


personaje_t* protagonista_crear(char ruta[100]){

    FILE* archivo_protagonista = fopen(ruta, "r");
    if (!archivo_protagonista){
        printf("Error al abrir el archivo del protagonista.\n");
        return NULL;
    }
    /* PERSONAJE */
    pokemon_t* p_pokemon = NULL;
    personaje_t* p_personaje = NULL;

    char letra = (char)fgetc(archivo_protagonista);
    if (letra != ENTRENADOR){
        fclose(archivo_protagonista);
        return NULL;
    }

    personaje_t personaje;
    int leidos = fscanf(archivo_protagonista, FORMATO_ENTRENADOR, personaje.nombre);
    if (leidos != 1){
        fclose(archivo_protagonista);
        return NULL;
    }

 
    /* ENCUENTRO PRIMER POKEMON */
    pokemon_t pokemon;
    letra = (char)fgetc(archivo_protagonista);
    //printf("Letra leida: %c\n", letra);

    if (letra != POKEMON){
        //printf("Error al cargar los pokemones del protagonista.\n");
        fclose(archivo_protagonista);
        return NULL;
    }else{
        leidos = fscanf(archivo_protagonista, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            printf("Error al cargar los datos de los pokemones.\n");
            fclose(archivo_protagonista);
            return NULL;
        }
        pokemon.nivel = 0;
        
        p_pokemon = malloc(sizeof(pokemon_t));
        if (!p_pokemon){
            //printf("ERRRORRRRRR\n\n\n");
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
            pokemon.nivel = 0;
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
        //printf("Error\n");
        fclose(archivo_gimnasio);
        return NULL;
    }
    
    //printf("%s, dificultad: %i, puntero: %i, leidos: %i\n", gimnasio.nombre, gimnasio.dificultad, gimnasio.puntero_a_combate, leidos);

    letra = (char)fgetc(archivo_gimnasio);
    if (letra != LIDER){
        printf("Error al cargar el lider de gimnasio.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }

    entrenador_t entrenador_lider;
    leidos = fscanf(archivo_gimnasio, FORMATO_ENTRENADOR, entrenador_lider.nombre);
    if (leidos != 1){
        printf("Error al cargar el lider de gimnasio. Mas de 1 dato de entrada.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }

    letra = (char)fgetc(archivo_gimnasio);
    if (letra != POKEMON){
        printf("Error al cargar el pokemon del lider de gimnasio.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon_t pokemon;
    leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
    if (leidos != 4){
        printf("Error al cargar los dartos del pokemon del lider\n");
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon.nivel = 0;

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
    bool error = false;
    while (letra == POKEMON && !error){
        leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            error = true;
        } else{
            pokemon.nivel = 0;
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
    if (letra != ENTRENADOR){
        printf("Error al cargar entrenador en gimnasio.\n");
        gimnasio_destruir(p_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }

    entrenador_t* p_entrenador;
    while(letra == ENTRENADOR){
    /* NO necesariamente porque quiza hay un gimnasio sin entrenadoires, solo LIDER?*/    
        entrenador_t entrenador;
        leidos = fscanf(archivo_gimnasio, FORMATO_ENTRENADOR, entrenador.nombre);
        if (leidos != 1){
            printf("Error de formato al cargar entrenador de gimnasio.\n");
            fclose(archivo_gimnasio);
            return NULL;
        }

        letra = (char)fgetc(archivo_gimnasio);
        if (letra != POKEMON){
            printf("Error. Deberia encontrar un pokemon para el entrenador.\n");
            gimnasio_destruir(p_gimnasio);
            fclose(archivo_gimnasio);
            return NULL;
        }

        //Ya tengo un pokemon_t pokemon; lo reutilizo.
        leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            printf("Error\n");
            gimnasio_destruir(p_gimnasio);
            fclose(archivo_gimnasio);
            return NULL;
        }
        pokemon.nivel = 0;
        
        p_entrenador = malloc(sizeof(entrenador_t));
        if (!p_entrenador){
            printf("Error al crear el entrenador de gimnasio en el heap. Devuelvo hasta lo que llegue a cargar.");
            gimnasio_destruir(p_gimnasio);
            return p_gimnasio;
        }
        
        p_pokemon = malloc(sizeof(pokemon_t));
        if (!p_entrenador){
            printf("Error al crear el entrenador de gimnasio en el heap. Devuelvo hasta lo que llegue a cargar.");
            gimnasio_destruir(p_gimnasio);
            return p_gimnasio;
        }
        
        *p_entrenador = entrenador;
        *p_pokemon = pokemon;
        p_entrenador->pokemones = lista_crear();
        if (!(p_entrenador->pokemones)){
            gimnasio_destruir(p_gimnasio);
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
                pokemon.nivel = 0;
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


void pokemon_destruir(pokemon_t* pokemon){
    if (!pokemon) return;
    free(pokemon);
}

void protagonista_destruir(personaje_t* personaje){
    if (!personaje) return;
    pokemon_t* pokemon;
    while (!lista_vacia(personaje->pokemon_obtenidos)){
        pokemon = lista_ultimo(personaje->pokemon_obtenidos);
        pokemon_destruir(pokemon);
        lista_borrar(personaje->pokemon_obtenidos); //El lista_borrar borra el elemento en la ultima posicion;
    }
    lista_destruir(personaje->pokemon_obtenidos);
    lista_destruir(personaje->pokemon_para_combatir);
    free(personaje);
}


void entrenador_destruir(entrenador_t* entrenador){
    if (!entrenador) return;
    pokemon_t* pokemon;
    while(!lista_vacia(entrenador->pokemones)){
        pokemon = lista_ultimo(entrenador->pokemones);
        pokemon_destruir(pokemon);
        lista_borrar(entrenador->pokemones); //El lista_borrar borra el elemento en la ultima posicion;
    } 
    lista_destruir(entrenador->pokemones);
    free(entrenador);
}

void entrenadores_destruir(lista_t* lista_entrenadores){
    if (!lista_entrenadores) return;
    entrenador_t* entrenador;

    while(!lista_vacia(lista_entrenadores)){
        entrenador = lista_ultimo(lista_entrenadores);
        entrenador_destruir(entrenador); 
        lista_borrar(lista_entrenadores); //El lista_borrar borra el elemento en la ultima posicion;
    }
    lista_destruir(lista_entrenadores);
}

void gimnasio_destruir(gimnasio_t* gimnasio){
    if (!gimnasio) return;

    entrenador_destruir(gimnasio->lider);
    entrenadores_destruir(gimnasio->entrenadores);

    free(gimnasio);    
}

int insertar_gimnasio(heap_t* heap_gimnasios){
    char ruta[50] = "Gimnasios/gimnasio_1.txt";
    /*
    printf("Ingrese la ruta del archivo del gimnasio que desea agregar: ");
    char ruta[MAX_RUTA];
    scanf(" %s", ruta);
    */
    gimnasio_t* gimnasio = gimnasio_crear(ruta);
    if (!gimnasio) return -1;
    if (heap_insertar_elemento(heap_gimnasios, gimnasio) == 0){
        printf("El %s ha sido añadido con exitosamente.\n", gimnasio->nombre);
        //gimnasio_mostrar(gimnasio);
        return 0;
    }
    printf("Error al insertar gimnasio en el heap.\n\n");
    return -1;
}

int agregar_personaje(juego_t* juego){
    char ruta[50] = "Protagonista/protagonista.txt";
    /*
    printf("Ingrese la ruta del archivo del protagonista que desea cargar: ");
    char ruta[MAX_RUTA];
    scanf(" %s", ruta);
    */
    personaje_t* protagonista = protagonista_crear(ruta);
    if (!protagonista){
        printf("Error al cargar el protagonista.\n");
        return -1;
    } 
    juego->protagonista = protagonista;
    printf("El protagonista ha sido cargado con exito.\n\n");
    return 0;
}


void entrenador_mostrar_pokemon(entrenador_t* entrenador){
    if (!entrenador) return;
    pokemon_t* pokemon;
    lista_iterador_t* iterador = lista_iterador_crear(entrenador->pokemones);
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf("%-20s %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);

}


void gimnasio_mostrar(gimnasio_t* gimnasio){
    if (!gimnasio) return;
    pokemon_t* pokemon;

    printf("GIMNASIO: %s\nLIDER: %s\nDIFICULTAD: %i\n TIPO DE COMBATE: %i\n", gimnasio->nombre, gimnasio->lider->nombre, gimnasio->dificultad, gimnasio->puntero_a_combate);
    
    //LIDER
    lista_iterador_t* iterador = lista_iterador_crear(gimnasio->lider->pokemones);
    printf("\nLider: %s \n", gimnasio->lider->nombre);
    printf("%-20s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf("%-20s %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);

    //ENTRENADORES
    entrenador_t* entrenador;
    iterador = lista_iterador_crear(gimnasio->entrenadores);
    while (lista_iterador_tiene_siguiente(iterador)){
        entrenador = (entrenador_t*)lista_iterador_elemento_actual(iterador);
        printf("\n%-20s\n", entrenador->nombre);
        entrenador_mostrar_pokemon(entrenador);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);

    printf("\n\n");
}

void protagonista_mostrar(personaje_t* protagonista){
    if (!protagonista) return;
    pokemon_t* pokemon;
    printf("\nProtagonista: %s \n", protagonista->nombre);

    /* EQUIPO */
    lista_iterador_t* iterador = lista_iterador_crear(protagonista->pokemon_para_combatir);
    printf("\nPokemones en el equipo: \n");
    printf("%-20s %-5s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF", "LVL");
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf("%-20s %-5i  %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->nivel);
        //printf("-Pokemon: %s\n", pokemon->nombre);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);


    /*  OBTENIDOS */
    
    lista_iterador_t* it = lista_iterador_crear(protagonista->pokemon_obtenidos);
    printf("\nPokemones obtenidos: \n");
    printf("%-20s %-5s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF", "LVL");
    while (lista_iterador_tiene_siguiente(it)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(it);
        printf("%-20s %-5i  %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->nivel);
        lista_iterador_avanzar(it);
    }
    lista_iterador_destruir(it);

    printf("\n\n");
}


void cargar_tipo_batalla(funcion_batalla* vector){
    vector[0] = &funcion_batalla_1;
    vector[1] = &funcion_batalla_2;
    vector[2] = &funcion_batalla_3;
    vector[3] = &funcion_batalla_4;
    vector[4] = &funcion_batalla_5;
}


bool pokemon_en_lista(lista_t* lista, pokemon_t* pokemon){
    bool devolver = false;
    if (lista && pokemon){
        pokemon_t* pokemon_lista;
        lista_iterador_t* iterador = lista_iterador_crear(lista);
        while (lista_iterador_tiene_siguiente(iterador)){
            pokemon_lista = (pokemon_t*)lista_iterador_elemento_actual(iterador);
            if (pokemon_lista == pokemon) devolver = true;
            lista_iterador_avanzar(iterador);
        }
        lista_iterador_destruir(iterador);
    }
    return devolver;
}


bool mostrar_pokemon(void* pokemon, void* contador){ //Pongo el contador para que no llore nomas.
    if (pokemon)
        printf("%-20s %-5i  %-5i %-5i %-5i\n", ((pokemon_t*)pokemon)->nombre, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa, ((pokemon_t*)pokemon)->nivel);
    return true;
}

bool mostrar_id_pokemon(void* pokemon, void* contador){
    if (pokemon && contador)
        printf("[%-i]   %-20s %-5i  %-5i %-5i %-5i\n", (*(int*)contador)++, ((pokemon_t*)pokemon)->nombre, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa, ((pokemon_t*)pokemon)->nivel);
    return true;
}

void mostrar_info_combate(pokemon_t* pkm1, pokemon_t* pkm2){
    if (pkm1 && pkm2){
        printf("\n%-20s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
        printf("%-20s %-5i %-5i %-5i \n", pkm1->nombre, pkm1->velocidad, pkm1->ataque, pkm1->defensa);
        printf("            VS\n");
        printf("%-20s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
        printf("%-20s %-5i %-5i %-5i \n\n", pkm2->nombre, pkm2->velocidad, pkm2->ataque, pkm2->defensa);
    }
}


void cambio_pokemon(personaje_t* personaje){
    if (!personaje) return;
    char continuar;
    printf("\n%s realizara un cambio de pokemones!\n", personaje->nombre);
    int i = 1;
    int j = 1;
    printf("\n      Pokemones en el EQUIPO de %s\n", personaje->nombre);
    printf("%-4s %-20s %-5s %-5s %-5s %-5s\n", " ID", " POKEMON", " VEL", "  ATK", "  DEF", " LVL");
    lista_con_cada_elemento(personaje->pokemon_para_combatir, &mostrar_id_pokemon, (void*)&i);

    printf("\n      Pokemones EN CAJA de %s\n", personaje->nombre);
    printf("%-20s %-5s %-5s %-5s %-5s\n", " POKEMON", "VEL", "ATK", "DEF", "LVL");
    lista_con_cada_elemento(personaje->pokemon_obtenidos, &mostrar_pokemon, NULL);

    printf("\nIngrese el ID del pokemon (DEL EQUIPO) que desea cambiar. (0 en caso de querer salir): ");
    size_t id_equipo = 0;
    scanf(" %lu", &id_equipo);
    while (id_equipo > MAX_EQUIPO){
        printf("\nEl numero ingresado sobrepasa el nro de ID de los pokemones en el equipo.\n");
        printf("Ingrese el ID del pokemon que desea cambiar. (0 en caso de querer salir): ");
        scanf(" %lu", &id_equipo);
    }
    if (id_equipo == 0) return;
    /*
    if (id_equipo == 0) {
        printf("Esta a punto de salir del menu de cambio. Presione (C) si desea continuar: ");
        scanf(" %c", &continuar);
        if (continuar != 'C') return;
    }*/ //ME da paja hacer que vuelva a preguntar el id.

    printf("\n      Pokemones EN CAJA (con los que cambiar) de %s\n", personaje->nombre);
    printf("%-4s %-20s %-5s %-5s %-5s %-5s\n", " ID", " POKEMON", " VEL", "  ATK", "  DEF", " LVL");
    lista_con_cada_elemento(personaje->pokemon_obtenidos, &mostrar_id_pokemon, (void*)&j);
    pokemon_t* pokemon_equipo = (pokemon_t*)(lista_elemento_en_posicion(personaje->pokemon_para_combatir, id_equipo-1));
    //printf("\nPor que PKMN desea reemplazar a %s?\n", pokemon_equipo->nombre);
    printf("Ingrese el ID del pokemon (DE LA CAJA) con el que desea reemplazar a %s. (0 en caso de querer salir): ", pokemon_equipo->nombre);

    size_t id_obtenidos = 0;
    scanf(" %lu", &id_obtenidos);
    if (id_equipo == 0) return;
    while (id_obtenidos > lista_elementos(personaje->pokemon_obtenidos) || pokemon_en_lista(personaje->pokemon_para_combatir, lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1)) ){
        if (id_obtenidos > lista_elementos(personaje->pokemon_obtenidos) && id_obtenidos <= MAX_EQUIPO ){
            printf("\nEl numero de ID ingresado es invalido. NO pertenece a un pokemon con el que sea valido intercambiar.\n");
        }else if (pokemon_en_lista(personaje->pokemon_para_combatir, lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1))){
            printf("\n%s ya esta en tu equipo!\n", ((pokemon_t*)lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1))->nombre);
        }else if (id_obtenidos > lista_elementos(personaje->pokemon_obtenidos)){
            printf("\nEl numero de ID ingresado sobrepasa el maximo nro de ID de los pokemones obtenidos.\n");
        }
        printf("Ingrese el ID del pokemon con el que reemplazar a %s. (0 en caso de querer salir): ", pokemon_equipo->nombre);
        scanf(" %lu", &id_obtenidos);
    }
    if (id_equipo == 0) return;
    lista_borrar_de_posicion(personaje->pokemon_para_combatir, id_equipo-1);
    lista_insertar_en_posicion(personaje->pokemon_para_combatir, lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1), id_equipo-1);
    pokemon_t* pokemon_obtenido = (pokemon_t*)(lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1));
    printf("\nHaz cambiado a %s por %s EXITOSAMENTE!\n", pokemon_equipo->nombre, pokemon_obtenido->nombre);
    printf("\n¿Desea continuar haciendo cambios en el equipo?\n(C)--> para continuar\n(Otra letra)--> para salir\n");
    printf("Respuesta: ");
    scanf(" %c", &continuar);
    if (continuar == 'c' || continuar == 'C')
        cambio_pokemon(personaje);
    return;
    








}