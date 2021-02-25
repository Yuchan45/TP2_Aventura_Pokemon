#include <stdio.h>
#include <stdbool.h>
#include "heap.h"
#include "gimnasio_y_protagonista.h"



#define ENTRENADOR 'E'
#define ENTRENADOR_MINUSCULA 'e'
#define AGREGAR_GIMNASIO 'A'
#define AGREGAR_GIMNASIO_MINUSCULA 'a'
#define INICIAR 'I'
#define INICIAR_MINUSCULA 'i'
#define SIMULAR 'S'
#define SIMULAR_MINUSCULA 's'
#define INFO_GIMNASIO 'G'
#define INFO_GIMNASIO_MINUSCULA 'g'
#define CAMBIAR_PKMN 'C'
#define CAMBIAR_PKMN_MINUSCULA 'c'
#define BATALLAR 'B'
#define BATALLAR_MINUSCULA 'b'
#define PROXIMO_COMBATE 'N'
#define PROXIMO_COMBATE_MINUSCULA 'n'
#define TOMAR_PRESTADO 'T'
#define TOMAR_PRESTADO_MINUSCULA 't'
#define REINTENTAR_GIMNASIO 'R'
#define REINTENTAR_GIMNASIO_MINUSCULA 'r'
#define FINALIZAR 'F'
#define FINALIZAR_MINUSCULA 'f'



/*
 * Devuelve:
 * 1 si el primer gimnasio es menor
 * -1 si el segundo gimnasio es menor
 * 0 si son de igual dificultad
 */
int comparador(void* gimnasio1, void* gimnasio_2){
    gimnasio_t* gim_1 = (gimnasio_t*)gimnasio1;
    gimnasio_t* gim_2 = (gimnasio_t*)gimnasio_2;

    if(gim_1->dificultad < gim_2->dificultad)
        return 1;
    else if(gim_1->dificultad > gim_2->dificultad)
        return -1;
    else
        return 0;
}

void destructor_de_gimnasio(void* gimnasio){
    gimnasio_destruir(gimnasio);
}
char leer_letra();
/*
*   imprime el menu inicial del juego.
*/
void menu_inicio(juego_t* juego);

void menu_gimnasio(juego_t* juego);

void menu_victoria(juego_t* juego);

void menu_derrota(juego_t* juego);

void combate_pokemon(juego_t* juego);

void tipo_de_combate_gimnasio(juego_t* juego);

void eres_maestro_pokemon(juego_t* juego);

//DSP BORRAR
/*
int insertar_gimnasio_2(heap_t* heap_gimnasios){
    char ruta[50] = "Gimnasios/gimnasio_2.txt";
    gimnasio_t* gimnasio = gimnasio_crear(ruta);
    if (!gimnasio) return -1;
    if (heap_insertar_elemento(heap_gimnasios, gimnasio) == 0){
        printf("El %s ha sido añadido con exitosamente.\n", gimnasio->nombre);
        //gimnasio_mostrar(gimnasio);
        return 0;
    }
    printf("Error al insertar gimnasio en el heap.\n\n");
    return -1;
}*/

int main(){
    juego_t juego;
    juego.protagonista = NULL;
    juego.simular = false;
    cargar_tipo_batalla(juego.tipo_batalla);
    juego.gimnasios = heap_crear(&comparador, &destructor_de_gimnasio);
    if (!juego.gimnasios){
        printf("Error al cargar el juego. reintente pls.\n");
        return 0;
    } 

    //agregar_personaje(&juego); //PA AGILIZAR (dsp hay que descomentar el agregar pj y insertar gim)!!
    //insertar_gimnasio(juego.gimnasios); //PA AGILIZAR
    //insertar_gimnasio_2(juego.gimnasios); //PA AGILIZAR
    //menu_gimnasio(&juego);

    menu_inicio(&juego);
    return 0;
}

