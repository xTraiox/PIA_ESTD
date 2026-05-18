#ifndef GRAFO_H
#define GRAFO_H

#define MAX_NODOS 25
#define MAX_NOMBRE 80
#define MAX_VIA 100
#define INF 999999

/* ─── Tipos de nodo ─── */
typedef enum {
    CEDIS,
    PLANTA,
    PARQUE_INDUSTRIAL,
    ALMACEN,
    NODO_VIAL,
    FRONTERA
} TipoNodo;

/* ─── Nodo del grafo ─── */
typedef struct {
    int id;
    char codigo[6];        /* "N01", "N02", ... */
    char nombre[MAX_NOMBRE];
    char municipio[40];
    TipoNodo tipo;
} Nodo;

/* ─── Arista (lista de adyacencia) ─── */
typedef struct Arista {
    int destino;   /* índice del nodo destino */
    double peso;      /* distancia en km */
    char via[MAX_VIA];
    struct Arista *siguiente;
} Arista;

/* ─── Grafo ─── */
typedef struct {
    int num_nodos;
    Nodo nodos[MAX_NODOS];
    Arista *lista_adj[MAX_NODOS]; /* lista de adyacencia */
} Grafo;

/* ─── Resultado de Dijkstra ─── */
typedef struct {
    double dist[MAX_NODOS];  /* distancia mínima desde origen */
    int prev[MAX_NODOS];  /* nodo previo en ruta óptima */
    int origen;
} ResultadoDijkstra;

/* ─── Datos del vehículo y combustible ─── */
typedef struct {
    double rendimiento_kmL;  /* km por litro (ej. 12.5) */
    double precio_litro;     /* precio del litro en MXN */
    char tipo[30];         /* descripción del vehículo */
} Vehiculo;

/* Calcula litros necesarios para recorrer dist_km */
double calcular_litros(const Vehiculo *v, double dist_km);

/* Calcula costo total en MXN para recorrer dist_km */
double calcular_costo(const Vehiculo *v, double dist_km);

/* Pide al usuario los datos del vehículo y los llena en *v */
void pedir_vehiculo(Vehiculo *v);

/* ─── Prototipos ─── */
void grafo_init(Grafo *g);
void grafo_agregar_nodo(Grafo *g, const char *codigo, const char *nombre, const char *municipio, TipoNodo tipo);
void grafo_agregar_arista(Grafo *g, int u, int v, double peso, const char *via);
void grafo_destruir(Grafo *g);
int grafo_buscar_nodo(const Grafo *g, const char *codigo);

ResultadoDijkstra dijkstra(const Grafo *g, int origen);

void imprimir_ruta(const Grafo *g, const ResultadoDijkstra *res, int destino, const Vehiculo *v);
void imprimir_todas_las_rutas(const Grafo *g, const ResultadoDijkstra *res, const Vehiculo *v);
void imprimir_grafo_ascii(const Grafo *g);
void imprimir_tabla_distancias(const Grafo *g, const ResultadoDijkstra *res, const Vehiculo *v);
void imprimir_nodos(const Grafo *g);

const char *tipo_nodo_str(TipoNodo t);

#endif /* GRAFO_H */
