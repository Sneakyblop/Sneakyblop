# Robot Pathfinding Simulator

Este proyecto implementa un simulador de navegación de robot en un entorno 2D usando el lenguaje C. El robot es capaz de encontrar rutas óptimas en un mapa con obstáculos utilizando el algoritmo de búsqueda en amplitud (BFS).

## Estructura del Proyecto

```
src/
├── main.c              # Programa principal
├── mapa/               # Módulo de gestión del mapa
│   ├── mapa.c
│   └── mapa.h
├── robot/              # Módulo del robot
│   ├── robot.c
│   └── robot.h
├── estructuras/        # Estructuras de datos
│   ├── cola.c         # Implementación de cola para BFS
│   ├── cola.h
│   ├── pila.c         # Implementación de pila
│   ├── pila.h
│   ├── lista.c        # Implementación de lista enlazada
│   └── lista.h
└── utilidades/         # Funciones de utilidad
    ├── visualizacion.c # Funciones de visualización
    └── visualizacion.h

mapas/                  # Mapas de prueba
├── mapa1.txt
├── mapa2.txt
└── mapa3.txt
```

## Compilación

Para compilar el proyecto, use el siguiente comando en la terminal:

```bash
gcc src/main.c src/mapa/mapa.c src/robot/robot.c src/estructuras/cola.c src/estructuras/pila.c src/estructuras/lista.c src/utilidades/visualizacion.c -o robot_simulator
```

## Uso

1. Ejecute el programa:
   ```bash
   ./robot_simulator
   ```

2. El menú principal ofrece las siguientes opciones:
   - Cargar mapa desde archivo
   - Establecer posición inicial del robot
   - Establecer destino
   - Buscar ruta
   - Guardar mapa
   - Salir

## Formato del Mapa

Los mapas son archivos de texto con el siguiente formato:
- ' ' (espacio): Celda libre
- '#': Obstáculo
- 'R': Posición del robot
- 'D': Destino
- '.': Camino encontrado

Ejemplo de mapa:
```
##########
#    #   #
# R  #  D#
#    #   #
##########
```

## Características

- Navegación en entorno 2D
- Detección de obstáculos
- Búsqueda de ruta óptima usando BFS
- Visualización en tiempo real
- Carga y guardado de mapas
- Manejo de errores robusto