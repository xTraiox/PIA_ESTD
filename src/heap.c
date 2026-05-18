#include "../include/heap.h"
#include <stdio.h>

/* ── Inicializar heap vacío ── */
void heap_init(MinHeap *h) {
    h->tam = 0;
}

int heap_vacio(const MinHeap *h) {
    return h->tam == 0;
}

/* ── Subir el elemento recién insertado hasta su posición correcta ── */
static void subir(MinHeap *h, int i) {
    while (i > 0) {
        int padre = (i - 1) / 2;
        if (h->datos[padre].dist > h->datos[i].dist) {
            HeapElem tmp = h->datos[padre];
            h->datos[padre] = h->datos[i];
            h->datos[i] = tmp;
            i = padre;
        } else {
            break;
        }
    }
}

/* ── Bajar el elemento raíz hasta su posición correcta ── */
static void bajar(MinHeap *h, int i) {
    int tam = h->tam;
    while (1) {
        int menor = i;
        int iz = 2 * i + 1;
        int de = 2 * i + 2;

        if (iz < tam && h->datos[iz].dist < h->datos[menor].dist)
            menor = iz;
        if (de < tam && h->datos[de].dist < h->datos[menor].dist)
            menor = de;

        if (menor == i) break;

        HeapElem tmp = h->datos[i];
        h->datos[i] = h->datos[menor];
        h->datos[menor] = tmp;
        i = menor;
    }
}

/* ── Insertar nodo con distancia dada ── */
void heap_insertar(MinHeap *h, int nodo, double dist) {
    if (h->tam >= HEAP_MAX) {
        fprintf(stderr, "Error: heap lleno\n");
        return;
    }
    h->datos[h->tam].nodo = nodo;
    h->datos[h->tam].dist = dist;
    subir(h, h->tam);
    h->tam++;
}

/* ── Extraer el elemento de menor distancia ── */
HeapElem heap_extraer_min(MinHeap *h) {
    HeapElem min = h->datos[0];
    h->tam--;
    if (h->tam > 0) {
        h->datos[0] = h->datos[h->tam];
        bajar(h, 0);
    }
    return min;
}
