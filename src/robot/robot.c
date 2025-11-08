#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"

// Inicializar un nuevo robot
void inicializarRobot(struct Robot* robot, int filaInicial, int columnaInicial) {
    robot->fila = filaInicial;
    robot->columna = columnaInicial;
    robot->filaDestino = -1;
    robot->columnaDestino = -1;
}

// Establecer el destino del robot
void establecerDestino(struct Robot* robot, int fila, int columna) {
    robot->filaDestino = fila;
    robot->columnaDestino = columna;
}

// Mover el robot en una dirección específica
int moverRobot(struct Robot* robot, struct Mapa* mapa, enum Direccion dir) {
    int nuevaFila = robot->fila;
    int nuevaColumna = robot->columna;

    // Calcular nueva posición según la dirección
    switch (dir) {
        case ARRIBA:
            nuevaFila--;
            break;
        case DERECHA:
            nuevaColumna++;
            break;
        case ABAJO:
            nuevaFila++;
            break;
        case IZQUIERDA:
            nuevaColumna--;
            break;
        default:
            return 0;
    }

    // Verificar si el movimiento es válido
    if (!esPosicionValida(mapa, nuevaFila, nuevaColumna)) return 0;
    if (!esEspacioLibre(mapa, nuevaFila, nuevaColumna)) return 0;

    // Marcar la posición anterior como visitada (si no era la meta ni un obstáculo)
    if (esPosicionValida(mapa, robot->fila, robot->columna)) {
        if (mapa->matriz[robot->fila][robot->columna] != OBSTACULO &&
            mapa->matriz[robot->fila][robot->columna] != META) {
            mapa->matriz[robot->fila][robot->columna] = VISITADO;
        }
    }

    // Actualizar la posición del robot
    robot->fila = nuevaFila;
    robot->columna = nuevaColumna;

        // No modificar la matriz del mapa aquí; la visualización superpone el robot.

    return 1;
}

// Buscar el camino más corto usando Cola (BFS)
int buscarCaminoOptimo(struct Robot* robot, struct Mapa* mapa) {
    struct Cola cola;
    struct PosicionAnterior anterior[MAX_FILAS][MAX_COLUMNAS];
    int visitado[MAX_FILAS][MAX_COLUMNAS] = {0};
    int dx[] = {-1, 0, 1, 0};  
    int dy[] = {0, 1, 0, -1};  
    int i, encontrado = 0;

    // Validar destino
    if (!esPosicionValida(mapa, robot->filaDestino, robot->columnaDestino)) return 0;

    // Inicializar estructuras
    inicializarCola(&cola);

    // Marcar posición inicial como visitada
    visitado[robot->fila][robot->columna] = 1;
    encolar(&cola, robot->fila, robot->columna);

    // BFS
    while (!colaVacia(&cola) && !encontrado) {
        int filaActual, columnaActual;
        desencolar(&cola, &filaActual, &columnaActual);

        // Si llegamos al destino
        if (filaActual == robot->filaDestino && columnaActual == robot->columnaDestino) {
            encontrado = 1;
            break;
        }

        for (i = 0; i < 4; i++) {
            int nf = filaActual + dx[i];
            int nc = columnaActual + dy[i];
            if (esPosicionValida(mapa, nf, nc) && esEspacioLibre(mapa, nf, nc) && !visitado[nf][nc]) {
                visitado[nf][nc] = 1;
                anterior[nf][nc].fila = filaActual;
                anterior[nf][nc].columna = columnaActual;
                encolar(&cola, nf, nc);
            }
        }
    }

    if (!encontrado) {
        // Analizar por qué no se puede llegar
        int rodeadoObstaculos = 1;
        for (i = 0; i < 4; i++) {
            int nf = robot->filaDestino + dx[i];
            int nc = robot->columnaDestino + dy[i];
            if (esPosicionValida(mapa, nf, nc) && esEspacioLibre(mapa, nf, nc)) {
                rodeadoObstaculos = 0;
                break;
            }
        }
        if (rodeadoObstaculos) {
            printf("\nError: El destino esta completamente rodeado de obstaculos.\n");
        } else {
            printf("\nError: No hay un camino posible al destino. Hay obstaculos bloqueando todas las rutas posibles.\n");
        }
        liberarCola(&cola);
        return 0;
    }

    // Reconstruir camino (desde destino hacia el inicio) y marcar ruta en el mapa
    struct Pila camino;
    inicializarPila(&camino);
    int filaActual = robot->filaDestino;
    int columnaActual = robot->columnaDestino;

    while (filaActual != robot->fila || columnaActual != robot->columna) {
        apilar(&camino, filaActual, columnaActual);
        int tf = anterior[filaActual][columnaActual].fila;
        int tc = anterior[filaActual][columnaActual].columna;
        filaActual = tf;
        columnaActual = tc;
    }

    // Marcar los pasos del camino como visitados (excepto la posicion inicial)
    while (!pilaVacia(&camino)) {
        int rf, rc;
        desapilar(&camino, &rf, &rc);
        // No sobrescribir la meta si existe; marcar intermedios como VISITADO
        if (!(rf == robot->filaDestino && rc == robot->columnaDestino)) {
            mapa->matriz[rf][rc] = VISITADO;
        }
    }

    // Finalmente, colocar el robot en la meta (actualizar estructura sin escribir 'R' en la matriz)
    robot->fila = robot->filaDestino;
    robot->columna = robot->columnaDestino;

    liberarCola(&cola);
    return 1;
}
