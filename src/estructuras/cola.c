#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

// Inicializar una cola vacía
void inicializarCola(struct Cola* cola) {
    cola->frente = NULL;
    cola->final = NULL;
    cola->cantidad = 0;
}

// Agregar un elemento al final de la cola
int encolar(struct Cola* cola, int fila, int columna) {
    // Crear nuevo nodo
    struct NodoCola* nuevo = (struct NodoCola*)malloc(sizeof(struct NodoCola));
    if (nuevo == NULL) return 0;  // Error de memoria

    // Asignar datos al nuevo nodo
    nuevo->fila = fila;
    nuevo->columna = columna;
    nuevo->siguiente = NULL;

    // Si la cola está vacía
    if (cola->final == NULL) {
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        // Agregar al final
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }

    cola->cantidad++;
    return 1;  // Éxito
}

// Quitar y retornar el primer elemento de la cola
int desencolar(struct Cola* cola, int* fila, int* columna) {
    if (cola->frente == NULL) return 0;  // Cola vacía

    // Guardar valores del primer elemento
    *fila = cola->frente->fila;
    *columna = cola->frente->columna;

    // Eliminar el primer elemento
    struct NodoCola* temp = cola->frente;
    cola->frente = cola->frente->siguiente;
    free(temp);

    // Si era el último elemento
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    cola->cantidad--;
    return 1;  // Éxito
}

// Verificar si la cola está vacía
int colaVacia(struct Cola* cola) {
    return (cola->frente == NULL);
}

// Liberar toda la memoria usada por la cola
void liberarCola(struct Cola* cola) {
    struct NodoCola* actual = cola->frente;
    while (actual != NULL) {
        struct NodoCola* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    cola->frente = NULL;
    cola->final = NULL;
    cola->cantidad = 0;
}