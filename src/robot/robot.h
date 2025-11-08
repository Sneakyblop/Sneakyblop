#ifndef ROBOT_H
#define ROBOT_H

#include "../mapa/mapa.h"
#include "../estructuras/cola.h"
#include "../estructuras/pila.h"

// Estructura para guardar una posición anterior
struct PosicionAnterior {
    int fila;
    int columna;
};

// Estructura del robot
struct Robot {
    int fila;           // Fila actual
    int columna;        // Columna actual
    int filaDestino;    // Fila destino
    int columnaDestino; // Columna destino
};

// Direcciones de movimiento
enum Direccion {
    ARRIBA = 1,
    DERECHA = 2,
    ABAJO = 3,
    IZQUIERDA = 4
};

// Funciones del robot
void inicializarRobot(struct Robot* robot, int filaInicial, int columnaInicial);
void establecerDestino(struct Robot* robot, int fila, int columna);
int moverRobot(struct Robot* robot, struct Mapa* mapa, enum Direccion dir);
int buscarCaminoOptimo(struct Robot* robot, struct Mapa* mapa);

#endif