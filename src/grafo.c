#include "../include/grafo.h"
#include "../include/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ════════════════════════════════════════════════════════
   GESTIÓN DEL GRAFO
   ════════════════════════════════════════════════════════ */

void grafo_init(Grafo *g) {
    g->num_nodos = 0;
    for (int i = 0; i < MAX_NODOS; i++)
        g->lista_adj[i] = NULL;
}

void grafo_agregar_nodo(Grafo *g, const char *codigo, const char *nombre,
                        const char *municipio, TipoNodo tipo) {
    int i = g->num_nodos;
    g->nodos[i].id = i;
    strncpy(g->nodos[i].codigo,    codigo,    sizeof(g->nodos[i].codigo)    - 1);
    strncpy(g->nodos[i].nombre,    nombre,    sizeof(g->nodos[i].nombre)    - 1);
    strncpy(g->nodos[i].municipio, municipio, sizeof(g->nodos[i].municipio) - 1);
    g->nodos[i].tipo = tipo;
    g->num_nodos++;
}

/* Agrega arista no dirigida u–v con peso dado */
void grafo_agregar_arista(Grafo *g, int u, int v, double peso, const char *via) {
    /* u → v */
    Arista *a1 = (Arista *)malloc(sizeof(Arista));
    a1->destino   = v;
    a1->peso      = peso;
    strncpy(a1->via, via, MAX_VIA - 1);
    a1->siguiente = g->lista_adj[u];
    g->lista_adj[u] = a1;

    /* v → u (grafo no dirigido) */
    Arista *a2 = (Arista *)malloc(sizeof(Arista));
    a2->destino   = u;
    a2->peso      = peso;
    strncpy(a2->via, via, MAX_VIA - 1);
    a2->siguiente = g->lista_adj[v];
    g->lista_adj[v] = a2;
}

/* Liberar toda la memoria del grafo */
void grafo_destruir(Grafo *g) {
    for (int i = 0; i < g->num_nodos; i++) {
        Arista *cur = g->lista_adj[i];
        while (cur) {
            Arista *sig = cur->siguiente;
            free(cur);
            cur = sig;
        }
        g->lista_adj[i] = NULL;
    }
    g->num_nodos = 0;
}

/* Buscar nodo por código (ej. "N01"), retorna índice o -1 */
int grafo_buscar_nodo(const Grafo *g, const char *codigo) {
    for (int i = 0; i < g->num_nodos; i++)
        if (strcmp(g->nodos[i].codigo, codigo) == 0)
            return i;
    return -1;
}

const char *tipo_nodo_str(TipoNodo t) {
    switch (t) {
        case CEDIS:             return "CEDIS";
        case PLANTA:            return "Planta";
        case PARQUE_INDUSTRIAL: return "Parque Industrial";
        case ALMACEN:           return "Almacen";
        case NODO_VIAL:         return "Nodo Vial";
        case FRONTERA:          return "Frontera";
        default:                return "Desconocido";
    }
}

/* ════════════════════════════════════════════════════════
   ALGORITMO DE DIJKSTRA
   ════════════════════════════════════════════════════════ */

ResultadoDijkstra dijkstra(const Grafo *g, int origen) {
    ResultadoDijkstra res;
    res.origen = origen;

    /* 1. Inicialización */
    for (int i = 0; i < g->num_nodos; i++) {
        res.dist[i] = INF;
        res.prev[i] = -1;
    }
    res.dist[origen] = 0.0;

    /* 2. Cola de prioridad mínima */
    MinHeap heap;
    heap_init(&heap);
    heap_insertar(&heap, origen, 0.0);

    int visitado[MAX_NODOS] = {0};

    /* 3. Bucle principal */
    while (!heap_vacio(&heap)) {
        HeapElem elem = heap_extraer_min(&heap);
        int u = elem.nodo;

        if (visitado[u]) continue;   /* nodo ya procesado con distancia menor */
        visitado[u] = 1;

        /* Relajar aristas salientes de u */
        Arista *a = g->lista_adj[u];
        while (a) {
            int    v        = a->destino;
            double nueva    = res.dist[u] + a->peso;

            if (!visitado[v] && nueva < res.dist[v]) {
                res.dist[v] = nueva;
                res.prev[v] = u;
                heap_insertar(&heap, v, nueva);
            }
            a = a->siguiente;
        }
    }

    return res;
}

