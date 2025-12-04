#ifndef PROGRAMACIÓN_ORIENTADA_A_OBJETOS_TABLERO_H
#define PROGRAMACIÓN_ORIENTADA_A_OBJETOS_TABLERO_H

// Inclusiones necesarias para las declaraciones
#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>

// Constantes globales de la pantalla
const int WIDTH=810, HEIGHT=250; /**< Dimensiones de la pantalla de juego. */
const int dW=9, dH=5; /**< Tamaño del "pixel" (dimensiones de cada casilla de la cuadrícula). */

/**
 * @brief Estructura que representa una casilla individual en el tablero.
 * * Contiene todas las propiedades necesarias para determinar el estado y
 * función de cada posición en el juego (Serpientes y Escaleras).
 */
struct coord {
    int c; /**< Coordenada de columna (eje X) de la casilla. */
    int f; /**< Coordenada de fila (eje Y) de la casilla. */
    bool ocupado=false; /**< Indica si la casilla está ocupada por un jugador o una característica especial. */
    int E=0; /**< 1 si la casilla es parte de una escalera. */
    int S=0; /**< 1 si la casilla es parte de una serpiente. */
    int infi=0; /**< 1=inicio (head) de la escalera/serpiente, 2=final (tail). */
    int pos=0; /**< Guarda el índice de la casilla especial a la que pertenece (e.g., esc[pos]). */
    int H=0; /**< Guarda el índice de la casilla de destino (head o tail) de la característica especial. */
};

/**
 * @brief Estructura auxiliar para manejar offsets de dibujo.
 * * Utilizada para las coordenadas relativas al dibujar la forma del cuerpo de la serpiente
 * en la consola.
 */
struct coxy {
    int x; /**< Desplazamiento en el eje X para el dibujo. */
    int y; /**< Desplazamiento en el eje Y para el dibujo. */
};

// Declaraciones de funciones globales (implementadas en Tablero.cpp)
void gotoxy(int x,int y);
void dibujo(char plano[HEIGHT/dH][WIDTH/dW+1], int A, int B, char c);

/**
 * @brief Clase principal que encapsula toda la lógica y el estado del juego Serpientes y Escaleras.
 * * Se encarga de la generación del tablero, posicionamiento aleatorio de las características especiales,
 * el dibujo en consola y la gestión del movimiento de los jugadores.
 */
class Tablero {
private:
    coord esc[9]; /**< Almacena el inicio de las 9 escaleras. */
    coord esf[9]; /**< Almacena el final de las 9 escaleras. */
    coord ser[9]; /**< Almacena el inicio de las 9 serpientes. */
    coord sef[9]; /**< Almacena el final de las 9 serpientes. */
    int xn[9]={10,10,10,8,8,8,8,8,8}; /**< Control de coordenadas aleatorias para escaleras. */
    int xm[9]={1,1,1,1,1,1,3,3,3}; /**< Control de coordenadas aleatorias para escaleras. */
    coxy xys[13]={{1,0},{2,1},{3,2},{3,3},{3,4},{3,5},{4,6},{5,7},{6,8},{6,9},{7,9},{8,10},{9,10}}; /**< Coordenadas relativas para dibujar el cuerpo de la serpiente. */
    int xf[6]={0,0,0,1,1,1}; /**< Coordenadas relativas de dibujo para diferentes tipos de escaleras. */

public:
    /**
     * @brief Dibuja los márgenes exteriores del tablero en el plano de caracteres.
     * @param plano Matriz de caracteres que representa el plano de dibujo de la consola.
     */
    void Ptablero (char plano[HEIGHT/dH][WIDTH/dW+1]);

    /**
     * @brief Dibuja el contenido de cada casilla (los números centrales) y mapea las coordenadas lógicas.
     * @param plano Matriz de caracteres que representa el plano de dibujo de la consola.
     */
    void pintar (char plano[HEIGHT/dH][WIDTH/dW+1]);

    /**
     * @brief Genera y asigna las posiciones aleatorias de las escaleras y serpientes.
     */
    void valor ();

    /**
     * @brief Dibuja las escaleras en el plano de la consola usando diferentes estilos.
     * @param plano Matriz de caracteres que representa el plano de dibujo de la consola.
     */
    void Pescaleras(char plano[HEIGHT/dH][WIDTH/dW+1]);

    /**
     * @brief Dibuja las serpientes en el plano de la consola.
     * @param plano Matriz de caracteres que representa el plano de dibujo de la consola.
     */
    void Pserpientes (char plano[HEIGHT/dH][WIDTH/dW+1]);

    /**
     * @brief Dibuja un personaje (jugador) en su posición actual.
     * @param plano Matriz de caracteres que representa el plano de dibujo.
     * @param p Posición actual del jugador (índice en el arreglo dato[]).
     * @param n Carácter ASCII del jugador (e.g., '1', '2').
     */
    void personaje(char plano[HEIGHT/dH][WIDTH/dW+1],int& p, char n);

    /**
     * @brief Ejecuta la lógica de movimiento, avance y chequeo de casillas especiales.
     * @param p [in,out] Posición actual del jugador (se actualiza).
     * @param pap [in,out] Indicador de pausa de movimiento.
     * @param act [in,out] Booleano que indica si la animación de movimiento está activa.
     * @param D [in,out] Valor del dado tirado para este movimiento.
     * @param con [in,out] Contador del movimiento actual.
     */
    void ejecucion(int& p, int& pap, bool& act,int& D, int& con);

    /**
     * @brief Vacía y reinicializa todas las estructuras de datos del tablero y casillas especiales.
     */
    void vaciar();

    /**
     * @brief Muestra las instrucciones del juego en la consola.
     */
    void instructions ();
};

#endif //PROGRAMACIÓN_ORIENTADA_A_OBJETOS_TABLERO_H