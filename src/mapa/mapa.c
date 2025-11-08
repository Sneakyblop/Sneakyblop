#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "mapa.h"
#ifdef _WIN32
#include <windows.h>
#endif

// Inicializar un mapa vacío con dimensiones dadas
void inicializarMapa(struct Mapa* mapa, int filas, int columnas) {
    if (filas > MAX_FILAS) filas = MAX_FILAS;
    if (columnas > MAX_COLUMNAS) columnas = MAX_COLUMNAS;
    mapa->filas = filas;
    mapa->columnas = columnas;
    for (int i = 0; i < mapa->filas; i++) {
        for (int j = 0; j < mapa->columnas; j++) {
            mapa->matriz[i][j] = VACIO;
        }
    }
}

// Cargar un mapa desde un archivo (lee línea por línea)
int cargarMapaDeArchivo(struct Mapa* mapa, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        return 0;
    }

    char linea[256];
    int fila = 0;
    int maxColumnas = 0;

    while (fgets(linea, sizeof(linea), archivo) != NULL && fila < MAX_FILAS) {
        // quitar salto de línea
        size_t len = strlen(linea);
        if (len > 0 && (linea[len-1] == '\n' || linea[len-1] == '\r')) {
            while (len > 0 && (linea[len-1] == '\n' || linea[len-1] == '\r')) {
                linea[len-1] = '\0';
                len--;
            }
        }

        int columnasLinea = (int)len;
        if (columnasLinea > maxColumnas) maxColumnas = columnasLinea;

        for (int col = 0; col < columnasLinea && col < MAX_COLUMNAS; col++) {
            // Sanitizar: evitar que archivos de mapa precontengan R o D que
            // generen duplicados. Los símbolos de robot/destino se manejan
            // por la estructura Robot, no por la matriz.
            char ch = linea[col];
            if (ch == ROBOT || ch == META) ch = VACIO;
            mapa->matriz[fila][col] = ch;
        }
        // Si la línea es corta, completar con VACIO
        for (int col = columnasLinea; col < MAX_COLUMNAS; col++) {
            // solo inicializamos hasta maxColumnas después
            if (fila == 0 && col >= maxColumnas) mapa->matriz[fila][col] = VACIO;
        }
        fila++;
    }

    mapa->filas = (fila == 0) ? 0 : fila;
    mapa->columnas = (maxColumnas == 0) ? 0 : maxColumnas;
    fclose(archivo);
    return 1;
}

// Guardar mapa en archivo (asume mapa->filas y columnas correctas)
void guardarMapaEnArchivo(struct Mapa* mapa, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error: no se pudo crear el archivo %s\n", nombreArchivo);
        return;
    }
    for (int i = 0; i < mapa->filas; i++) {
        for (int j = 0; j < mapa->columnas; j++) {
            fputc(mapa->matriz[i][j], archivo);
        }
        fputc('\n', archivo);
    }
    fclose(archivo);
}

