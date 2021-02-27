Trabajo practico nº2 - "¡Aventura pokémon!".

Hago entrega de los archivos necesarios para ejecutar el juego: 

-aventura.c (main)               --> Aqui se cargan en el juego_t la informacion necesaria para jugar.
-menus.h y menus.c               --> Aqui se encuentran todos los menues interactivos con el usuario.
-gimnasio_y_protagonista.h y .c  --> Aqui se encuentran funciones que el menu utiliza.
-pokemon_y_combate.h y .c        --> Aqui se encuentran funciones que el menu utiliza.
-batallas.h y .c                 --> Aqui se encuentran funciones de batalla.
-heap.h y .c                     --> Aqui se encuentra la implementacion del TDA HEAP.
Asi como tambien las pruebas del TDA Heap dentro de la carpeta "Testeos" y algunos archivos .txt para poder cargar al protagonista de la aventura y los gimnasios que este debera superar. 

-Dentro de la carpeta de "Protagonista", he dejado 4 protagonistas para usar.
-Dentro de la carpeta "Gimnasios", he dejado 8 archivos de gimnasio (individuales) por si desea enfrentarse contra algun/os gimnasio/s en especifico. Tambien deje un (1) archivo en donde se encuentran los 8 gimnasios (TODOS JUNTOS) para asi poder cargarlos a todos al mismo tiempo y no tener que hacerlo uno por uno.

ACLARACION: Dichos .txts (gimnasio y protagonista) pueden ser modificados a gusto con el nombre y pokemones que el usuario desee, siempre y cuando se respete el formato de dicho archivo.

----- ¿Como jugar? -----

Compilacion:
    gcc *.c -o juego -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

Ejecucion: 
    ./juego

Ejecucion con Valgrind:
    valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./juego

Para comenzar a jugar, primero te pedira que ingreses la ruta de un archivo protagonista. 
Como lo es por ejemplo: Protagonista/protagonista.txt
Tambien te solicitara que cargues (como minimo) 1 gimnasio. Para ello debes ingresar la ruta de dicho archivo. 
Por ejemplo: Gimnasios/gimnasios_kanto.txt 
(En este archivo hay 8 gimnasios)

Una vez completados estos pasos, ya estas listo para comenzar la aventura pokemon!



---- Detalles de implementacion ----

Para desarrollar el TP, realice la implementacion del TDA heap el cual utilizaria luego para guardar los gimnasios pokemon. El motivo por el cual se utilizo el heap es que los gimnasios siempre deben aparecer de menor a mayor en terminos de dificultad, y mediante una funcion comparadora de dificultad, es posible utilizar el heap de forma minimal (El primer elemento del arbol siempre es el elemento menor) y de esta forma ir "sacando" los gimnasios insertados de menor a mayor. 
Tambien utilice los TDAS implementados para entregas anteriores como el TDA Lista, pila e iterador para almacenar pokemones o entrenadores y recorrer dichas listas o pilas.

*Para realizar la implementacion del TP, se crearon las siguientes estructuras: juego_t, pokemon_t, personaje_t, entrenador_t, gimnasio_t, heap_t, lista_t.

--> juego_t-- (Contiene la informacion para ejecutar el juego)

-Un personaje_t en donde se guarda al personaje principal.
-Un heap_t que es un heap minimal en donde se almacenan los gimnasios pokemon segun du dificultad.
-Un bool simular el cual se utiliza para saber el flujo del juego. Si se le debe consultar al usuario o seguir de forma automatica.
-Las 5 funciones de batalla.

--> pokemon_t-- (Contiene los datos del pokemon)

    -Un char* como nombre
    -Un int que indica la velocidad
    -Un int que indica la ataque
    -Un int que indica la defensa
    -Un int que indica el nivel (Utilizado para saber cuantas mejoras recibio dicho pokemon)
    (Todos los pokemones cargados comienzan en nivel 0)

--> personaje_t-- (Contiene la informacion del protagonista)

    -Un char* como nombre
    -Una lista con los pokemones para combatir
    -Una lista con los pokemones obtenidos

--> entrenador_t-- (Contiene la informacion de los entrenadores (LIDER incluido))

    -Un char* como nombre
    -Una lista con los pokemones que posee para combatir.

--> gimnasio_t-- (Contiene la informacion de un gimnasio)

    -Un char* como nombre
    -Un int con la dificultad que este tiene.
    -Un int con el tipo de combate que realiza.
    -Un entrenador_t que seria el LIDER del gimnasio.
    -Una pila en la cual se almacenan los entrenadores que estan en el gimnasio. Elegi una pila ya que el orden en el que salen los entrenadores es   inverso al que estan en el archivo de gimnasio. 

/*******************/
 -Para los combates entre el protagonista y los diferentes entrenadores/LIDERES, se crean dos iteradores. Uno que recorre la lista de pokemones del protagonista y otro que recorre la lista de pokemones del rival. Luego de combatir, se itera sobre la lista pokemon del perdedor, y asi sucesivamente hasta que algun iterador llegue al final de la lista, lo cual significaria que se quedo sin pokemones y perdio.

 -Cita del enunciado: "Una vez derrotado un entrenador rival no se volverá a combatir con él. Sin embargo, si se ha derrotado a un Pokémon del entrenador rival pero no a todos ellos se deberá repetir el combate, es decir, se deberá volver a combatir con el Pokémon que antes fue derrotado." Por este motivo, cuando se vence a un entrenador, este es "desapilado" de la pila del gimnasio y liberado de memoria. Mientras que a los pokemones derrotados no se les hace nada, simplemente se itera sobre su lista y se imprime por pantalla su derrota o victoria.

Algunas aclaraciones:
*En caso de que en un combate peleen dos pokemones con las mismas estadisticas, gana el pokemon del protagonista.
*En cuanto a la carga del archivo protagonista, en caso de encontrar un dato invalido (por ejemplo que un pokemon tenga mal los datos), se cargara el protagonista con los pokemones que se lograron cargar hasta el momento.
*En caso de recibir un archivo con varios gimnasios y que alguno de los gimnasios este con un formato incorrecto, el programa cargara todos los gmnasios validos(completos) previos al gimnasio invalido.

