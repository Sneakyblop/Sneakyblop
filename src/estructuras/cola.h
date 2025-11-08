// cola.h - Implementación de una cola para el manejo de la búsqueda de rutas
#ifndef COLA_H
#define COLA_H

// Estructura para un elemento de la cola
struct NodoCola {
    int fila;
    int columna;
    struct NodoCola* siguiente;
};

// Estructura principal de la cola
struct Cola {
    struct NodoCola* frente;  // Primer elemento
    struct NodoCola* final;   // Último elemento
    int cantidad;             // Cantidad de elementos
};

// Operaciones básicas de la cola
void inicializarCola(struct Cola* cola);
int encolar(struct Cola* cola, int fila, int columna);
int desencolar(struct Cola* cola, int* fila, int* columna);
int colaVacia(struct Cola* cola);
void liberarCola(struct Cola* cola);

#endif