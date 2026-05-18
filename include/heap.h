#ifndef HEAP_H
#define HEAP_H

#include "grafo.h"

#define HEAP_MAX (MAX_NODOS * 2)

/* ─── Elemento del heap ─── */
typedef struct {
    int nodo;
    double dist;
} HeapElem;

/* ─── Min-heap ─── */
typedef struct {
    HeapElem datos[HEAP_MAX];
    int tam;
} MinHeap;

void heap_init(MinHeap *h);
int heap_vacio(const MinHeap *h);
void heap_insertar(MinHeap *h, int nodo, double dist);
HeapElem heap_extraer_min(MinHeap *h);

#endif /* HEAP_H */
