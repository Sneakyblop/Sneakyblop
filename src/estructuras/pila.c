#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

// Inicializar una pila vacía
void inicializarPila(struct Pila* pila) {
    pila->tope = NULL;
    pila->cantidad = 0;
}

// Agregar un elemento en el tope de la pila
int apilar(struct Pila* pila, int fila, int columna) {
    // Crear nuevo nodo
    struct NodoPila* nuevo = (struct NodoPila*)malloc(sizeof(struct NodoPila));
    if (nuevo == NULL) return 0;  // Error de memoria

    // Asignar datos al nuevo nodo
    nuevo->fila = fila;
    nuevo->columna = columna;
    
    // Insertar al principio
    nuevo->siguiente = pila->tope;
    pila->tope = nuevo;
    
    pila->cantidad++;
    return 1;  // Éxito
}

// Quitar y retornar el elemento del tope
int desapilar(struct Pila* pila, int* fila, int* columna) {
    if (pila->tope == NULL) return 0;  // Pila vacía

    // Guardar valores del tope
    *fila = pila->tope->fila;
    *columna = pila->tope->columna;

    // Eliminar el nodo del tope
    struct NodoPila* temp = pila->tope;
    pila->tope = pila->tope->siguiente;
    free(temp);

    pila->cantidad--;
    return 1;  // Éxito
}

// Verificar si la pila está vacía
int pilaVacia(struct Pila* pila) {
    return (pila->tope == NULL);
}

// Liberar toda la memoria usada por la pila
void liberarPila(struct Pila* pila) {
    while (!pilaVacia(pila)) {
        int fila, columna;
        desapilar(pila, &fila, &columna);
    }
    pila->cantidad = 0;
}