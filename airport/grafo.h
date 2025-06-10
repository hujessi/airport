//
// Created by User on 6/2/2025.
//



#ifndef GRAFO_H
#define GRAFO_H


// Estructura para nodo de la lista de adyacencia
typedef struct nodoAdy {
    int destino;                   // Nodo destino
    int duracion;                  // Costo del vuelo
    char * numVuelo;               // Número de vuelo
    char * company;                // Compañía de vuelo
    struct nodoAdy* next;          // Siguiente nodo adyacente
} nodoAdy;

// Lista de adyacencia
typedef struct listAdy {
    nodoAdy* head;
} listAdy;

// Estructura del grafo ponderado
typedef struct Grafo {
    int numVertices;
    listAdy* array;  // Array de listas de adyacencia
} Grafo;


// Funciones grafo
nodoAdy* newAdyNode(int destino);
Grafo* crearGrafo(int vertices);
void addVuelo(Grafo* grafo, int origen, int destino, int duracion);
int** matrizAdyacencia(Grafo* grafo);
void imprimirGrafo(Grafo* grafo);
void dijkstra(Grafo* grafo, int origen, int dist[], int previo[]);
void mostrarRuta(int destino, int previo[]);
void rutaMasCorta(Grafo* grafo, int origen, int destino);
void mostrarRutasDesdeOrigen(Grafo* grafo, int origen);
void freeGraph(Grafo* grafo);


#endif //GRAFO_H
