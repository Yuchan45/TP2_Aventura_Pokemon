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
        //printf("Error al abrir el archivo del protagonista.\n");
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
            //printf("Error al cargar los datos de los pokemones.\n");
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
        //printf("Error al cargar los pokemones del protagonista.\n");
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
        //printf("Error al abrir el archivo gimnasio.\n");
        return NULL;
    }
    /* GIMNASIO */
    char letra = (char)fgetc(archivo_gimnasio);
    //printf("Letra leida: %c\n", letra);
    
    if (letra != GIMNASIO){
        //printf("Error al cargar el gimnasio. Formato de datos de archivo incorrecto.\n");
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
        //printf("Error al cargar el lider de gimnasio.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }

    entrenador_t entrenador_lider;
    leidos = fscanf(archivo_gimnasio, FORMATO_ENTRENADOR, entrenador_lider.nombre);
    if (leidos != 1){
        //printf("Error al cargar el lider de gimnasio. Mas de 1 dato de entrada.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }

    letra = (char)fgetc(archivo_gimnasio);
    if (letra != POKEMON){
        //printf("Error al cargar el pokemon del lider de gimnasio.\n");
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon_t pokemon;
    leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
    if (leidos != 4){
        //printf("Error al cargar los dartos del pokemon del lider\n");
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
        //printf("Error al cargar entrenador en gimnasio.\n");
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
            //printf("Error de formato al cargar entrenador de gimnasio.\n");
            fclose(archivo_gimnasio);
            return NULL;
        }

        letra = (char)fgetc(archivo_gimnasio);
        if (letra != POKEMON){
            //printf("Error. Deberia encontrar un pokemon para el entrenador.\n");
            gimnasio_destruir(p_gimnasio);
            fclose(archivo_gimnasio);
            return NULL;
        }

        //Ya tengo un pokemon_t pokemon; lo reutilizo.
        leidos = fscanf(archivo_gimnasio, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if (leidos != 4){
            //printf("Error\n");
            gimnasio_destruir(p_gimnasio);
            fclose(archivo_gimnasio);
            return NULL;
        }
        pokemon.nivel = 0;
        
        p_entrenador = malloc(sizeof(entrenador_t));
        if (!p_entrenador){
            //printf("Error al crear el entrenador de gimnasio en el heap. Devuelvo hasta lo que llegue a cargar.");
            gimnasio_destruir(p_gimnasio);
            return p_gimnasio;
        }
        
        p_pokemon = malloc(sizeof(pokemon_t));
        if (!p_entrenador){
            //printf("Error al crear el entrenador de gimnasio en el heap. Devuelvo hasta lo que llegue a cargar.");
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
        printf("\n"VERDE"El %s ha sido añadido con exitosamente."BLANCO"\n\n", gimnasio->nombre);
        //gimnasio_mostrar(gimnasio);
        return 0;
    }
    printf("\n"ROJO"Error"BLANCO" al insertar gimnasio en el heap.\n\n");
    return -1;
}

int agregar_personaje(juego_t* juego){
    char ruta[50] = "Protagonista/protagonista.txt";
    /*
    printf("Ingrese la ruta del "VERDE"archivo del protagonista"BLANCO" que desea cargar: ");
    char ruta[MAX_RUTA];
    scanf(" %s", ruta);
    */
    personaje_t* protagonista = protagonista_crear(ruta);
    if (!protagonista){
        printf("\n"ROJO"Error"BLANCO" al cargar el protagonista.\n");
        return -1;
    } 
    juego->protagonista = protagonista;
    printf("\n"VERDE"El protagonista ha sido cargado con exito."BLANCO"\n\n");
    return 0;
}

void tipo_de_combate(gimnasio_t* gimnasio){
    if (gimnasio->puntero_a_combate == 1) printf(""AMARILLO"TIPO DE COMBATE:"BLANCO" DEFENSA\n");
    if (gimnasio->puntero_a_combate == 2) printf(""AMARILLO"TIPO DE COMBATE:"BLANCO" VELOCIDAD\n");
    if (gimnasio->puntero_a_combate == 3) printf(""AMARILLO"TIPO DE COMBATE:"BLANCO" ATAQUE\n");
    if (gimnasio->puntero_a_combate == 4) printf(""AMARILLO"TIPO DE COMBATE:"BLANCO" SUMA DE ESTADISTICAS (VEL + ATK + DEF)\n");
    if (gimnasio->puntero_a_combate == 5) printf(""AMARILLO"TIPO DE COMBATE:"BLANCO" LARGO DEL NOMBRE\n");

}

void entrenador_mostrar_pokemon(entrenador_t* entrenador){
    if (!entrenador) return;
    pokemon_t* pokemon;
    lista_iterador_t* iterador = lista_iterador_crear(entrenador->pokemones);
    printf("%-20s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf(""AZUL"%-20s"BLANCO" %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);

}


void gimnasio_mostrar(gimnasio_t* gimnasio){
    if (!gimnasio) return;
    pokemon_t* pokemon;
    printf("\n...............................................\n");
    printf(""VERDE"Informacion del gimnasio: "BLANCO"\n");
    printf(""AMARILLO"GIMNASIO:"BLANCO" %s\n"AMARILLO"LIDER:"BLANCO" %s\n"AMARILLO"DIFICULTAD:"BLANCO" %i\n", gimnasio->nombre, gimnasio->lider->nombre, gimnasio->dificultad);
    tipo_de_combate(gimnasio);

    //LIDER
    lista_iterador_t* iterador = lista_iterador_crear(gimnasio->lider->pokemones);
    printf("\n"AMARILLO"Lider"BLANCO": "AZUL"%s"BLANCO" \n", gimnasio->lider->nombre);
    printf("%-20s %-5s %-5s %-5s\n", "POKEMON", "VEL", "ATK", "DEF");
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf(""AZUL"%-20s"BLANCO" %-5i  %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);

    //ENTRENADORES
    entrenador_t* entrenador;
    iterador = lista_iterador_crear(gimnasio->entrenadores);
    while (lista_iterador_tiene_siguiente(iterador)){
        entrenador = (entrenador_t*)lista_iterador_elemento_actual(iterador);
        printf("\n"AZUL"%-20s"BLANCO" \n", entrenador->nombre);
        entrenador_mostrar_pokemon(entrenador);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);

    printf("\n\n");
}

void protagonista_mostrar(personaje_t* protagonista){
    if (!protagonista) return;
    pokemon_t* pokemon;
    printf("\nProtagonista: "AZUL"%s"BLANCO" \n", protagonista->nombre);

    /* EQUIPO */
    lista_iterador_t* iterador = lista_iterador_crear(protagonista->pokemon_para_combatir);
    printf("\nPokemones en el equipo: \n");
    printf(""CYAN"%-20s "BLANCO"%-5s %-5s %-5s %-5s\n", "POKEMON", "VEL", " ATK", " DEF", "LVL");
    while (lista_iterador_tiene_siguiente(iterador)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        printf(""CYAN"%-20s"BLANCO"%-5i  %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->nivel);
        //printf("-Pokemon: %s\n", pokemon->nombre);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);


    /*  OBTENIDOS */
    
    lista_iterador_t* it = lista_iterador_crear(protagonista->pokemon_obtenidos);
    printf("\nPokemones obtenidos: \n");
    printf(""CYAN"%-20s"BLANCO" %-5s %-5s %-5s %-5s\n", "POKEMON", "VEL", " ATK", " DEF", "LVL");
    while (lista_iterador_tiene_siguiente(it)){
        pokemon = (pokemon_t*)lista_iterador_elemento_actual(it);
        printf(""CYAN"%-20s"BLANCO" %-5i  %-5i %-5i %-5i\n", pokemon->nombre, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->nivel);
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



bool mostrar_pokemon(void* pokemon, void* contador){ //Pongo el contador para que no llore nomas.
    if (pokemon)
        printf(""CYAN"%-20s"BLANCO" %-5i  %-5i %-5i %-5i\n", ((pokemon_t*)pokemon)->nombre, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa, ((pokemon_t*)pokemon)->nivel);
    return true;
}

bool mostrar_id_pokemon(void* pokemon, void* contador){
    if (pokemon && contador)
        printf(""VERDE"[%-i]"BLANCO"   %-20s %-5i  %-5i %-5i %-5i\n", (*(int*)contador)++, ((pokemon_t*)pokemon)->nombre, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa, ((pokemon_t*)pokemon)->nivel);
    return true;
}


void cambio_pokemon(personaje_t* personaje){
    if (!personaje) return;
    char continuar;
    printf("\n"VERDE"****"AZUL"%s"BLANCO" realizara un cambio de pokemones!"VERDE"****"BLANCO"", personaje->nombre);
    int i = 1;
    int j = 1;
    printf("\n"AMARILLO"Pokemones en tu EQUIPO"BLANCO"\n");
    printf(""VERDE"%-4s"BLANCO" %-20s %-5s %-5s %-5s %-5s\n", "ID", " POKEMON", " VEL", "  ATK", "  DEF", " LVL");
    lista_con_cada_elemento(personaje->pokemon_para_combatir, &mostrar_id_pokemon, (void*)&i);

    printf("\n"AMARILLO"Pokemones obtenidos"BLANCO"\n");
    printf(""BLANCO"%-20s"AZUL" %-5s %-5s %-5s %-5s"BLANCO"\n", "POKEMON", "VEL", " ATK", " DEF", "LVL");
    lista_con_cada_elemento(personaje->pokemon_obtenidos, &mostrar_pokemon, NULL);

    printf("\n"AMARILLO"Ingrese el "VERDE"ID"AMARILLO" del pokemon (DEL EQUIPO) que desea cambiar. (0 en caso de querer salir): "BLANCO"");
    size_t id_equipo = 0;
    scanf(" %lu", &id_equipo);
    while (id_equipo > MAX_EQUIPO){
        printf("\n"VERDE" -"BLANCO"El numero ingresado sobrepasa el nro de "VERDE"ID"BLANCO" de los pokemones en el equipo.\n");
        printf(""AMARILLO"Ingrese el "VERDE"ID"AMARILLO" del pokemon que desea cambiar. (0 en caso de querer salir): "BLANCO"");
        scanf(" %lu", &id_equipo);
    }
    if (id_equipo == 0) return;

    printf("\n"AMARILLO"Pokemones obtenidos (con los que cambiar)"BLANCO"\n");
    printf(""VERDE"%-4s"BLANCO" %-20s %-5s %-5s %-5s %-5s\n", "ID", " POKEMON", " VEL", "  ATK", "  DEF", " LVL");
    lista_con_cada_elemento(personaje->pokemon_obtenidos, &mostrar_id_pokemon, (void*)&j);
    pokemon_t* pokemon_equipo = (pokemon_t*)(lista_elemento_en_posicion(personaje->pokemon_para_combatir, id_equipo-1));
    //printf("\nPor que PKMN desea reemplazar a %s?\n", pokemon_equipo->nombre);
    printf("\n"AMARILLO"Ingrese el "VERDE"ID"AMARILLO" del pokemon (DE LA CAJA) con el que desea reemplazar a "CYAN"%s"BLANCO". (0 en caso de querer salir): "BLANCO"", pokemon_equipo->nombre);

    size_t id_obtenidos = 0;
    scanf(" %lu", &id_obtenidos);
    if (id_equipo == 0) return;
    while (id_obtenidos > lista_elementos(personaje->pokemon_obtenidos) || pokemon_en_lista(personaje->pokemon_para_combatir, lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1)) ){
        if (id_obtenidos > lista_elementos(personaje->pokemon_obtenidos) && id_obtenidos <= MAX_EQUIPO ){
            printf("\n"ROJO" *"AMARILLO"El numero de ID ingresado es "ROJO"invalido"AMARILLO". NO pertenece a un pokemon con el que sea valido intercambiar.\n");
        }else if (pokemon_en_lista(personaje->pokemon_para_combatir, lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1))){
            printf("\n"AMARILLO"%s ya esta en tu equipo!"BLANCO"\n", ((pokemon_t*)lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1))->nombre);
        }else if (id_obtenidos > lista_elementos(personaje->pokemon_obtenidos)){
            printf("\n"AMARILLO"El numero de ID ingresado "ROJO"sobrepasa el maximo nro de ID"AMARILLO" de los pokemones obtenidos."BLANCO"\n");
        }
        printf(""AMARILLO"Ingrese el "VERDE"ID"AMARILLO" del pokemon con el que reemplazar a "CYAN"%s"BLANCO". (0 en caso de querer salir): ", pokemon_equipo->nombre);
        scanf(" %lu", &id_obtenidos);
    }
    if (id_equipo == 0) return;
    lista_borrar_de_posicion(personaje->pokemon_para_combatir, id_equipo-1);
    lista_insertar_en_posicion(personaje->pokemon_para_combatir, lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1), id_equipo-1);
    pokemon_t* pokemon_obtenido = (pokemon_t*)(lista_elemento_en_posicion(personaje->pokemon_obtenidos, id_obtenidos-1));
    printf("\n"VERDE" * ¡Haz cambiado a "CYAN"%s"VERDE" por "CYAN"%s"VERDE" EXITOSAMENTE! * "BLANCO"\n", pokemon_equipo->nombre, pokemon_obtenido->nombre);
    printf("\n"AMARILLO"¿Desea continuar haciendo cambios en el equipo?\n"VERDE"(C)"BLANCO"--> para continuar\n"VERDE"(Otra letra)"BLANCO"--> para salir\n");
    printf(""AMARILLO"Respuesta: "BLANCO"");
    scanf(" %c", &continuar);
    if (continuar == 'c' || continuar == 'C')
        cambio_pokemon(personaje);
    return;
    
}

int tomar_pokemon_prestado(lista_t* pokemones_obtenidos, lista_t* pokemones_rival){
    //char continuar;
    int i = 1;
    printf("\n******¿Que pokemon deseas tomar prestado?******\n\n");
    printf("%-4s %-20s %-5s %-5s %-5s %-5s\n", " ID", " POKEMON", " VEL", "  ATK", "  DEF", " LVL");
    lista_con_cada_elemento(pokemones_rival, &mostrar_id_pokemon, (void*)&i);

    printf("\nIngrese el ID del pokemon rival que desee tomar prestado. (0 en caso de no querer ninguno): ");
    size_t id_rival = 0;
    scanf(" %lu", &id_rival);
    while (id_rival > lista_elementos(pokemones_rival)){
        printf("\nEl numero ingresado sobrepasa el nro de ID de los pokemones en el equipo del rival.\n");
        printf("\nIngrese el ID del pokemon rival que desee tomar prestado. (0 en caso de no querer ninguno): ");
        scanf(" %lu", &id_rival);
    }
    if (id_rival == 0) return -1;
    /*
    if (id_equipo == 0) {
        printf("Esta a punto de salir del menu de cambio. Presione (C) si desea continuar: ");
        scanf(" %c", &continuar);
        if (continuar != 'C') return;
    }*/ //ME da paja hacer que vuelva a preguntar el id.

    pokemon_t* pokemon_a_agregar = malloc(sizeof(pokemon_t));
    if (!pokemon_a_agregar) return -1;
    *pokemon_a_agregar = *(pokemon_t*)(lista_elemento_en_posicion(pokemones_rival, id_rival -1));
    lista_insertar(pokemones_obtenidos, pokemon_a_agregar);
    printf("\n%s ha sido añadido a tu equipo!\n", pokemon_a_agregar->nombre);
    return 0;
}