#include <stdio.h>
#include <stdbool.h>
#include "heap.h"
#include "gimnasio_y_protagonista.h"

#define AZUL "\033[0;34m"
#define CYAN "\033[0;36m"
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define BLANCO "\033[0;37m"
#define VIOLETA "\033[0;35m"
#define AMARILLO "\033[0;33m"

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
 *   Muestra el menu inicial del juego.
 */
void menu_inicio(juego_t* juego);
/*
 *   Muestra el menu de gimnasio.
 */
void menu_gimnasio(juego_t* juego);
/*
 *   Muestra el menu de victoria.
 */
void menu_victoria(juego_t* juego);
/*
 *   Muestra el menu de derrota.
 */
void menu_derrota(juego_t* juego);
/*
 *  Muestra un menu de combate y los detalles de este.
 */
void combate_pokemon(juego_t* juego);
/*
 *   Imprime el tipo de combate de dicho gimnasio.
 */
void tipo_de_combate_gimnasio(juego_t* juego);
/*
 *   Muestra por consola un ascii art de MAESTRO POKEMON.
 */
void eres_maestro_pokemon(juego_t* juego);


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
    //menu_gimnasio(&juego);

    menu_inicio(&juego);
    return 0;
}

void menu_inicio(juego_t* juego){
    char letra;

    printf("\n¡Te doy la bienvenida al "AMARILLO"mundo Pokemon"BLANCO"!\n  ¡Preparate para una gran aventura!\n\n");

    printf(""VERDE"(E)"BLANCO"--> Ingresar el archivo del protagonista\n");
    printf(""VERDE"(A)"BLANCO"--> Agregar gimnasio/s pokemon\n");
    //if (juego->protagonista && heap_elementos(juego->gimnasios) > 0){
        printf(""ROJO"(I)--> Comienza la partida."BLANCO"\n");
        printf(""ROJO"(S)--> Comienza la partida en modo SIMULACION"BLANCO"\n");
    //}
    printf("\n"ROJO"NOTA"BLANCO": Para iniciar la partida, primero se debe ingresar el personaje y al menos 1 gimnasio.\n");

    printf("\n"AMARILLO"Ingrese uno de los caracteres indicados: "BLANCO"");
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
            if (letra == INICIAR || letra == INICIAR_MINUSCULA) juego->simular = false; 
            if (letra == SIMULAR || letra == SIMULAR_MINUSCULA) juego->simular = true; 
            caracter_valido = true;
            datos_completos = true;
        }

        if (!datos_completos){
            if (!caracter_valido) {
                printf("\n"VERDE" *"BLANCO"Caracter invalido, las opciones son:\n");
                if (!juego->protagonista) printf(""VERDE"(E)"BLANCO"--> Ingresar el archivo del protagonista\n");
                printf(""VERDE"(A)"BLANCO"--> Agregar gimnasio/s pokemon\n"); //Para que pueda agregar otro gimnasio si quiere.
                if (juego->protagonista && heap_elementos(juego->gimnasios) > 0){
                    printf(""VERDE"(I)"BLANCO"--> Comienza la partida\n");
                    printf(""VERDE"(S)"BLANCO"--> Comienza la partida en modo SIMULACION\n");
                }else{
                    printf(""ROJO"(I)--> Comienza la partida"BLANCO"\n");
                    printf(""ROJO"(S)--> Comienza la partida en modo SIMULACION"BLANCO"\n");
                    printf("\n"ROJO"NOTA"BLANCO": Para iniciar la partida, primero se debe ingresar el personaje y al menos 1 gimnasio.\n");
                }
            }else{
                if(!(juego->protagonista) && heap_elementos(juego->gimnasios) == 0){
                    printf("\n"VERDE" *"BLANCO"Para iniciar la partida es necesario cargar un personaje y al menos un gimnasio."VERDE"* "BLANCO"\n");
                    printf(""VERDE"(E)"BLANCO"--> Ingresar el archivo del protagonista\n");
                    printf(""VERDE"(A)"BLANCO"--> Agregar gimnasio/s pokemon\n");
                    printf(""ROJO"(I)--> Comienza la partida"BLANCO"\n");
                    printf(""ROJO"(S)--> Comienza la partida en modo SIMULACION"BLANCO"\n");
                    printf("\n"ROJO"NOTA"BLANCO": Para iniciar la partida, primero se debe ingresar el personaje y al menos 1 gimnasio.\n");
                }
                else if(!(juego->protagonista)){
                    printf("\n"VERDE" *"BLANCO"Para iniciar la partida necesita cargar un protagonista."VERDE"* "BLANCO"\n");
                    printf(""VERDE"(E)"BLANCO"--> Ingresar el archivo del protagonista\n");
                    printf(""VERDE"(A)"BLANCO"--> Agregar gimnasio/s pokemon\n");
                    printf(""ROJO"(I)--> Comienza la partida"BLANCO"\n");
                    printf(""ROJO"(S)--> Comienza la partida en modo SIMULACION"BLANCO"\n");
                    printf("\n"ROJO"NOTA"BLANCO": Para iniciar la partida, primero se debe ingresar el personaje y al menos 1 gimnasio.\n");
                }
                else if(heap_elementos(juego->gimnasios) == 0){
                    printf("\n"VERDE" *"BLANCO"Para iniciar la partida necesita cargar al menos un gimnasio."VERDE"* "BLANCO"\n");
                    printf(""VERDE"(A)"BLANCO"--> Agregar gimnasio/s pokemon\n");
                    printf(""ROJO"(I)--> Comienza la partida"BLANCO"\n");
                    printf(""ROJO"(S)--> Comienza la partida en modo SIMULACION"BLANCO"\n");
                    printf("\n"ROJO"NOTA"BLANCO": Para iniciar la partida, primero se debe ingresar el personaje y al menos 1 gimnasio.\n");
                }
                if ((juego->protagonista) && heap_elementos(juego->gimnasios) > 0){ //Recien cuando tenga prota y gym, puedo empezar.
                    printf("\n...........................................\n");
                    printf(""VERDE"(A)"BLANCO"--> Agregar otro gimnasio pokemon\n");
                    printf(""VERDE"(I)"BLANCO"--> Comenzar la partida\n");
                    printf(""VERDE"(S)"BLANCO"--> Comenzar la partida en modo SIMULACION\n");
                }
            }

            printf("\n"AMARILLO"Ingrese uno de los caracteres indicados: "BLANCO"");
            letra = leer_letra();
        }

    }
    printf("\n\n"AMARILLO"");
    printf(" ██████╗ ██╗   ██╗███████╗     ██████╗ ██████╗ ███╗   ███╗██╗███████╗███╗   ██╗ ██████╗███████╗\n");
    printf("██╔═══██╗██║   ██║██╔════╝    ██╔════╝██╔═══██╗████╗ ████║██║██╔════╝████╗  ██║██╔════╝██╔════╝\n");
    printf("██║   ██║██║   ██║█████╗      ██║     ██║   ██║██╔████╔██║██║█████╗  ██╔██╗ ██║██║     █████╗  \n");
    printf("██║▄▄ ██║██║   ██║██╔══╝      ██║     ██║   ██║██║╚██╔╝██║██║██╔══╝  ██║╚██╗██║██║     ██╔══╝  \n");
    printf("╚██████╔╝╚██████╔╝███████╗    ╚██████╗╚██████╔╝██║ ╚═╝ ██║██║███████╗██║ ╚████║╚██████╗███████╗\n");
    printf(" ╚══▀▀═╝  ╚═════╝ ╚══════╝     ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝╚══════╝\n");
    printf("\n");
    printf("██╗      █████╗      █████╗ ██╗   ██╗███████╗███╗   ██╗████████╗██╗   ██╗██████╗  █████╗ ██╗   \n");
    printf("██║     ██╔══██╗    ██╔══██╗██║   ██║██╔════╝████╗  ██║╚══██╔══╝██║   ██║██╔══██╗██╔══██╗██║   \n");
    printf("██║     ███████║    ███████║██║   ██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║██████╔╝███████║██║   \n");
    printf("██║     ██╔══██║    ██╔══██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ██║   ██║██╔══██╗██╔══██║╚═╝  \n");
    printf("███████╗██║  ██║    ██║  ██║ ╚████╔╝ ███████╗██║ ╚████║   ██║   ╚██████╔╝██║  ██║██║  ██║██╗  \n");
    printf("╚══════╝╚═╝  ╚═╝    ╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  \n"BLANCO"");
    //printf("\n\n            "AMARILLO"¡QUE COMIENCE LA AVENTURA!"BLANCO"\n");
    menu_gimnasio(juego);
}