/* ════════════════════════════════════════════════════════
   FUNCIONES DE IMPRESIÓN
   ════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════
   CÁLCULO DE COMBUSTIBLE
   ════════════════════════════════════════════════════════ */

double calcular_litros(const Vehiculo *v, double dist_km) {
    if (v->rendimiento_kmL <= 0.0) return 0.0;
    return dist_km / v->rendimiento_kmL;
}

double calcular_costo(const Vehiculo *v, double dist_km) {
    return calcular_litros(v, dist_km) * v->precio_litro;
}

void pedir_vehiculo(Vehiculo *v) {
    printf("\n");
    printf("  +---------------------------------------------+\n");
    printf("  |         DATOS DEL VEHICULO / COMBUSTIBLE    |\n");
    printf("  +---------------------------------------------+\n");

    printf("  Tipo de vehiculo (ej. Camion 3.5t, Pick-up): ");
    /* leer cadena con espacios */
    fgets(v->tipo, sizeof(v->tipo), stdin);
    /* quitar newline */
    v->tipo[strcspn(v->tipo, "\n")] = '\0';
    if (v->tipo[0] == '\0') strncpy(v->tipo, "Vehiculo de carga", sizeof(v->tipo)-1);

    /* rendimiento */
    v->rendimiento_kmL = 0.0;
    while (v->rendimiento_kmL <= 0.0) {
        printf("  Rendimiento del vehiculo (km/litro, ej. 10.5): ");
        if (scanf("%lf", &v->rendimiento_kmL) != 1) {
            while(getchar()!='\n');
            v->rendimiento_kmL = 0.0;
        } else {
            while(getchar()!='\n');
        }
        if (v->rendimiento_kmL <= 0.0)
            printf("  [!] Ingresa un valor positivo.\n");
    }

    /* precio del litro */
    v->precio_litro = 0.0;
    while (v->precio_litro <= 0.0) {
        printf("  Precio del litro de gasolina (MXN, ej. 24.50): $ ");
        if (scanf("%lf", &v->precio_litro) != 1) {
            while(getchar()!='\n');
            v->precio_litro = 0.0;
        } else {
            while(getchar()!='\n');
        }
        if (v->precio_litro <= 0.0)
            printf("  [!] Ingresa un valor positivo.\n");
    }

    printf("\n  Vehiculo registrado: %s | %.1f km/L | $%.2f/L\n",
           v->tipo, v->rendimiento_kmL, v->precio_litro);
}

/* ════════════════════════════════════════════════════════
   IMPRESIÓN CON COSTO DE COMBUSTIBLE
   ════════════════════════════════════════════════════════ */

/* Reconstruye y muestra la ruta óptima desde origen hasta destino */
void imprimir_ruta(const Grafo *g, const ResultadoDijkstra *res, int destino,
                   const Vehiculo *v) {
    if (res->dist[destino] >= INF) {
        printf("  [!] No existe ruta desde %s hasta %s\n",
               g->nodos[res->origen].codigo,
               g->nodos[destino].codigo);
        return;
    }

    /* Reconstruir ruta invirtiendo prev[] */
    int camino[MAX_NODOS];
    int len = 0;
    int cur = destino;
    while (cur != -1) {
        camino[len++] = cur;
        cur = res->prev[cur];
    }

    /* Imprimir secuencia de nodos */
    printf("  Ruta: ");
    for (int i = len - 1; i >= 0; i--) {
        printf("%s", g->nodos[camino[i]].codigo);
        if (i > 0) printf(" -> ");
    }
    printf("\n");

    /* Detalle de cada tramo con km parciales */
    for (int i = len - 1; i > 0; i--) {
        int desde = camino[i];
        int hasta = camino[i - 1];
        Arista *a = g->lista_adj[desde];
        double tramo = 0.0;
        char   via[MAX_VIA] = "---";
        while (a) {
            if (a->destino == hasta) {
                tramo = a->peso;
                strncpy(via, a->via, MAX_VIA - 1);
                break;
            }
            a = a->siguiente;
        }
        printf("         %s -> %s  (%.1f km | %s)\n",
               g->nodos[desde].codigo, g->nodos[hasta].codigo, tramo, via);
    }

    double dist_total   = res->dist[destino];
    double litros       = calcular_litros(v, dist_total);
    double costo_total  = calcular_costo(v, dist_total);

    printf("  %-26s %.1f km\n",  "Distancia total:",  dist_total);

    if (v->rendimiento_kmL > 0.0) {
        printf("  %-26s %.2f L\n",   "Combustible necesario:", litros);
        printf("  %-26s $%.2f MXN\n","Costo estimado gasolina:", costo_total);
    }
}