void menu_inicio(juego_t* juego){
    char letra;

    printf("\nHola!!\nBienvenido al mundo Pokemon! Soy el profesor OAK(?\nAntes de comenzar tu aventura, necesito que completes un formulario xdxd. \n\n");

    printf("(E)--> Ingresar el archivo del protagonista\n");
    printf("(A)--> Agregar un gimnasio pokemon\n");
    if (juego->protagonista && heap_elementos(juego->gimnasios) > 0){
        printf("(I)--> Comienza la partida\n");
        printf("(S)--> Comienza la partida en modo SIMULACION\n");
    }
    printf("NOTA: Para iniciar la partida, primero se debe ingresar el personaje y al menos 1 gimnasio\n");

    printf("\nIngrese uno de los caracteres indicados: ");
    letra = leer_letra();

    bool datos_completos = false;
    bool caracter_valido = false;
    while (!datos_completos){
        caracter_valido = false;
        if ( (letra == ENTRENADOR || letra == ENTRENADOR_MINUSCULA) && !(juego->protagonista) ){
            agregar_personaje(juego);
            caracter_valido = true;
        }
        if (letra == AGREGAR_GIMNASIO || letra == AGREGAR_GIMNASIO_MINUSCULA){
            insertar_gimnasio(juego->gimnasios);
            caracter_valido = true;
        }
        if ( (letra == INICIAR || letra == INICIAR_MINUSCULA || letra == SIMULAR || letra == SIMULAR_MINUSCULA) && juego->protagonista && (heap_elementos(juego->gimnasios) > 0)){
            if (letra == INICIAR || letra == INICIAR_MINUSCULA) juego->simular = 0; //false
            if (letra == SIMULAR || letra == SIMULAR_MINUSCULA) juego->simular = 1; //true
            caracter_valido = true;
            datos_completos = true;
        }

        if (!datos_completos){
            if (!caracter_valido) {
                printf("\nCaracter invalido, las opciones son:\n");
                if (!juego->protagonista) printf("(E)--> Ingresar el archivo del protagonista\n");
                printf("(A)--> Agregar un gimnasio pokemon\n"); //Para que pueda agregar otro gimnasio si quiere.
                if (juego->protagonista && heap_elementos(juego->gimnasios) > 0){
                    printf("(I)--> Comienza la partida\n");
                    printf("(S)--> Comienza la partida en modo SIMULACION\n");
                }
            }else{
                if(!(juego->protagonista) && heap_elementos(juego->gimnasios) == 0){
                    printf("\nPara iniciar la partida es necesario cargar un personaje y al menos un gimnasio.\n");
                    printf("(E)--> Ingresar el archivo del protagonista\n");
                    printf("(A)--> Agregar un gimnasio pokemon\n");
                }
                else if(!(juego->protagonista)){
                    printf("\nPara iniciar la partida necesita cargar un protagonista.\n");
                    printf("(E)--> Ingresar el archivo del protagonista\n");
                    printf("(A)--> Agregar un gimnasio pokemon\n");
                }
                else if(heap_elementos(juego->gimnasios) == 0){
                    printf("\nPara iniciar la partida necesita cargar al menos un gimnasio.\n");
                    printf("(A)--> Agregar un gimnasio pokemon\n");
                }
                if ((juego->protagonista) && heap_elementos(juego->gimnasios) > 0){ //Recien cuando tenga prota y gym, puedo empezar.
                    printf("(A)--> Agregar otro gimnasio pokemon\n");
                    printf("(I)--> Comenzar la partida\n");
                    printf("(S)--> Comenzar la partida en modo SIMULACION\n");
                }
            }

            printf("\nIngrese uno de los caracteres indicados: ");
            letra = leer_letra();
        }

    }
    printf("\n\n\nEMPIEZA LA AVENTURAAA!\n\n\n");
    menu_gimnasio(juego);
}

