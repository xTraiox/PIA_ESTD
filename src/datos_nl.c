#include "../include/grafo.h"
#include <stdio.h>

/*
 * cargar_red_nl()
 * ---------------
 * Carga los 22 nodos y 26 aristas del corredor industrial
 * de Nuevo León directamente en el grafo.
 */
void cargar_red_nl(Grafo *g) {

    grafo_init(g);

    /* ── NODOS ─────────────────────────────────────────────────────────────
       ID  Código  Nombre                           Municipio       Tipo
       ─────────────────────────────────────────────────────────────────── */
    grafo_agregar_nodo(g, "N01", "CEDIS Apodaca",              "Apodaca",        CEDIS);
    grafo_agregar_nodo(g, "N02", "Planta KIA Pesqueria",       "Pesqueria",      PLANTA);
    grafo_agregar_nodo(g, "N03", "Parque Ind. Stiva",          "Apodaca",        PARQUE_INDUSTRIAL);
    grafo_agregar_nodo(g, "N04", "Parque Ind. Escobedo",       "Escobedo",       PARQUE_INDUSTRIAL);
    grafo_agregar_nodo(g, "N05", "Parque Ind. Garcia",         "Garcia",         PARQUE_INDUSTRIAL);
    grafo_agregar_nodo(g, "N06", "Planta FEMSA Monterrey",     "Monterrey",      PLANTA);
    grafo_agregar_nodo(g, "N07", "Planta CEMEX Sta. Catarina", "Sta. Catarina",  PLANTA);
    grafo_agregar_nodo(g, "N08", "Terminal de Carga MTY",      "Monterrey",      ALMACEN);
    grafo_agregar_nodo(g, "N09", "CEDIS San Nicolas",          "San Nicolas",    CEDIS);
    grafo_agregar_nodo(g, "N10", "Almacen Guadalupe",          "Guadalupe",      ALMACEN);
    grafo_agregar_nodo(g, "N11", "Parque Ind. FINSA",          "Apodaca",        PARQUE_INDUSTRIAL);
    grafo_agregar_nodo(g, "N12", "Nodo Periferico Norte",      "Escobedo",       NODO_VIAL);
    grafo_agregar_nodo(g, "N13", "Nodo Carr. 85 (Laredo)",     "Apodaca",        NODO_VIAL);
    grafo_agregar_nodo(g, "N14", "Nodo Av. Miguel Aleman",     "Monterrey",      NODO_VIAL);
    grafo_agregar_nodo(g, "N15", "Nodo Libramiento Noreste",   "Guadalupe",      NODO_VIAL);
    grafo_agregar_nodo(g, "N16", "Parque Ind. Ramos Arizpe",   "Ramos Arizpe",   PARQUE_INDUSTRIAL);
    grafo_agregar_nodo(g, "N17", "Almacen Pesqueria Norte",    "Pesqueria",      ALMACEN);
    grafo_agregar_nodo(g, "N18", "Zona Industrial Vallejo",    "Monterrey",      PARQUE_INDUSTRIAL);
    grafo_agregar_nodo(g, "N19", "Nodo Carr. a Saltillo",      "Sta. Catarina",  NODO_VIAL);
    grafo_agregar_nodo(g, "N20", "Aduana Colombia/Puente",     "Anahuac",        FRONTERA);
    grafo_agregar_nodo(g, "N21", "Parque Ind. Cienega",        "Juarez NL",      PARQUE_INDUSTRIAL);
    grafo_agregar_nodo(g, "N22", "CEDIS Regional Sultana",     "Monterrey",      CEDIS);

    /* ── ARISTAS (u, v, km, vialidad) ──────────────────────────────────── */
    grafo_agregar_arista(g,  0,  2,   8.0, "Blvd. Diaz Ordaz");
    grafo_agregar_arista(g,  0, 12,  12.0, "Carretera 85 Norte");
    grafo_agregar_arista(g,  0, 10,   6.0, "Periferico Apodaca");
    grafo_agregar_arista(g,  2,  3,  15.0, "Carr. Apodaca-Escobedo");
    grafo_agregar_arista(g,  2, 11,  18.0, "Periferico Norte");
    grafo_agregar_arista(g,  2,  1,  22.0, "Carr. Pesqueria");
    grafo_agregar_arista(g,  3,  4,  28.0, "Carr. Escobedo-Garcia");
    grafo_agregar_arista(g,  3, 11,  10.0, "Av. Industrial Escobedo");
    grafo_agregar_arista(g, 11, 19,  95.0, "Autopista a Nuevo Laredo");
    grafo_agregar_arista(g, 12, 19, 110.0, "Carretera 85 Federal");
    grafo_agregar_arista(g, 12, 15,  85.0, "Carr. a Saltillo");
    grafo_agregar_arista(g,  1, 16,   5.0, "Interna Pesqueria");
    grafo_agregar_arista(g, 16, 15,  72.0, "Carr. Pesqueria-Ramos Arizpe");
    grafo_agregar_arista(g,  8,  7,  14.0, "Av. San Nicolas");
    grafo_agregar_arista(g,  8,  9,  11.0, "Periferico Guadalupe");
    grafo_agregar_arista(g,  7, 13,   9.0, "Av. Miguel Aleman");
    grafo_agregar_arista(g,  7, 17,   7.0, "Corredor Industrial");
    grafo_agregar_arista(g,  9, 14,  13.0, "Libramiento Noreste");
    grafo_agregar_arista(g, 14, 20,  20.0, "Carr. Juarez NL");
    grafo_agregar_arista(g, 13,  5,   8.0, "Av. Constitucion MTY");
    grafo_agregar_arista(g, 13, 21,   6.0, "Blvd. Colosio");
    grafo_agregar_arista(g, 21,  6,  30.0, "Autopista MTY-Sta. Catarina");
    grafo_agregar_arista(g,  6, 18,  12.0, "Interna Sta. Catarina");
    grafo_agregar_arista(g, 18, 15,  70.0, "Carretera a Saltillo");
    grafo_agregar_arista(g, 10,  8,   9.0, "Periferico sur Apodaca");
    grafo_agregar_arista(g,  0,  8,  20.0, "Corredor MTY-Apodaca");
}