/* Muestra tabla de distancias mínimas desde el origen */
void imprimir_tabla_distancias(const Grafo *g, const ResultadoDijkstra *res,
                               const Vehiculo *v) {
    printf("\n  +------+-----------------------------+----------+----------+---------------+\n");
    printf("  | Cod  | Destino                     | Dist(km) | Litros   | Costo (MXN)   |\n");
    printf("  +------+-----------------------------+----------+----------+---------------+\n");
    for (int i = 0; i < g->num_nodos; i++) {
        if (i == res->origen) continue;
        if (res->dist[i] >= INF) {
            printf("  | %-4s | %-27s | SIN RUTA |    ---   |      ---      |\n",
                   g->nodos[i].codigo, g->nodos[i].nombre);
        } else {
            double litros = calcular_litros(v, res->dist[i]);
            double costo  = calcular_costo(v, res->dist[i]);
            printf("  | %-4s | %-27s | %8.1f | %8.2f | $%11.2f |\n",
                   g->nodos[i].codigo, g->nodos[i].nombre,
                   res->dist[i], litros, costo);
        }
    }
    printf("  +------+-----------------------------+----------+----------+---------------+\n");
    if (v->rendimiento_kmL > 0.0)
        printf("  Vehiculo: %s | %.1f km/L | $%.2f/L\n",
               v->tipo, v->rendimiento_kmL, v->precio_litro);
}

/* Lista todos los nodos del grafo */
void imprimir_nodos(const Grafo *g) {
    printf("\n  +------+-----------------------------+-------------------+-----------+\n");
    printf("  | Cod  | Nombre                      | Municipio         | Tipo      |\n");
    printf("  +------+-----------------------------+-------------------+-----------+\n");
    for (int i = 0; i < g->num_nodos; i++) {
        printf("  | %-4s | %-27s | %-17s | %-9s |\n",
               g->nodos[i].codigo,
               g->nodos[i].nombre,
               g->nodos[i].municipio,
               tipo_nodo_str(g->nodos[i].tipo));
    }
    printf("  +------+-----------------------------+-------------------+-----------+\n");
}

/* Representación ASCII de la lista de adyacencia */
void imprimir_grafo_ascii(const Grafo *g) {
    printf("\n  Lista de Adyacencia del Grafo\n");
    printf("  ================================\n");
    for (int i = 0; i < g->num_nodos; i++) {
        printf("  [%s] %s\n", g->nodos[i].codigo, g->nodos[i].nombre);
        Arista *a = g->lista_adj[i];
        while (a) {
            printf("       +-- %s (%.1f km | %s)\n",
                   g->nodos[a->destino].codigo, a->peso, a->via);
            a = a->siguiente;
        }
    }
}

/* Todas las rutas mínimas desde el origen */
void imprimir_todas_las_rutas(const Grafo *g, const ResultadoDijkstra *res,
                              const Vehiculo *v) {
    for (int i = 0; i < g->num_nodos; i++) {
        if (i == res->origen) continue;
        printf("\n  [%s] %s\n", g->nodos[i].codigo, g->nodos[i].nombre);
        imprimir_ruta(g, res, i, v);
    }
}