// Dibujar el mapa con índices de fila y columna para ayudar al usuario
// Ahora recibimos las coordenadas del robot y de la meta para poder
// superponerlos sin escribir en la matriz.
void dibujarMapa(struct Mapa* mapa, int robotFila, int robotColumna, int destFila, int destColumna) {
    if (mapa->filas == 0 || mapa->columnas == 0) {
        printf("(Mapa vacío)\n");
        return;
    }

    // Calcular el ancho necesario para los números de columna
    int ancho_col = 2;  // Mínimo 2 espacios
    if (mapa->columnas > 9) ancho_col = 3;  // 3 espacios para números de 2 dígitos
    if (mapa->columnas > 99) ancho_col = 4; // 4 espacios para números de 3 dígitos

    // Elegir símbolos: por defecto Unicode, pero permitir modo ASCII si
    // la variable de entorno MAP_ASCII está establecida a "1".
    int use_ascii = 0;
    const char* env = getenv("MAP_ASCII");
    if (env && strcmp(env, "1") == 0) use_ascii = 1;
#ifdef _WIN32
    // Si estamos en Windows y la consola no está en UTF-8, forzar ASCII
    if (!use_ascii) {
        UINT cp = GetConsoleOutputCP();
        if (cp != 65001) use_ascii = 1;
    }
#endif

    const char* sym_robot = use_ascii ? "R" : "🤖";
    const char* sym_meta = use_ascii ? "D" : "⭐";
    const char* sym_visit = use_ascii ? "." : "•";
    const char* sym_obs  = use_ascii ? "#" : "█";
    const char* sym_vacio= " ";
    // Imprimir encabezado de columnas (1-based)
    int row_label_width = (mapa->filas > 9) ? 3 : 2;
    printf("%*s", row_label_width + 1, "");
    for (int col = 0; col < mapa->columnas; col++) {
        printf("%*d", ancho_col, col+1);
    }
    printf("\n");

    // Imprimir cada fila con su número (1-based) y celdas con ancho fijo para alineación
    for (int i = 0; i < mapa->filas; i++) {
        printf("%*d ", row_label_width, i+1);
        for (int j = 0; j < mapa->columnas; j++) {
            // Superponer robot/destino: primero verificar coordenadas
            const char* out = sym_vacio;
            if (i == robotFila && j == robotColumna) {
                out = sym_robot;
            } else if (i == destFila && j == destColumna) {
                out = sym_meta;
            } else {
                char c = mapa->matriz[i][j];
                if (c == VISITADO) out = sym_visit;
                else if (c == OBSTACULO) out = sym_obs;
                else out = sym_vacio;
            }
            printf("%*s", ancho_col, out);
        }
        printf("\n");
    }
}

// Verificar si una posición está dentro del mapa
int esPosicionValida(struct Mapa* mapa, int fila, int columna) {
    return (fila >= 0 && fila < mapa->filas && columna >= 0 && columna < mapa->columnas);
}

// Verificar si es espacio libre o la meta
int esEspacioLibre(struct Mapa* mapa, int fila, int columna) {
    if (!esPosicionValida(mapa, fila, columna)) return 0;
    char c = mapa->matriz[fila][columna];
    return (c == VACIO || c == META);
}

// Listar archivos .txt disponibles en la carpeta 'mapas'
// Devuelve la cantidad de archivos encontrados y llena 'nombres' con los nombres (hasta 'max').
int listarMapasDisponibles(const char* carpeta, char nombres[][256], int max) {
    DIR* dir = opendir(carpeta);
    if (dir == NULL) {
        printf("No se pudo acceder a la carpeta de mapas '%s'\n", carpeta);
        return 0;
    }
    struct dirent* ent;
    int contador = 0;

    printf("\n╔══════════ Mapas Disponibles ══════════╗\n");
    printf("║                                       ║\n");

    while ((ent = readdir(dir)) != NULL && contador < max) {
        if (ent->d_name[0] == '.') continue;
        const char* ext = strrchr(ent->d_name, '.');
        if (ext && strcmp(ext, ".txt") == 0) {
            contador++;
            strncpy(nombres[contador-1], ent->d_name, 255);
            nombres[contador-1][255] = '\0';
            printf("║  %2d. %-30s  ║\n", contador, ent->d_name);
        }
    }

    if (contador == 0) {
        printf("║     No hay mapas disponibles        ║\n");
    }

    printf("║                                       ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    printf("Para cargar un mapa, elija el número en la lista (opción 1) o\n");
    printf("use la opción 2 y escriba la ruta completa (ej: mapas/mapa1.txt)\n\n");

    closedir(dir);
    return contador;
}

// Contar obstáculos en el mapa
int contarObstaculos(struct Mapa* mapa) {
    int count = 0;
    for (int i = 0; i < mapa->filas; i++) {
        for (int j = 0; j < mapa->columnas; j++) {
            if (mapa->matriz[i][j] == OBSTACULO) count++;
        }
    }
    return count;
}

// Función para mostrar coordenadas válidas
void mostrarCoordenadasValidas(struct Mapa* mapa) {
    printf("\nCoordenadas validas disponibles:\n");
    printf("--------------------------------\n");
    for (int i = 0; i < mapa->filas; i++) {
        for (int j = 0; j < mapa->columnas; j++) {
            if (esEspacioLibre(mapa, i, j)) {
                printf("(%d,%d) ", i+1, j+1);
            }
        }
    }
    printf("\n--------------------------------\n");
}