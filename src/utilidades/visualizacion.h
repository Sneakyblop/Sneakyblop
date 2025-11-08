#ifndef VISUALIZACION_H
#define VISUALIZACION_H

#include "../mapa/mapa.h"
#include "../robot/robot.h"

// Funciones de visualización
void limpiarPantalla();
void mostrarMenu();
// Usar las estructuras actuales
void visualizarEstado(struct Mapa* mapa, struct Robot* robot);
void mostrarMensajeError(const char* mensaje);
// Mostrar un saludo de bienvenida
void mostrarBienvenida(const char* usuario);

#endif