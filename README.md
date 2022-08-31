# IA_21-22

## Índice
- [Información general](#información-general).
- [Ejecución](#ejecución).
- [Información general técnica](#información-general-técnica).
- [Participantes](#participantes).



## Información general
Implementación de estrategias de búsqueda como propuesta de resolución para la determinación de trayectorias óptimas para taxis autónomos<br>

## Ejecución
Para ejecutar el programa debe estar en la carpeta `build/` y hay disponible un makefile con las opciones:
* `make`: Compila el programa.
* `make clean`: Borra los ejecutables.

Para ejecutar el programa:
* `./Taxi`: ejecuta el programa.

comentario: explicar el funcionamiento y opciones del programa:
* Salida por consola : La solución del mapa se muestra por pantalla.
* Salida por fichero : La solución del mapa se imprime en un fichero.
* Modo Aleatorio : Se generan los obstáculos aleatoriamente.
* Modo Manual : Se carga un fichero con el mapa ya creado.
* 4 direcciones : se desarrollan los algoritmos con 4 direcciones.
* 8 direcciones : se desarrollan los algoritmos con 8 direcciones.
* Función Euclídeo : se utiliza la función de búsqueda euclídea.
* Función de Manhattan : Se utilizará la función de búsqueda de Manhattan.
* Función Chebyshev : Se utilizará la función de búsqueda Chebyshev.

## Ficheros
Para ejecutar el programa introduciendole un fichero, deberemos preparar el fichero con anterioridad.
El formato que debe tener el fichero es el siguiente:
* M N
* 2 0 0 1
* 1 1 0 0
* 0 0 0 0
* 3 1 1 1

M y N son las dimensiones X e Y de la matriz.
0 indica un camino posible.
1 indica un obstaculo.
2 indica el inicio.
3 indica el fin.

## Información general técnica
Sistema de gestión de versiones y archivos: GitHub <br>
Ramas: main <br>
Lenguajes del proyecto: C++, Makefile<br>
Lenguaje: Español <br>

Organización de archivos:
* README.md: Información general del proyecto, así como participantes y especificaciones técnicas.
* code/: Desarrollo del código, con sus cabeceras, implementaciones, los datos y la carpeta tests/.


## Participantes
A continuación se listan los participantes del proyecto:
* Stephanie Andreina Arismendi Escobar (alu0101351728)
* Dana Belén Choque Zárate (alu0101328348)
* Gabriel Alberto Luis Freitas (alu0101348421)


### Extra
Informe de la práctica: [Informe De Búsqueda](https://docs.google.com/document/d/1uKA5Q1jRwRV-i3AIdlaz69VMC7k5pFXL/edit?usp=sharing&ouid=112592623507564456368&rtpof=true&sd=true). <br>
Este repositorio: [IA_21-22](https://github.com/Dncz/IA_21-22.git). <br>
