#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/grafo.h"

void cargar_red_nl(Grafo *g);

static void limpiar_pantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void pausar(void) {
    printf("\n  Presiona ENTER para continuar...");
    while (getchar() != '\n');
}

static void linea(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
    putchar('\n');
}

static void banner(void) {
    linea('=', 65);
    printf("  OPTIMIZACION DE RUTAS LOGISTICAS - CORREDOR INDUSTRIAL NL\n");
    printf("  Algoritmo de Dijkstra | Estructura de Datos | FCFM - UANL\n");
    linea('=', 65);
}

static void banner_vehiculo(const Vehiculo *v) {
    printf("  Vehiculo: %-22s %.1f km/L  $%.2f/L\n", v->tipo, v->rendimiento_kmL, v->precio_litro);
    linea('-', 65);
}

static int pedir_nodo(const Grafo *g, const char *prompt) {
    char codigo[10];
    int idx = -1;
    while (idx < 0) {
        printf("  %s (ej. N01): ", prompt);
        if (scanf("%9s", codigo) != 1) { 
            while(getchar()!='\n'); 
            continue; 
        }
        while(getchar()!='\n');
        idx = grafo_buscar_nodo(g, codigo);
        if (idx < 0)
            printf("  Codigo no encontrado.\n");
    }
    return idx;
}

/* ─── Opciones ──────────────────────────────────────────────────────── */

static void opcion_ruta_simple(const Grafo *g, Vehiculo *v) {
    limpiar_pantalla(); 
    banner(); 
    banner_vehiculo(v);
    printf("\n  [ RUTA OPTIMA ENTRE DOS PUNTOS ]\n\n");
    imprimir_nodos(g);
    printf("\n");
    int origen  = pedir_nodo(g, "Nodo ORIGEN ");
    int destino = pedir_nodo(g, "Nodo DESTINO");
    printf("\n"); linea('-', 65);
    printf("  Ejecutando Dijkstra desde [%s] %s...\n\n", g->nodos[origen].codigo, g->nodos[origen].nombre);
    ResultadoDijkstra res = dijkstra(g, origen);
    printf("  Destino: [%s] %s\n", g->nodos[destino].codigo, g->nodos[destino].nombre);
    imprimir_ruta(g, &res, destino, v);
    linea('-', 65);
    pausar();
}

static void opcion_todas_rutas(const Grafo *g, Vehiculo *v) {
    limpiar_pantalla(); 
    banner(); 
    banner_vehiculo(v);
    printf("\n  [ TODAS LAS RUTAS DESDE UN ORIGEN ]\n\n");
    imprimir_nodos(g);
    printf("\n");
    int origen = pedir_nodo(g, "Nodo ORIGEN");
    printf("\n"); linea('-', 65);
    printf("  Ejecutando Dijkstra desde [%s] %s...\n", g->nodos[origen].codigo, g->nodos[origen].nombre);
    linea('-', 65);
    ResultadoDijkstra res = dijkstra(g, origen);
    imprimir_todas_las_rutas(g, &res, v);
    printf("\n"); linea('-', 65);
    printf("  TABLA RESUMEN - DISTANCIAS Y COSTOS DE COMBUSTIBLE\n");
    imprimir_tabla_distancias(g, &res, v);
    pausar();
}

static void opcion_ver_grafo(const Grafo *g) {
    limpiar_pantalla(); 
    banner();
    printf("\n  [ ESTRUCTURA DEL GRAFO - LISTA DE ADYACENCIA ]\n");
    printf("  22 nodos | 26 aristas | Pesos en kilometros\n");
    imprimir_grafo_ascii(g);
    int total = 0;
    for (int i = 0; i < g->num_nodos; i++) {
        Arista *a = g->lista_adj[i];
        while (a) { 
            total++; a = a->siguiente; 
        }
    }
    printf("\n  Nodos: %d  |  Aristas: %d\n", g->num_nodos, total / 2);
    pausar();
}

static void opcion_ver_nodos(const Grafo *g) {
    limpiar_pantalla(); 
    banner();
    printf("\n  [ CATALOGO DE NODOS - CORREDOR INDUSTRIAL NL ]\n");
    imprimir_nodos(g);
    pausar();
}

static void opcion_demo(const Grafo *g, Vehiculo *v) {
    limpiar_pantalla(); 
    banner(); 
    banner_vehiculo(v);
    printf("\n  [ DEMO AUTOMATICO - 5 rutas representativas ]\n\n");

    struct { const char *orig; const char *dest; } demos[] = {
        {"N01", "N20"},
        {"N01", "N02"},
        {"N01", "N16"},
        {"N01", "N07"},
        {"N09", "N05"},
    };
    int n = sizeof(demos) / sizeof(demos[0]);

    for (int d = 0; d < n; d++) {
        int orig = grafo_buscar_nodo(g, demos[d].orig);
        int dest = grafo_buscar_nodo(g, demos[d].dest);
        if (orig < 0 || dest < 0) continue;
        ResultadoDijkstra res = dijkstra(g, orig);
        printf("  Caso %d: [%s] %s  -->  [%s] %s\n", d + 1, g->nodos[orig].codigo, g->nodos[orig].nombre, g->nodos[dest].codigo, g->nodos[dest].nombre);
        imprimir_ruta(g, &res, dest, v);
        linea('-', 65);
    }
    pausar();
}

static void opcion_cambiar_vehiculo(Vehiculo *v) {
    limpiar_pantalla(); banner();
    printf("\n  [ CAMBIAR DATOS DEL VEHICULO ]\n");
    pedir_vehiculo(v);
    printf("\n  Datos actualizados correctamente.\n");
    pausar();
}

/* ─── main ──────────────────────────────────────────────────────────── */

int main(void) {
    Grafo g;
    Vehiculo v;

    cargar_red_nl(&g);

    limpiar_pantalla();
    banner();
    printf("\n  Bienvenido. Ingresa los datos de tu vehiculo para calcular\n");
    printf("  el costo de gasolina en cada ruta.\n");
    pedir_vehiculo(&v);
    pausar();

    int opcion = 0;
    do {
        limpiar_pantalla();
        banner();
        printf("\n");
        banner_vehiculo(&v);
        printf("\n");
        printf("  [1]  Calcular ruta optima entre dos puntos\n");
        printf("  [2]  Ver todas las rutas desde un origen\n");
        printf("  [3]  Ver grafo (lista de adyacencia)\n");
        printf("  [4]  Ver catalogo de nodos\n");
        printf("  [5]  Demo automatico (5 rutas de ejemplo)\n");
        printf("  [6]  Cambiar datos del vehiculo\n");
        printf("  [0]  Salir\n");
        printf("\n");
        linea('-', 65);
        printf("  Selecciona una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = -1;
            continue;
        }
        while (getchar() != '\n');

        switch (opcion) {
            case 1: opcion_ruta_simple(&g, &v);  
            break;
            case 2: opcion_todas_rutas(&g, &v);  
            break;
            case 3: opcion_ver_grafo(&g);         
            break;
            case 4: opcion_ver_nodos(&g);         
            break;
            case 5: opcion_demo(&g, &v);          
            break;
            case 6: opcion_cambiar_vehiculo(&v);  
            break;
            case 0: 
            break;
            default:
                printf("\n  [!] Opcion invalida.\n");
                pausar();
        }
    } while (opcion != 0);

    grafo_destruir(&g);
    printf("\n  Hasta luego.\n\n");
    return 0;
}