void menu_gimnasio(juego_t* juego){
    char letra;
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    
    printf("\n\n        Bienvenido al "AMARILLO"%s"BLANCO"!!\n", gimnasio->nombre);
    tipo_de_combate_gimnasio(juego);

    if (juego->simular){
        printf(""VERDE"Se realizara la simulacion."BLANCO"\n");
        combate_pokemon(juego);
        return;
    }
    printf("\n"AMARILLO"¿Que quiere hacer?...."BLANCO"\n");
    printf("\n"VERDE"(E)"BLANCO"--> Ver tu equipo PKMN.\n");
    printf(""VERDE"(G)"BLANCO"--> Ver informacion del gimnasio.\n");
    printf(""VERDE"(C)"BLANCO"--> Cambiar tu equipo PKMN.\n");
    if (lista_vacia(gimnasio->entrenadores)){
        printf(""VERDE"(B)"BLANCO"--> Combatir contra el lider %s\n", gimnasio->lider->nombre);
    }else{
        printf(""VERDE"(B)"BLANCO"--> Combatir contra el proximo entrenador.\n");
    }

    printf("\n"AMARILLO"Ingrese uno de los caracteres indicados: "BLANCO"");
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
                printf("\n"VERDE" * "ROJO"No hay pokemones en caja, todos los pokemones que tienes estan en su equipo."VERDE" * "BLANCO"\n");
            }
            caracter_valido = true;
        }
        if (letra == BATALLAR || letra == BATALLAR_MINUSCULA){
            caracter_valido = true;
            combate_pokemon(juego);
            fin = true;
        }

        if (!fin){
            if (!caracter_valido) printf("\n"VERDE" *"BLANCO"Caracter invalido, las opciones son:\n");
            printf("\n.............................................\n");
            printf("\n\n             "AMARILLO"%s"BLANCO"!!\n", gimnasio->nombre);
            tipo_de_combate_gimnasio(juego);
            printf("\n"AMARILLO"¿Que quiere hacer?...."BLANCO"\n");
            printf("\n"VERDE"(E)"BLANCO"--> Ver tu equipo PKMN.\n");
            printf(""VERDE"(G)"BLANCO"--> Ver informacion del gimnasio.\n");
            printf(""VERDE"(C)"BLANCO"--> Cambiar tu equipo PKMN.\n");
            if (lista_vacia(gimnasio->entrenadores)){
                printf(""VERDE"(B)"BLANCO"--> Combatir contra el lider %s\n", gimnasio->lider->nombre);
            }else{
                printf(""VERDE"(B)"BLANCO"--> Combatir contra el proximo entrenador.\n");
            }
            printf("\n"AMARILLO"Ingrese uno de los caracteres indicados: "BLANCO"");
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
    
    printf("\n      *********** "AZUL"%s"BLANCO" ¡VS! "ROJO"%s"BLANCO" ***********\n", juego->protagonista->nombre, rival->nombre);

    while (lista_iterador_tiene_siguiente(it_pokemon_protagonista) && lista_iterador_tiene_siguiente(it_pokemon_rival)){
        if (!juego->simular){
            printf(""VERDE"             ¡Comienza el %iº enfrentamiento!"BLANCO"\n", i);
            tipo_de_combate_gimnasio(juego);

            mostrar_info_combate(lista_iterador_elemento_actual(it_pokemon_protagonista), lista_iterador_elemento_actual(it_pokemon_rival));
            printf(""AMARILLO"Ingrese N para realizar el combate: "BLANCO"");
            letra = leer_letra();
            while(letra != PROXIMO_COMBATE && letra != PROXIMO_COMBATE_MINUSCULA){
                printf(""AMARILLO"Ingrese N para realizar el combate: "BLANCO"");
                letra = leer_letra();
            }
        }
        if (funcion_tipo_batalla(lista_iterador_elemento_actual(it_pokemon_protagonista), lista_iterador_elemento_actual(it_pokemon_rival)) == GANO_PRIMERO){
            printf("\n"AMARILLO" * "BLANCO"¡Tu" CYAN " %s "BLANCO"ha derrotado al "ROJO"%s" BLANCO" rival! "AMARILLO" * "BLANCO"\n", ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_protagonista))->nombre, ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_rival))->nombre);
            mejorar_pokemon(lista_iterador_elemento_actual(it_pokemon_protagonista));
            lista_iterador_avanzar(it_pokemon_rival); //Avanzo la del q perdio.
        } else{
            printf("\n- OH NO! "ROJO"%s"BLANCO" ha derrotado a tu querido "CYAN"%s"BLANCO"\n", ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_rival))->nombre, ((pokemon_t*)lista_iterador_elemento_actual(it_pokemon_protagonista))->nombre);
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
            printf(""VERDE" * ¡FELICIDADES!"BLANCO" Has vencido al lider del gimnasio! * \n");
            printf(""ROJO"%s"BLANCO": ¡Has mostrado tu valia al vencerme!\n"ROJO"%s"BLANCO": Como lider del "AMARILLO"%s"BLANCO" te otorgo la medalla de "AZUL"%s"BLANCO"\n\n", gimnasio->lider->nombre, gimnasio->lider->nombre, gimnasio->nombre, gimnasio->lider->nombre);
            menu_victoria(juego);
            return;
        }
        /*Hay q eliminar a los entrenadores vencidos para que no vuelvan a aparecer*/
        printf(""VERDE" * "BLANCO"Haz vencido al entrenador "ROJO"%s"VERDE" * "BLANCO"\n", rival->nombre);
        entrenador_destruir(rival);
        lista_desapilar(gimnasio->entrenadores);
        printf(""AMARILLO"¡Preparate que comienza el combate contra el siguiente entrenador!"BLANCO"\n");
        combate_pokemon(juego);
    }else{
        //printf(""ROJO"Has sido vencido por %s :(\n", rival->nombre);
        //printf(""ROJO"QUE LASTIMA! HAS ESTADO MUY CERCA.\n");
        menu_derrota(juego);
    }

}


