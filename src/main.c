#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa/mapa.h"
#include "robot/robot.h"
#include "utilidades/visualizacion.h"

// Constantes del programa
#define FILAS_INICIAL 10
#define COLUMNAS_INICIAL 10

// Las funciones de visualización (limpiarPantalla y mostrarMenu)
// están definidas en `utilidades/visualizacion.c` y declaradas en
// `utilidades/visualizacion.h`. Se usan desde aquí.

// Programa principal
int main() {
    struct Mapa mapa;
    struct Robot robot;
    int opcion = -1;
    char archivoEntrada[200];
    char usuario[50];
    int fila, columna;
    char mapaActual[260] = "Mapa inicial generado";

    // Inicialización
    inicializarMapa(&mapa, FILAS_INICIAL, COLUMNAS_INICIAL);
    inicializarRobot(&robot, 0, 0);
    // No escribir 'R' en la matriz: la visualizacion superpone el robot.

    // Pedir nombre de usuario
    printf("Por favor, ingrese su nombre: ");
    if (fgets(usuario, sizeof(usuario), stdin) != NULL) {
        // quitar salto de línea final
        size_t ln = strlen(usuario) - 1;
        if (usuario[ln] == '\n') usuario[ln] = '\0';
    } else {
        strcpy(usuario, "Usuario");
    }

    mostrarBienvenida(usuario);
    getchar(); // Esperar a que el usuario presione Enter tras la bienvenida

    // Ciclo principal del programa
    do {
        visualizarEstado(&mapa, &robot);
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            // limpiar entrada inválida
            while (getchar() != '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1: {
                // listar mapas y permitir cargar por número
                char nombres[100][256];
                int cantidad = listarMapasDisponibles("mapas", nombres, 100);
                if (cantidad > 0) {
                    int seleccion = -1;
                    printf("Ingrese el número del mapa a cargar (0 para volver): ");
                    if (scanf("%d", &seleccion) == 1) {
                        while (getchar() != '\n');
                        if (seleccion > 0 && seleccion <= cantidad) {
                            snprintf(archivoEntrada, sizeof(archivoEntrada), "mapas/%s", nombres[seleccion-1]);
                            if (!cargarMapaDeArchivo(&mapa, archivoEntrada)) {
                                printf("No se pudo abrir '%s'.\n", archivoEntrada);
                            } else {
                                strcpy(mapaActual, archivoEntrada);
                                printf("Mapa '%s' cargado: %d filas x %d columnas, %d obstaculos\n",
                                       mapaActual, mapa.filas, mapa.columnas, contarObstaculos(&mapa));
                            }
                        }
                    } else {
                        while (getchar() != '\n');
                    }
                }
            } break;

            case 2:
                printf("Ingrese nombre de archivo (por ejemplo: mapas/mapa1.txt): ");
                if (scanf("%199s", archivoEntrada) == 1) {
                    while (getchar() != '\n');
                    if (!cargarMapaDeArchivo(&mapa, archivoEntrada)) {
                        printf("No se pudo abrir '%s'. Asegúrese de que el archivo exista en la carpeta mapas/ o escriba la ruta completa.\n", archivoEntrada);
                    } else {
                        strcpy(mapaActual, archivoEntrada);
                        printf("Mapa '%s' cargado: %d filas x %d columnas, %d obstaculos\n",
                               mapaActual, mapa.filas, mapa.columnas, contarObstaculos(&mapa));
                    }
                } else {
                    while (getchar() != '\n');
                }
                break;

            case 3:
                printf("Ingrese la posición del robot (fila columna). Ejemplo: 4 3 (base 1): ");
                if (scanf("%d %d", &fila, &columna) == 2) {
                    while (getchar() != '\n');
                    // Convertir entrada 1-based a 0-based internamente
                    fila -= 1; columna -= 1;
                    if (esPosicionValida(&mapa, fila, columna) && esEspacioLibre(&mapa, fila, columna)) {
                        // Actualizar solo la estructura Robot; la matriz no guarda R
                        inicializarRobot(&robot, fila, columna);
                        printf("Posicion del robot actualizada a (%d %d).\n", fila+1, columna+1);
                    } else {
                        printf("Posicion invalida o ocupada. Use la opcion 7 para ver coordenadas validas.\n");
                    }
                } else {
                    printf("Formato invalido. Debe ingresar: fila espacio columna (ej: 4 3)\n");
                    while (getchar() != '\n');
                }
                break;

            case 4:
                printf("Ingrese la posición del destino (fila columna). Ejemplo: 4 3 (base 1): ");
                if (scanf("%d %d", &fila, &columna) == 2) {
                    while (getchar() != '\n');
                    fila -= 1; columna -= 1;
                    if (esPosicionValida(&mapa, fila, columna) && esEspacioLibre(&mapa, fila, columna)) {
                        establecerDestino(&robot, fila, columna);
                        // No escribir 'D' en la matriz; se superpone en la visualizacion.
                        printf("Destino establecido en (%d %d).\n", fila+1, columna+1);
                    } else {
                        printf("Posicion invalida o ocupada. Use la opcion 7 para ver coordenadas validas.\n");
                    }
                } else {
                    printf("Formato invalido. Debe ingresar: fila espacio columna (ej: 4 3)\n");
                    while (getchar() != '\n');
                }
                break;

            case 5:
                if (robot.filaDestino == -1) {
                    printf("Primero establezca un destino con la opción 4.\n");
                } else {
                    printf("Buscando el camino mas corto en '%s'...\n", mapaActual);
                    if (buscarCaminoOptimo(&robot, &mapa)) {
                        printf("Camino encontrado: el robot llego a la meta.\n");
                    } else {
                        printf("No existe un camino posible hacia la meta en este mapa.\n");
                    }
                }
                break;

            case 6:
                printf("Ingrese el nombre de archivo para guardar el mapa (ej: mapas/mi_mapa.txt): ");
                scanf("%s", archivoEntrada);
                guardarMapaEnArchivo(&mapa, archivoEntrada);
                printf("Mapa guardado en '%s'\n", archivoEntrada);
                break;

            case 7:
                // Mostrar coordenadas validas disponibles
                mostrarCoordenadasValidas(&mapa);
                break;

            case 0:
                printf("Gracias por utilizar MapQuest, grupo 18, Laboratorio C, AED 2025, Comision C\n");
                break;

            default:
                printf("Opción inválida. Ingrese un número del menú.\n");
        }

        printf("\nPresione Enter para continuar...");
        while (getchar() != '\n');

    } while (opcion != 0);

    return 0;
}