void menu_gimnasio(juego_t* juego){
    char letra;
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);

    printf("\n\n\nBienvenido al %s!!!.\n\n", gimnasio->nombre);
    tipo_de_combate_gimnasio(juego);

    if (juego->simular){
        printf("Se realizara la simulacion.\n");
    }
    printf("        ¿Que quiere hacer?....\n");
    printf("\n\n(E)--> Muesta el equipo del protagonista.\n");
    printf("(G)--> Muesta informacion del gimnasio.\n");
    printf("(C)--> Cambiar pokemones del equipo.\n");
    if (lista_vacia(gimnasio->entrenadores)){
        printf("(B)--> Combatir contra el lider %s\n", gimnasio->lider->nombre);
    }else{
        printf("(B)--> Combatir contra el proximo entrenador.\n");
    }

    printf("\nIngrese uno de los caracteres indicados: ");
    letra = leer_letra();

    bool fin = false;
    bool caracter_valido = false;
    while (!fin){
        fin = false;

        if (letra == ENTRENADOR || letra == ENTRENADOR_MINUSCULA){
            protagonista_mostrar(juego->protagonista);
            caracter_valido = true;
        }
        if (letra == INFO_GIMNASIO || letra == INFO_GIMNASIO_MINUSCULA){
            gimnasio_mostrar(gimnasio);
            caracter_valido = true;
        }
        if (letra == CAMBIAR_PKMN || letra == CAMBIAR_PKMN_MINUSCULA){
            if (lista_elementos(juego->protagonista->pokemon_obtenidos) > MAX_EQUIPO){
                cambio_pokemon(juego->protagonista);
            }else{
                printf("No hay pokemones en caja, todos los pokemones que tiene estan en su equipo.\n");
            }
            caracter_valido = true;
        }
        if (letra == BATALLAR || letra == BATALLAR_MINUSCULA){
            caracter_valido = true;
            combate_pokemon(juego);
            fin = true;
        }

        if (!fin){
            if (!caracter_valido) printf("\nCaracter invalido, las opciones son:\n");
            printf("\n......................................\n");
            printf("    %s\n", gimnasio->nombre);
            printf("\n      ¿Que quiere hacer?....\n");
            printf("\n(E)--> Muesta el equipo del protagonista.\n");
            printf("(G)--> Muesta informacion del gimnasio.\n");
            printf("(C)--> Cambiar pokemones del equipo.\n");
            if (lista_vacia(gimnasio->entrenadores)){
                printf("(B)--> Combatir contra el lider %s\n", gimnasio->lider->nombre);
            }else{
                printf("(B)--> Combatir contra el proximo entrenador.\n");
            }
            printf("\nIngrese uno de los caracteres indicados: ");
            letra = leer_letra();
        }

    }

}

void combate_pokemon(juego_t* juego){
    bool es_lider = false;
    entrenador_t* rival;
    char letra;
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    funcion_batalla funcion_tipo_batalla = juego->tipo_batalla[(gimnasio->puntero_a_combate) - 1];
    if (lista_vacia(gimnasio->entrenadores)) es_lider = true;
    if (es_lider)
        rival = gimnasio->lider;
    else
        rival = lista_ultimo(gimnasio->entrenadores);

    lista_iterador_t* it_pokemon_protagonista = lista_iterador_crear(juego->protagonista->pokemon_para_combatir);
    lista_iterador_t* it_pokemon_rival = lista_iterador_crear(rival->pokemones);
    
    int i = 1;
    
    printf("\n***********¡%s VS %s!***********\n", juego->protagonista->nombre, rival->nombre);

    while (lista_iterador_tiene_siguiente(it_pokemon_protagonista) && lista_iterador_tiene_siguiente(it_pokemon_rival)){
        if (!juego->simular){
            printf("¡Comenzara el %iº enfrentamiento!\n", i);
            mostrar_info_combate(lista_iterador_elemento_actual(it_pokemon_protagonista), lista_iterador_elemento_actual(it_pokemon_rival));
            printf("Ingrese N para realizar el combate: ");
            letra = leer_letra();
            while(letra != PROXIMO_COMBATE && letra != PROXIMO_COMBATE_MINUSCULA){
                printf("Ingrese N para realizar el combate: ");
                letra = leer_letra();
            }
        }
        if (funcion_tipo_batalla(lista_iterador_elemento_actual(it_pokemon_protagonista), lista_iterador_elemento_actual(it_pokemon_rival)) == GANO_PRIMERO){
            printf("Tu %s ha derrotado al %s rival\n", ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_protagonista))->nombre, ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_rival))->nombre);
            mejorar_pokemon(lista_iterador_elemento_actual(it_pokemon_protagonista));
            lista_iterador_avanzar(it_pokemon_rival); //Avanzo la del q perdio.
        } else{
            printf("%s ha derrotado a tu querido %s\n", ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_rival))->nombre, ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_protagonista))->nombre);
            lista_iterador_avanzar(it_pokemon_protagonista);
            //printf("Tu siguiente pokemon es %s\n", ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_protagonista))->nombre);
        }
        i++;
    }
    bool ganaste = lista_iterador_tiene_siguiente(it_pokemon_protagonista);
    lista_iterador_destruir(it_pokemon_protagonista);
    lista_iterador_destruir(it_pokemon_rival);
    if (ganaste){
        if (es_lider){
            printf("FELICIDADES! Has vencido al lider del gimnasio!\n");
            printf("%s: ¡Has mostrado tu valia al vencerme!\n%s: Como lider del %s te otorgo la medalla de %s\n", gimnasio->lider->nombre, gimnasio->lider->nombre, gimnasio->nombre, gimnasio->lider->nombre);
            menu_victoria(juego);
            return;
        } else{
            /*Hay q eliminar a los entrenadores vencidos para que no vuelvan a aparecer*/
            printf("Haz vencido al entrenador %s\n", rival->nombre);
            entrenador_destruir(rival);
            lista_desapilar(gimnasio->entrenadores);
            printf("¡Preparate que comienza el combate contra el siguiente entrenador!\n");
            combate_pokemon(juego);
        }
    }else{
        printf("Has sido vencido por %s :(\n", rival->nombre);
        printf("QUE LASTIMA! HAS ESTADO MUY CERCA.\n");
        menu_derrota(juego);
    }

}


