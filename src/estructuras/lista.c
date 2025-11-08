#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Crear un nuevo nodo
struct Nodo* crearNodo(int fila, int columna) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo != NULL) {
        nuevoNodo->pos.fila = fila;
        nuevoNodo->pos.columna = columna;
        nuevoNodo->siguiente = NULL;
    }
    return nuevoNodo;
}

// Insertar un nodo al inicio de la lista
void insertarAlInicio(struct Nodo** cabeza, int fila, int columna) {
    struct Nodo* nuevoNodo = crearNodo(fila, columna);
    if (nuevoNodo != NULL) {
        nuevoNodo->siguiente = *cabeza;
        *cabeza = nuevoNodo;
    }
}

// Eliminar un nodo de la lista
void eliminarNodo(struct Nodo** cabeza, int fila, int columna) {
    struct Nodo* actual = *cabeza;
    struct Nodo* anterior = NULL;

    // Buscar el nodo a eliminar
    while (actual != NULL && 
           (actual->pos.fila != fila || actual->pos.columna != columna)) {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si se encontró el nodo
    if (actual != NULL) {
        if (anterior == NULL) {
            // Si es el primer nodo
            *cabeza = actual->siguiente;
        } else {
            // Si es un nodo intermedio o final
            anterior->siguiente = actual->siguiente;
        }
        free(actual);
    }
}

// Buscar un nodo en la lista
struct Nodo* buscarNodo(struct Nodo* cabeza, int fila, int columna) {
    struct Nodo* actual = cabeza;
    
    while (actual != NULL) {
        if (actual->pos.fila == fila && actual->pos.columna == columna) {
            return actual;
        }
        actual = actual->siguiente;
    }
    
    return NULL;
}

// Liberar toda la memoria de la lista
void liberarLista(struct Nodo** cabeza) {
    struct Nodo* actual = *cabeza;
    while (actual != NULL) {
        struct Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}

// Mostrar todos los elementos de la lista
void mostrarLista(struct Nodo* cabeza) {
    struct Nodo* actual = cabeza;
    printf("Camino: ");
    while (actual != NULL) {
        printf("(%d,%d) ", actual->pos.fila, actual->pos.columna);
        actual = actual->siguiente;
    }
    printf("\n");
}