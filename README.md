# Robot Pathfinding Simulator

Este proyecto implementa un simulador de navegación de robot en un entorno 2D usando el lenguaje C. El robot es capaz de encontrar rutas óptimas en un mapa con obstáculos utilizando el algoritmo de búsqueda en amplitud (BFS).

## Estructura del Proyecto

```
4 carpetas principales:
-.vscode donde dentro debe estar un archivo .json
-bin, donde dentro debe estar el simulador del robot
-mapas, donde dentro debe contener 5 ejemplos de mapas que el usuario puede usar
-src, donde dentro deben haber 4 carpetas mas un archivo llamado "main.c"
```

## Uso

1. Ejecute el programa en terminal cmd: 
debe estar en la carpeta principal llamada "proyecto c" y de ahi ejecutar el siguiente comando
.\bin\robot_simulator.exe

2. El menú principal ofrece las siguientes opciones:
   - Cargar mapa desde archivo
   - Establecer posición inicial del robot
   - Establecer destino
   - Buscar ruta
   - Guardar mapa
   - Salir
   - entro otros (primeramente pide nombre del usuario)

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

