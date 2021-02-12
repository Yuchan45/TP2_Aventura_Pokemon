#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

lista_t* lista_crear(){
    lista_t* lista = malloc(sizeof(lista_t));
    if (!lista){
        return NULL;
    }
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
    lista->cantidad = 0;
    return lista;

}

int lista_insertar(lista_t* lista, void* elemento){
    if (!lista){
        return -1;
    }

    nodo_t* p_nodo = malloc(sizeof(nodo_t));
    if (!p_nodo)
        return -1;

    if (lista->cantidad == 0){
        lista->nodo_inicio = p_nodo;
        lista->nodo_fin = p_nodo;
    }else{
        lista->nodo_fin->siguiente = p_nodo; // Primero, antes de cambiar el puntero final, hago que el elemento del puntero final (osea el anterior) apunte al nuevo.
        lista->nodo_fin = p_nodo; // Ahora si actualizo el puntero final.
    }

    lista->nodo_fin->elemento = elemento;
    lista->nodo_fin->siguiente = NULL;
    (lista->cantidad)++;

    return 0;
}


int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if (!lista){
        return -1;
    }
    if (posicion >= lista->cantidad || lista->cantidad == 0) //Si la posicion es la ultima o mayor, o si la lista esta vacia. Hay que insertar al final.
        return lista_insertar(lista, elemento);

    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if (!nodo_nuevo)
        return -1;

    nodo_nuevo->elemento = elemento;
    nodo_nuevo->siguiente = NULL;

    if (posicion == 0){
        nodo_nuevo->siguiente = lista->nodo_inicio;
        lista->nodo_inicio = nodo_nuevo;
        (lista->cantidad)++;
        return 0;
    }else{
        size_t indice = 0;
        nodo_t* nodo = lista->nodo_inicio;

        while(nodo != NULL){ // Caso que el nodo a agregar es uno de los del medio.
            if ((indice + 1) == posicion){
                nodo_nuevo->siguiente = nodo->siguiente;
                nodo->siguiente = nodo_nuevo;
                (lista->cantidad)++;
            }
            (indice)++;
            nodo = nodo->siguiente;
        }
        return 0;
    }
}


int lista_borrar(lista_t* lista){
    if (!lista)
        return -1;

    if (lista->cantidad == 0)
        return -1;

    if (lista->cantidad == 1){
        free(lista->nodo_fin);
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
        (lista->cantidad)--;
    }else{
        nodo_t* nodo = lista->nodo_inicio;
        size_t posicion = 0;

        (lista->cantidad)--;
        free(lista->nodo_fin);
        while(nodo != NULL){
            if ((posicion + 1) == lista->cantidad){
                lista->nodo_fin = nodo;
                lista->nodo_fin->siguiente = NULL;
                return 0;
            }
            (posicion)++;
            nodo = nodo->siguiente;
        }
    }

    return 0;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if (!lista)
        return -1;

    if (lista->cantidad == 0)   
        return -1;

    if ( (posicion > 0) && (posicion < (lista->cantidad-1)) ){ // Si no es ni el ultimo nodo ni el primero.
        nodo_t* nodo_auxiliar;
        nodo_t* nodo = lista->nodo_inicio;
        size_t indice = 0;

        while(nodo != NULL){
            if ((indice + 1) == posicion){
                nodo_auxiliar = nodo->siguiente;
                nodo->siguiente = nodo_auxiliar->siguiente;
                free(nodo_auxiliar);
                (lista->cantidad)--;

            }
            (indice)++;
            nodo = nodo->siguiente;
        }
    }else{
        // Si la posicion es 0 o la ultima. Hay que reasignar punteros de la lista.
        if (posicion == 0 && (lista->cantidad > 1)){ // Aca entra si la posicion a borrar es la 0 y hay 2 o mas elementos.
            nodo_t* nodo_auxiliar;
            (lista->cantidad)--;
            nodo_auxiliar = lista->nodo_inicio;
            lista->nodo_inicio = lista->nodo_inicio->siguiente;
            free(nodo_auxiliar);

        }else{ // Aca entra si hay que borrar la ultima posicion.
            return lista_borrar(lista);
        }
    }

    return 0;
}


void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if (!lista)
        return NULL;

    if (lista->cantidad == 0 || posicion > lista->cantidad-1)
        return NULL;

    nodo_t* nodo_buscado = lista->nodo_inicio;    
    for (int i = 0; i < posicion; i++){
        nodo_buscado = nodo_buscado->siguiente;
    }
    return nodo_buscado->elemento;
}

void* lista_ultimo(lista_t* lista){
    if(!lista || lista->cantidad == 0)
        return NULL;
    return lista->nodo_fin->elemento;
}

void* lista_primero(lista_t* lista){
    if(!lista || lista->cantidad == 0)
        return NULL;
    return lista->nodo_inicio->elemento;
}

bool lista_vacia(lista_t* lista){
    if(lista == NULL || lista->cantidad == 0)
        return true;
    return false;
}

size_t lista_elementos(lista_t* lista){
    if (!lista)
        return 0;
    return lista->cantidad;
}

void lista_destruir(lista_t* lista){
    if (!lista)
        return;
        
    nodo_t* nodo_actual = lista->nodo_inicio;
    while(nodo_actual){
        nodo_t* nodo_auxiliar = nodo_actual->siguiente;
        free(nodo_actual);
        nodo_actual = nodo_auxiliar;
    }
    free(lista);
}

/*----------PILAS-----------*/

int lista_apilar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}


int lista_desapilar(lista_t* lista){
    return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){
    return lista_ultimo(lista);
}

/*----------COLAS-----------*/

int lista_encolar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){
    return lista_borrar_de_posicion(lista, 0);
}

/*--------ITERADORES---------*/

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if (!lista)
        return NULL;
    
    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    if (!iterador)
        return NULL;
    iterador->lista = lista;
    iterador->corriente = lista->nodo_inicio;
    return iterador;

}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if (!iterador)
        return false;
    return iterador->corriente;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if (!iterador)
        return false;
    if (!(iterador->corriente))
        return false;
    
    iterador->corriente = iterador->corriente->siguiente;
    return iterador->corriente;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if (!iterador)
        return NULL;
    if (!(iterador->corriente))
        return NULL;
    return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if (!lista)
        return 0;
    if (!funcion)
        return 0;
    size_t elem_recorridos = 0;
    nodo_t* nodo_actual = lista->nodo_inicio;
    while(nodo_actual && (*funcion)(nodo_actual->elemento, contexto)){
        nodo_actual = nodo_actual->siguiente;
        (elem_recorridos)++;
    }
    return elem_recorridos;
}


