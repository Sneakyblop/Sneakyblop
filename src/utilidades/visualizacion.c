#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "visualizacion.h"
#ifdef _WIN32
#include <windows.h>
#endif

// Determina si la terminal soporta UTF-8 
static int terminal_supports_utf8() {
    const char* env = getenv("MAP_ASCII");
    if (env && strcmp(env, "1") == 0) return 0; // forzar ASCII
#ifdef _WIN32
    // En Windows comprobamos la code page de salida de la consola
    UINT cp = GetConsoleOutputCP();
    return (cp == 65001);
#else
    return 1;
#endif
}

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarMenu() {
    if (terminal_supports_utf8()) {
        printf("\n╔═══════════════ Simulador MapQuest ═══════════════╗\n");
        printf("║  1. Ver mapas disponibles                         ║\n");
        printf("║  2. Cargar mapa desde archivo                     ║\n");
        printf("║  3. Establecer posicion del robot 🤖             ║\n");
        printf("║  4. Establecer destino ⭐                         ║\n");
        printf("║  5. Buscar camino mas corto (BFS)                ║\n");
        printf("║  6. Guardar mapa                                  ║\n");
        printf("║  7. Ver coordenadas validas                       ║\n");
        printf("║  0. Salir                                         ║\n");
        printf("╚══════════════════════════════════════════════════╝\n");
    } else {
        // Version ASCII mas compatible (sin acentos)
        printf("\n=== Simulador MapQuest ===\n");
        printf(" 1. Ver mapas disponibles\n");
        printf(" 2. Cargar mapa desde archivo\n");
        printf(" 3. Establecer posicion del robot (R)\n");
        printf(" 4. Establecer destino (D)\n");
        printf(" 5. Buscar camino mas corto (BFS)\n");
        printf(" 6. Guardar mapa\n");
        printf(" 7. Ver coordenadas validas\n");
        printf(" 0. Salir\n");
    }
    printf("\nIngrese una opcion (ej: 1) y presione Enter: ");
}


void visualizarEstado(struct Mapa* mapa, struct Robot* robot) {
    limpiarPantalla();
    printf("Estado actual del mapa:\n");
    dibujarMapa(mapa, robot->fila, robot->columna, robot->filaDestino, robot->columnaDestino);
    // Mostrar posiciones en base 1 para los usuarios
    printf("\nPosicion actual del robot: (%d %d)\n", robot->fila + 1, robot->columna + 1);
    if (robot->filaDestino != -1) {
        printf("Destino: (%d %d)\n", robot->filaDestino + 1, robot->columnaDestino + 1);
    }
}

void mostrarBienvenida(const char* usuario) {
    limpiarPantalla();
    if (terminal_supports_utf8()) {
        printf("\n╔════════════════════════════════════════════════════════════╗\n");
        printf("║             Bienvenido/a al Simulador MapQuest             ║\n");
        printf("║                                                            ║\n");
        printf("║  ¡Hola, %s!", usuario);
        // Rellenar con espacios hasta el final del cuadro
        for (int i = strlen(usuario); i < 45; i++) printf(" ");
        printf("║\n");
        printf("║                                                            ║\n");
        printf("║  Este programa te ayudará a:                              ║\n");
        printf("║  • Explorar diferentes mapas                              ║\n");
        printf("║  • Colocar un robot y establecer su destino              ║\n");
        printf("║  • Encontrar el camino más corto entre dos puntos        ║\n");
        printf("║                                                            ║\n");
        printf("║  Formato de coordenadas: fila columna (Ejemplo: 4 3)      ║\n");
        printf("║  Las coordenadas comienzan desde 1                        ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n\n");
        printf("Presiona Enter para comenzar...");
    } else {
        // Mensaje ASCII simple para terminales sin UTF-8 (sin acentos)
        printf("\n=== Bienvenido/a al Simulador MapQuest ===\n");
        printf("Hola, %s!\n\n", usuario);
        printf("Este programa te ayudara a:\n");
        printf(" - Explorar diferentes mapas\n");
        printf(" - Colocar un robot y establecer su destino\n");
        printf(" - Encontrar el camino mas corto entre dos puntos\n\n");
        printf("Formato de coordenadas: fila columna (Ejemplo: 4 3). Las coordenadas comienzan desde 1.\n\n");
        printf("Presiona Enter para comenzar...");
    }
}

void mostrarMensajeError(const char* mensaje) {
    printf("\nError: %s\n", mensaje);
}

void mostrarDespedida() {
    limpiarPantalla();
    if (terminal_supports_utf8()) {
        printf("\n╔════════════════════════════════════════════════════════════╗\n");
        printf("║          ¡Gracias por utilizar MapQuest! 🤖               ║\n");
        printf("║                                                            ║\n");
        printf("║  Esperamos que hayas disfrutado usando el simulador       ║\n");
        printf("║  y que te haya ayudado a entender mejor los conceptos     ║\n");
        printf("║  de búsqueda de caminos y navegación de robots.           ║\n");
        printf("║                                                            ║\n");
        printf("║              ¡Hasta la próxima! 👋                        ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n\n");
    } else {
        printf("\n===========================================\n");
        printf("     Gracias por utilizar MapQuest!      \n");
        printf("-------------------------------------------\n");
        printf("  Esperamos que hayas disfrutado usando   \n");
        printf("  el simulador y que te haya ayudado a    \n");
        printf("  entender mejor los conceptos de busqueda\n");
        printf("  de caminos y navegacion de robots.      \n");
        printf("                                          \n");
        printf("          Hasta la proxima!              \n");
        printf("===========================================\n\n");
    }
}