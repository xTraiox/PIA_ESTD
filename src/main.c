#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/grafo.h"

/* declaración externa del cargador de datos */
void cargar_red_nl(Grafo *g);

/* ── Utilidades de consola ────────────────────────────────────────────── */
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

/* ── Banner ───────────────────────────────────────────────────────────── */
static void banner(void) {
    linea('=', 65);
    printf("  OPTIMIZACION DE RUTAS LOGISTICAS - CORREDOR INDUSTRIAL NL\n");
    printf("  Algoritmo de Dijkstra | Estructura de Datos | FCFM - UANL\n");
    linea('=', 65);
}

/* ── Pedir un índice de nodo válido al usuario ────────────────────────── */
static int pedir_nodo(const Grafo *g, const char *prompt) {
    char codigo[10];
    int  idx = -1;
    while (idx < 0) {
        printf("  %s (ej. N01): ", prompt);
        if (scanf("%9s", codigo) != 1) { while(getchar()!='\n'); continue; }
        while(getchar()!='\n');
        idx = grafo_buscar_nodo(g, codigo);
        if (idx < 0)
            printf("  [!] Codigo no encontrado. Intenta de nuevo.\n");
    }
    return idx;
}

/* ════════════════════════════════════════════════════════════════════════
   OPCIONES DEL MENÚ
   ════════════════════════════════════════════════════════════════════════ */

/* 1. Ruta entre dos nodos */
static void opcion_ruta_simple(const Grafo *g) {
    limpiar_pantalla();
    banner();
    printf("\n  [ RUTA OPTIMA ENTRE DOS PUNTOS ]\n\n");
    imprimir_nodos(g);

    printf("\n");
    int origen  = pedir_nodo(g, "Nodo ORIGEN ");
    int destino = pedir_nodo(g, "Nodo DESTINO");

    printf("\n");
    linea('-', 65);
    printf("  Ejecutando Dijkstra desde [%s] %s...\n\n",
           g->nodos[origen].codigo, g->nodos[origen].nombre);

    ResultadoDijkstra res = dijkstra(g, origen);

    printf("  Destino: [%s] %s\n", g->nodos[destino].codigo, g->nodos[destino].nombre);
    imprimir_ruta(g, &res, destino);
    linea('-', 65);

    pausar();
}

/* 2. Todas las rutas desde un origen */
static void opcion_todas_rutas(const Grafo *g) {
    limpiar_pantalla();
    banner();
    printf("\n  [ TODAS LAS RUTAS DESDE UN ORIGEN ]\n\n");
    imprimir_nodos(g);

    printf("\n");
    int origen = pedir_nodo(g, "Nodo ORIGEN");

    printf("\n");
    linea('-', 65);
    printf("  Ejecutando Dijkstra desde [%s] %s...\n",
           g->nodos[origen].codigo, g->nodos[origen].nombre);
    linea('-', 65);

    ResultadoDijkstra res = dijkstra(g, origen);

    imprimir_todas_las_rutas(g, &res);

    printf("\n");
    linea('-', 65);
    printf("  TABLA RESUMEN DE DISTANCIAS MINIMAS\n");
    imprimir_tabla_distancias(g, &res);

    pausar();
}

/* 3. Ver el grafo (lista de adyacencia) */
static void opcion_ver_grafo(const Grafo *g) {
    limpiar_pantalla();
    banner();
    printf("\n  [ ESTRUCTURA DEL GRAFO - LISTA DE ADYACENCIA ]\n");
    printf("  22 nodos | 26 aristas | Pesos en kilometros\n");
    imprimir_grafo_ascii(g);
    printf("\n  Total de nodos: %d\n", g->num_nodos);

    /* Contar aristas (cada arista aparece dos veces en lista no dirigida) */
    int total_aristas = 0;
    for (int i = 0; i < g->num_nodos; i++) {
        Arista *a = g->lista_adj[i];
        while (a) { total_aristas++; a = a->siguiente; }
    }
    printf("  Total de aristas (no dirigidas): %d\n", total_aristas / 2);
    pausar();
}

/* 4. Ver catálogo de nodos */
static void opcion_ver_nodos(const Grafo *g) {
    limpiar_pantalla();
    banner();
    printf("\n  [ CATALOGO DE NODOS - CORREDOR INDUSTRIAL NL ]\n");
    imprimir_nodos(g);
    pausar();
}

/* 5. Demo automático: 5 rutas de ejemplo */
static void opcion_demo(const Grafo *g) {
    limpiar_pantalla();
    banner();
    printf("\n  [ DEMO AUTOMATICO - Rutas representativas ]\n\n");

    struct { const char *orig; const char *dest; } demos[] = {
        {"N01", "N20"},   /* CEDIS Apodaca -> Aduana Colombia (ruta larga) */
        {"N01", "N02"},   /* CEDIS Apodaca -> Planta KIA                   */
        {"N01", "N16"},   /* CEDIS Apodaca -> Parque Ramos Arizpe           */
        {"N01", "N07"},   /* CEDIS Apodaca -> Planta CEMEX                  */
        {"N09", "N05"},   /* CEDIS San Nicolas -> Parque Garcia              */
    };
    int n_demos = sizeof(demos) / sizeof(demos[0]);

    for (int d = 0; d < n_demos; d++) {
        int orig = grafo_buscar_nodo(g, demos[d].orig);
        int dest = grafo_buscar_nodo(g, demos[d].dest);
        if (orig < 0 || dest < 0) continue;

        ResultadoDijkstra res = dijkstra(g, orig);

        printf("  Caso %d: [%s] %s  -->  [%s] %s\n",
               d + 1,
               g->nodos[orig].codigo, g->nodos[orig].nombre,
               g->nodos[dest].codigo, g->nodos[dest].nombre);
        imprimir_ruta(g, &res, dest);
        linea('-', 65);
    }

    pausar();
}

/* ════════════════════════════════════════════════════════════════════════
   MENÚ PRINCIPAL
   ════════════════════════════════════════════════════════════════════════ */

int main(void) {
    Grafo g;
    cargar_red_nl(&g);

    int opcion = 0;

    do {
        limpiar_pantalla();
        banner();
        printf("\n");
        printf("  [1]  Calcular ruta optima entre dos puntos\n");
        printf("  [2]  Ver todas las rutas desde un origen\n");
        printf("  [3]  Ver grafo (lista de adyacencia)\n");
        printf("  [4]  Ver catalogo de nodos\n");
        printf("  [5]  Demo automatico (5 rutas de ejemplo)\n");
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
            case 1: opcion_ruta_simple(&g);   break;
            case 2: opcion_todas_rutas(&g);    break;
            case 3: opcion_ver_grafo(&g);      break;
            case 4: opcion_ver_nodos(&g);      break;
            case 5: opcion_demo(&g);           break;
            case 0: break;
            default:
                printf("\n  [!] Opcion invalida.\n");
                pausar();
        }
    } while (opcion != 0);

    grafo_destruir(&g);
    printf("\n  Hasta luego.\n\n");
    return 0;
}
