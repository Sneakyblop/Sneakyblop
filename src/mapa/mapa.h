#ifndef MAPA_H
#define MAPA_H

#define MAX_FILAS 20
#define MAX_COLUMNAS 20

// Símbolos para el mapa
#define VACIO ' '
#define OBSTACULO '#'    
#define ROBOT 'R'        
#define META 'D'         
#define VISITADO '.'     

// Registro (estructura) para el mapa
struct Mapa {
    char matriz[MAX_FILAS][MAX_COLUMNAS];  // Arreglo bidimensional para el mapa
    int filas;                             // Cantidad de filas
    int columnas;                          // Cantidad de columnas
};

// Procedimientos y funciones básicas
void inicializarMapa(struct Mapa* mapa, int filas, int columnas);
int cargarMapaDeArchivo(struct Mapa* mapa, const char* nombreArchivo);
void guardarMapaEnArchivo(struct Mapa* mapa, const char* nombreArchivo);
// Ahora dibujarMapa recibe las coordenadas del robot y de la meta para
// permitir superponer el robot/destino sin alterar la matriz subyacente.
void dibujarMapa(struct Mapa* mapa, int robotFila, int robotColumna, int destFila, int destColumna);
int esPosicionValida(struct Mapa* mapa, int fila, int columna);
int esEspacioLibre(struct Mapa* mapa, int fila, int columna);
// Listar archivos de mapas disponibles en la carpeta 'mapas'
// Devuelve la cantidad de mapas encontrados y llena el arreglo 'nombres' con los nombres (cada nombre hasta 255 chars).
int listarMapasDisponibles(const char* carpeta, char nombres[][256], int max);

// Contar obstáculos en un mapa
int contarObstaculos(struct Mapa* mapa);

// Mostrar coordenadas validas (imprime lista de celdas libres)
void mostrarCoordenadasValidas(struct Mapa* mapa);

#endif