void tipo_de_combate_gimnasio(juego_t* juego){
    if (!juego) return;
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    if (gimnasio->puntero_a_combate == 1) printf("Este gimnasio decide al ganador por la DEFENSA de sus pokemones.\n");
    if (gimnasio->puntero_a_combate == 2) printf("Este gimnasio decide al ganador por la VELOCIDAD de sus pokemones.\n");
    if (gimnasio->puntero_a_combate == 3) printf("Este gimnasio decide al ganador por la ATAQUE de sus pokemones.\n");
    if (gimnasio->puntero_a_combate == 4) printf("Este gimnasio decide al ganador por la SUMA GENERAL DE LAS ESTADISTICAS de sus pokemones.\n");
    if (gimnasio->puntero_a_combate == 5) printf("Este gimnasio decide al ganador por el LARGO DEL NOMBRE de sus pokemones.\n");

}

void menu_victoria(juego_t* juego){
    if (juego->simular){
        heap_eliminar_raiz(juego->gimnasios);
        if (heap_elementos(juego->gimnasios) == 0){
            printf("SOS UN KPO MAESTRO POKEMON BRO.\n");
            //MENU_MAESTRO POKEMON
            eres_maestro_pokemon(juego);
        }else{
            menu_gimnasio(juego);
        }
        return;
    }
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    char letra;
    bool tomar_prestado = false;

    if (!tomar_prestado) printf("(T)--> Tomar prestado un pokemon de %s\n", gimnasio->lider->nombre);
    printf("(C)--> Cambiar pokemones del equipo.\n");
    printf("(N)--> Ir al proximo gimnasio.\n");
    

    printf("\nIngrese uno de los caracteres indicados: ");
    letra = leer_letra();

    bool fin = false;
    bool caracter_valido = false;
    while (!fin){
        fin = false;

        if (letra == TOMAR_PRESTADO || letra == TOMAR_PRESTADO_MINUSCULA){
            int correcto = tomar_pokemon_prestado(juego->protagonista->pokemon_obtenidos, gimnasio->lider->pokemones);
            caracter_valido = true;
            if (correcto == 0) tomar_prestado = true;
        }

        if (letra == CAMBIAR_PKMN || letra == CAMBIAR_PKMN_MINUSCULA){
            if (lista_elementos(juego->protagonista->pokemon_obtenidos) > MAX_EQUIPO){
                cambio_pokemon(juego->protagonista);
            }else{
                printf("No hay pokemones en caja, todos los pokemones que tiene estan en su equipo.\n");
            }
            caracter_valido = true;
        }
        if (letra ==  PROXIMO_COMBATE || letra == PROXIMO_COMBATE_MINUSCULA){ //PROX COMBATE O PROXIMO GIM ES LO MISMO.
            caracter_valido = true;
            heap_eliminar_raiz(juego->gimnasios);
            if (heap_elementos(juego->gimnasios) == 0){
                printf("ENBTRASTE ACA BRO.\n");
                //MENU_MAESTRO POKEMON
                eres_maestro_pokemon(juego);
                return;
            }else{
                menu_gimnasio(juego);
            }
            fin = true;
        }

        if (!fin){
            if (!caracter_valido) printf("\nCaracter invalido, las opciones son:\n");
            printf("\n......................................\n");
            if (!tomar_prestado) printf("(T)--> Tomar prestado un pokemon de %s\n", gimnasio->lider->nombre);
            printf("(C)--> Cambiar pokemones del equipo.\n");
            printf("(N)--> Ir al proximo gimnasio.\n");
            
            printf("\nIngrese uno de los caracteres indicados: ");
            letra = leer_letra();
        }
    }

}

