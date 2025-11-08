#ifndef PILA_H
#define PILA_H

// Estructura para un elemento de la pila
struct NodoPila {
    int fila;
    int columna;
    struct NodoPila* siguiente;
};

// Estructura principal de la pila
struct Pila {
    struct NodoPila* tope;   // Elemento superior
    int cantidad;            // Cantidad de elementos
};

// Operaciones básicas de la pila
void inicializarPila(struct Pila* pila);
int apilar(struct Pila* pila, int fila, int columna);
int desapilar(struct Pila* pila, int* fila, int* columna);
int pilaVacia(struct Pila* pila);
void liberarPila(struct Pila* pila);

#endif