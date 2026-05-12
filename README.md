# Dijkstra — Corredor Industrial de Nuevo León
## Proyecto Integrador | Estructura de Datos | FCFM - UANL

---

## Descripción
Implementación en C del algoritmo de Dijkstra aplicado a la red
logística del corredor industrial del Área Metropolitana de Monterrey.
Modela 22 nodos (plantas, CEDIS, parques industriales) y 26 aristas
(vialidades reales de NL) para calcular rutas de mínima distancia.

---

## Estructura del proyecto
```
dijkstra_nl/
├── include/
│   ├── grafo.h       <- Structs y prototipos del grafo
│   └── heap.h        <- Struct y prototipos del min-heap
├── src/
│   ├── main.c        <- Menú interactivo
│   ├── grafo.c       <- Grafo + Dijkstra + impresión
│   ├── heap.c        <- Min-heap (cola de prioridad)
│   └── datos_nl.c    <- Carga de 22 nodos y 26 aristas de NL
├── Makefile
└── README.md
```

---

## Compilación

### Windows (MinGW)
```bash
# Opción 1: con make
make

# Opción 2: línea directa
gcc -Wall -Wextra -std=c11 -Iinclude -o dijkstra_nl.exe src/main.c src/grafo.c src/heap.c src/datos_nl.c
```

### Linux / Mac
```bash
make
# o bien:
gcc -Wall -Wextra -std=c11 -Iinclude -o dijkstra_nl src/main.c src/grafo.c src/heap.c src/datos_nl.c
```

---

## Ejecución
```bash
# Windows
dijkstra_nl.exe

# Linux / Mac
./dijkstra_nl
```

---

## Menú principal
```
[1]  Calcular ruta optima entre dos puntos
[2]  Ver todas las rutas desde un origen
[3]  Ver grafo (lista de adyacencia)
[4]  Ver catalogo de nodos
[5]  Demo automatico (5 rutas de ejemplo)
[0]  Salir
```

---

## Complejidad
| Aspecto         | Valor              |
|-----------------|--------------------|
| Nodos (V)       | 22                 |
| Aristas (E)     | 26                 |
| Tiempo          | O((V+E) log V)     |
| Espacio         | O(V + E)           |

---

## Autores
Facultad de Ciencias Físico-Matemáticas — UANL, 2026