void menu_derrota(juego_t* juego){
    char letra;
    bool es_lider = false;
    entrenador_t* rival;
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    if (lista_vacia(gimnasio->entrenadores)) es_lider = true;
    if (es_lider)
        rival = gimnasio->lider;
    else
        rival = lista_ultimo(gimnasio->entrenadores);

    if (juego->simular){
        printf("¡Has perdido contra %s!\n", rival->nombre);
        printf("HASTA AQUI HAS LLEGADO MUCHACHO\nFin de la simulacion....\n");
        protagonista_destruir(juego->protagonista);
        heap_destruir(juego->gimnasios);
    }

    printf("¡Has perdido contra %s!\n", rival->nombre);

    printf("(C)--> Cambiar pokemones del equipo.\n");
    printf("(R)--> Reintentar el gimnasio.\n");
    printf("(F)--> Finalizar partida.\n");
    
    printf("\nIngrese uno de los caracteres indicados: ");
    letra = leer_letra();

    bool fin = false;
    bool caracter_valido = false;
    while (!fin){
        fin = false;

        if (letra == CAMBIAR_PKMN || letra == CAMBIAR_PKMN_MINUSCULA){
            if (lista_elementos(juego->protagonista->pokemon_obtenidos) > MAX_EQUIPO){
                cambio_pokemon(juego->protagonista);
            }else{
                printf("No hay pokemones en caja, todos los pokemones que tiene estan en su equipo.\n");
            }
            caracter_valido = true;
        }
        if (letra ==  REINTENTAR_GIMNASIO || letra == REINTENTAR_GIMNASIO_MINUSCULA){ 
            menu_gimnasio(juego);
            caracter_valido = true;
            fin = true;
        }
        if (letra == FINALIZAR || letra == FINALIZAR_MINUSCULA){
            printf("Uhhh, que lastima. Espero que vuelvas! :)\n");
            printf("NOS VEMOSS!\n\n\n");
            protagonista_destruir(juego->protagonista);
            heap_destruir(juego->gimnasios);
            caracter_valido = true;
            fin = true;
        }

        if (!fin){
            if (!caracter_valido) printf("\nCaracter invalido, las opciones son:\n");
            printf("\n......................................\n");
            printf("(C)--> Cambiar pokemones del equipo.\n");
            printf("(R)--> Reintentar el gimnasio.\n");
            printf("(F)--> Finalizar partida.\n");
            
            printf("\nIngrese uno de los caracteres indicados: ");
            letra = leer_letra();
        }
    }

}

void eres_maestro_pokemon(juego_t* juego){
    printf("\n*************************************************\n");
    printf("Felicidades %s! Eres todo un maestro pokemon!\n", juego->protagonista->nombre);
    printf("*************************************************\n");

    protagonista_destruir(juego->protagonista);
    heap_destruir(juego->gimnasios);
}

char leer_letra(){
    char letra = (char)getchar();
    
    while (letra == -1 || letra == '\n'){
        //printf("Enter solo no vale. Vuelta a ingresar: ");
        letra = (char)getchar();
    }

    char siguiente_letra = (char)getchar();
    while (siguiente_letra == -1 || siguiente_letra != '\n'){
        //printf("Deber ser una letra sola. Vuelta a ingresar.\n");
        letra = (char)getchar();
    }

    return letra;
}