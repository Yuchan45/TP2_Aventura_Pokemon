#include <stdio.h>
#include <stdbool.h>
#include "heap.h"
#include "juego.h"

#define ENTRENADOR 'E'
#define ENTRENADOR_MINUSCULA 'e'
#define GIMNASIO 'A'
#define GIMNASIO_MINUSCULA 'a'
#define INICIAR 'I'
#define INICIAR_MINUSCULA 'i'
#define SIMULAR 'S'
#define SIMULAR_MINUSCULA 's'


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


int main(){
    juego_t juego;
    juego.protagonista = NULL;
    juego.simular = false;
    juego.gimnasios = heap_crear(&comparador, &destructor_de_gimnasio);
    if (!juego.gimnasios){
        printf("Error al cargar el juego. reintente pls.\n");
        return 0;
    } 

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

    bool completo = false;
    bool caracter_valido = false;
    while (!completo){
        if ( (letra == ENTRENADOR || letra == ENTRENADOR_MINUSCULA) && !(juego->protagonista) ){
            agregar_personaje(juego);
            caracter_valido = true;
        }
        if (letra == GIMNASIO || letra == GIMNASIO_MINUSCULA){
            insertar_gimnasio(juego->gimnasios);
            caracter_valido = true;
        }
        if ( (letra == INICIAR || letra == INICIAR_MINUSCULA || letra == SIMULAR || letra == SIMULAR_MINUSCULA) && juego->protagonista && (heap_elementos(juego->gimnasios) > 0)){
            if (letra == INICIAR || letra == INICIAR_MINUSCULA) juego->simular = 0;
            if (letra == SIMULAR || letra == SIMULAR_MINUSCULA) juego->simular = 1;
            caracter_valido = true;
            completo = true;
        }

        if (!completo){
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
                    printf("(E)--> Agregar un gimnasio pokemon\n");
                    printf("(E)--> Ingresar el archivo del protagonista\n");
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
    //menu_gimnasio(juego);
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