void tipo_de_combate_gimnasio(juego_t* juego){
    if (!juego) return;
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    if (gimnasio->puntero_a_combate == 1) printf("      (El "CYAN"PKMN ganador"BLANCO" se definira por su "CYAN"DEFENSA"BLANCO"!)\n");
    if (gimnasio->puntero_a_combate == 2) printf("      (El "CYAN"PKMN ganador"BLANCO" se definira por su "CYAN"VELOCIDAD"BLANCO"!)\n");
    if (gimnasio->puntero_a_combate == 3) printf("      (El "CYAN"PKMN ganador"BLANCO" se definira por su "CYAN"ATAQUE"BLANCO"!)\n");
    if (gimnasio->puntero_a_combate == 4) printf("      (El "CYAN"PKMN ganador"BLANCO" se definira por sus "CYAN"ESTADISTICAS GENERALES"BLANCO"!)\n");
    if (gimnasio->puntero_a_combate == 5) printf("      (El "CYAN"PKMN ganador"BLANCO" se definira por el "CYAN"LARGO DE SU NOMBRE"BLANCO"!)\n");

}

void menu_victoria(juego_t* juego){
    if (juego->simular){
        heap_eliminar_raiz(juego->gimnasios);
        if (heap_elementos(juego->gimnasios) == 0){
            //printf("SOS UN KPO MAESTRO POKEMON BRO.\n");
            eres_maestro_pokemon(juego);
            return;
        }else{
            menu_gimnasio(juego);
        }
        return;
    }
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    char letra;
    bool tomar_prestado = false;

    if (!tomar_prestado) printf(""VERDE"(T)"BLANCO"--> Tomar prestado un pokemon de %s\n", gimnasio->lider->nombre);
    printf(""VERDE"(C)"BLANCO"--> Cambiar pokemones del equipo.\n");
    printf(""VERDE"(N)"BLANCO"--> Ir al proximo gimnasio.\n");
    

    printf(""AMARILLO"\nIngrese uno de los caracteres indicados: "BLANCO"");
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
                printf(""ROJO" * "ROJO"No hay pokemones en caja, todos los pokemones que tiene estan en su equipo.\n");
            }
            caracter_valido = true;
        }
        if (letra ==  PROXIMO_COMBATE || letra == PROXIMO_COMBATE_MINUSCULA){ //PROX COMBATE O PROXIMO GIM ES LO MISMO.
            caracter_valido = true;
            heap_eliminar_raiz(juego->gimnasios);
            if (heap_elementos(juego->gimnasios) == 0){
                eres_maestro_pokemon(juego);
                return;
            }else{
                menu_gimnasio(juego);
            }
            fin = true;
        }

        if (!fin){
            if (!caracter_valido) printf("\n"VERDE" *"BLANCO"Caracter invalido, las opciones son:\n");
            printf("\n......................................\n");
            if (!tomar_prestado) printf(""VERDE"(T)"BLANCO"--> Tomar prestado un pokemon de %s\n", gimnasio->lider->nombre);
            printf(""VERDE"(C)"BLANCO"--> Cambiar pokemones del equipo.\n");
            printf(""VERDE"(N)"BLANCO"--> Ir al proximo gimnasio.\n");
            
            printf("\n"AMARILLO"Ingrese uno de los caracteres indicados: "BLANCO"");
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
        printf("\n"ROJO"¡Has perdido contra el "BLANCO"%s del gimnasio "AMARILLO"%s"BLANCO"\n", rival->nombre, gimnasio->nombre);
        printf("\n"AMARILLO"HASTA AQUI HAS LLEGADO MUCHACHO!\nFin de la simulacion"BLANCO"....\n\n\n");
        protagonista_destruir(juego->protagonista);
        heap_destruir(juego->gimnasios);
        return;
    }

    printf("\n"ROJO"¡Has perdido contra el "BLANCO"%s"ROJO"!"BLANCO"\n", rival->nombre);
    printf("....................................................\n");
    printf(""VERDE"(C)"BLANCO"--> Cambiar pokemones del equipo.\n");
    printf(""VERDE"(R)"BLANCO"--> Reintentar el gimnasio.\n");
    printf(""VERDE"(F)"BLANCO"--> Finalizar partida.\n");
    
    printf("\n"AMARILLO"Ingrese uno de los caracteres indicados: "BLANCO"");
    letra = leer_letra();

    bool fin = false;
    bool caracter_valido = false;
    while (!fin){
        fin = false;

        if (letra == CAMBIAR_PKMN || letra == CAMBIAR_PKMN_MINUSCULA){
            if (lista_elementos(juego->protagonista->pokemon_obtenidos) > MAX_EQUIPO){
                cambio_pokemon(juego->protagonista);
            }else{
                printf(""VERDE" * "ROJO"No hay pokemones en caja, todos los pokemones que tiene estan en su equipo."BLANCO"\n");
            }
            caracter_valido = true;
        }
        if (letra ==  REINTENTAR_GIMNASIO || letra == REINTENTAR_GIMNASIO_MINUSCULA){ 
            menu_gimnasio(juego);
            caracter_valido = true;
            fin = true;
        }
        if (letra == FINALIZAR || letra == FINALIZAR_MINUSCULA){
            printf(""AMARILLO"\nUhhh, que lastima.... Espero que vuelvas! :)"BLANCO"\n");
            printf(""AMARILLO"NOS VEMOSS!"BLANCO"\n\n\n");
            protagonista_destruir(juego->protagonista);
            heap_destruir(juego->gimnasios);
            caracter_valido = true;
            fin = true;
        }

        if (!fin){
            if (!caracter_valido) printf("\n"VERDE" *"BLANCO"Caracter invalido, las opciones son:\n");
            printf("\n......................................\n");
            printf(""VERDE"(C)"BLANCO"--> Cambiar pokemones del equipo.\n");
            printf(""VERDE"(R)"BLANCO"--> Reintentar el gimnasio.\n");
            printf(""VERDE"(F)"BLANCO"--> Finalizar partida.\n");
            
            printf("\n"AMARILLO"Ingrese uno de los caracteres indicados: "BLANCO"");
            letra = leer_letra();
        }
    }

}

