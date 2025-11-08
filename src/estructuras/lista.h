#ifndef LISTA_H
#define LISTA_H

// Estructura para almacenar una posición en el mapa
struct Posicion {
    int fila;
    int columna;
};

// Estructura para un nodo de la lista
struct Nodo {
    struct Posicion pos;
    struct Nodo* siguiente;
};

// Funciones básicas de la lista
struct Nodo* crearNodo(int fila, int columna);
void insertarAlInicio(struct Nodo** cabeza, int fila, int columna);
void eliminarNodo(struct Nodo** cabeza, int fila, int columna);
struct Nodo* buscarNodo(struct Nodo* cabeza, int fila, int columna);
void liberarLista(struct Nodo** cabeza);
void mostrarLista(struct Nodo* cabeza);

#endif