void eres_maestro_pokemon(juego_t* juego){
    printf("\n"AMARILLO" Felicidades "BLANCO"%s"AMARILLO"! Ya eres todo un....\n\n", juego->protagonista->nombre);
    printf(" ███╗   ███╗ █████╗ ███████╗███████╗████████╗██████╗  ██████╗     ██████╗  ██████╗ ██╗  ██╗███████╗███╗   ███╗ ██████╗ ███╗   ██╗██╗\n");
    printf(" ████╗ ████║██╔══██╗██╔════╝██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗    ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝████╗ ████║██╔═══██╗████╗  ██║██║\n");
    printf(" ██╔████╔██║███████║█████╗  ███████╗   ██║   ██████╔╝██║   ██║    ██████╔╝██║   ██║█████╔╝ █████╗  ██╔████╔██║██║   ██║██╔██╗ ██║██║\n");
    printf(" ██║╚██╔╝██║██╔══██║██╔══╝  ╚════██║   ██║   ██╔══██╗██║   ██║    ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██║╚██╔╝██║██║   ██║██║╚██╗██║╚═╝\n");
    printf(" ██║ ╚═╝ ██║██║  ██║███████╗███████║   ██║   ██║  ██║╚██████╔╝    ██║     ╚██████╔╝██║  ██╗███████╗██║ ╚═╝ ██║╚██████╔╝██║ ╚████║██╗\n");
    printf(" ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝     ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝\n"BLANCO"");

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
    while (siguiente_letra == -1 && siguiente_letra != '\n'){
        //printf("Deber ser una letra sola. Vuelta a ingresar.\n");
        letra = (char)getchar();
    }

    return letra;
}