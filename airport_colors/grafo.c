#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "aeropuertos.h"
#include <stdbool.h>

#define INF 9999
#define MAX_VERTICES 100


const char* cyan = "\x1b[36m";
const char* reset = "\x1b[0m";
const char* dorado = "\x1b[93m";


// Crear un nuevo nodo de adyacencia
nodoAdy* newAdyNode(int destino) {
    nodoAdy* newNode = (nodoAdy*)malloc(sizeof(nodoAdy));
    newNode->destino = destino;
    newNode->next = NULL;
    return newNode;
}

// Crear el grafo con n vértices
Grafo* crearGrafo(int vertices) {
    Grafo* graph = (Grafo*)malloc(sizeof(Grafo));
    graph->numVertices = vertices;
    graph->array = (listAdy*)malloc(vertices * sizeof(listAdy));

    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addVuelo(Grafo* grafo, int origen, int destino, int duracion) {
    nodoAdy* nuevoNodo = malloc(sizeof(nodoAdy));
    nuevoNodo->destino = destino;
    nuevoNodo->duracion = duracion;
    nuevoNodo->next = grafo->array[origen].head;
    grafo->array[origen].head = nuevoNodo;

    // Si es bidireccional, añade también el reverso
    // lo dejamos comentado.
    // lo hemos quitado porque añadia vuelos bidireccionales y eso está mal

    /*nodoAdy* nuevoNodo2 = malloc(sizeof(nodoAdy));
    nuevoNodo2->destino = origen;
    nuevoNodo2->duracion = duracion;
    nuevoNodo2->next = grafo->array[destino].head;
    grafo->array[destino].head = nuevoNodo2;
    */
}




// Función que crea la matriz de adyacencia e imprime
int** matrizAdyacencia(Grafo* grafo) {
    int V = grafo->numVertices;

    // Iniciales de los países
    const char* iniciales[] = {
        "MAD", "BCN", "CDG", "LHR", "FCO", "BER", "AMS", "LIS", "PRG",
        "ATH", "JNB", "IST", "DXB", "JFK", "LAX", "MEX", "EZE", "GIG", "NRT", "SYD", "PEK"
    };

    // Crear matriz dinámica V x V
    int** matriz = malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        matriz[i] = malloc(V * sizeof(int));
    }

    // Inicializar matriz con -1 (sin conexión)
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            matriz[i][j] = -1;
        }
    }

    // Rellenar matriz con duraciones desde la lista de adyacencia
    for (int i = 0; i < V; i++) {
        nodoAdy* actual = grafo->array[i].head;
        while (actual != NULL) {
            matriz[i][actual->destino] = actual->duracion;
            actual = actual->next;
        }
    }

    // Encabezado de columnas
    printf("     "); // Espacio para el encabezado de filas
    for (int j = 0; j < V; j++) {
        printf("%s%4s %s", cyan, iniciales[j], reset);
    }
    printf("\n");

    // Filas con encabezado y datos
    for (int i = 0; i < V; i++) {
        printf("%s%4s %s", cyan, iniciales[i], reset); // Encabezado de fila
        for (int j = 0; j < V; j++) {
            if (i == j) {
                printf("   0 ");
            } else {
                if (matriz[i][j] == -1)
                    printf(" INF ");
                else
                    printf("%4d ", matriz[i][j]);
            }
        }
        printf("\n");
    }

    return matriz;
}






// Imprimir el grafo
/*void imprimirGrafo(Grafo* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        nodoAdy* pCrawl = graph->array[v].head;
        printf("Vertex %d:", v);
        while (pCrawl) {
            printf(" -> %d", pCrawl->destino);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}*/




void imprimirGrafo(Grafo* grafo) {
    printf("\n%s--- LISTA DE ADYACENCIA -----------------------------------------------------------------------------------------------------------%s\n\n", dorado, reset);

    for (int i = 0; i < grafo->numVertices; i++) {
        nodoAdy* actual = grafo->array[i].head;

        // Declarar la matriz sin inicializar
        bool yaImpreso[grafo->numVertices][24];

        // Inicializar manualmente
        for (int j = 0; j < grafo->numVertices; j++) {
            for (int k = 0; k < 24; k++) {
                yaImpreso[j][k] = false;
            }
        }

        // Imprime la ciudad de origen
        printf("%s%s (%s) -> %s", cyan, nombres_aeropuertos[i], iniciales_aeropuertos[i], reset);

        // Recorre la lista de adyacencia del vértice i
        while (actual != NULL) {
            int destino = actual->destino;
            int duracion = actual->duracion;

            if (duracion < 24 && !yaImpreso[destino][duracion]) {
                printf(" %s (%s) (%dh)->", nombres_aeropuertos[destino], iniciales_aeropuertos[destino], duracion);
                yaImpreso[destino][duracion] = true;
            }

            actual = actual->next;
        }
        printf(" NULL\n\n");
    }

    printf("%s------------------------------------------------------------------------------------------------------------------------------------%s\n\n", dorado, reset);

}



void dijkstra(Grafo* grafo, int origen, int dist[], int previo[]) {
    bool visitado[MAX_VERTICES];
    int n = grafo->numVertices;

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visitado[i] = false;
        previo[i] = -1;
    }

    dist[origen] = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = INF, u = -1;

        // Buscar el vértice no visitado con la distancia mínima
        for (int j = 0; j < n; j++) {
            if (!visitado[j] && dist[j] <= min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) break;

        visitado[u] = true;

        nodoAdy* actual = grafo->array[u].head;
        while (actual != NULL) {
            int v = actual->destino;
            int peso = actual->duracion;

            if (!visitado[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                previo[v] = u;
            }

            actual = actual->next;
        }
    }
}

void mostrarRuta(int destino, int previo[]) {
    if (previo[destino] == -1) {
        printf("%s (%s)", nombres_aeropuertos[destino], iniciales_aeropuertos[destino]);
        return;
    }
    mostrarRuta(previo[destino], previo);
    printf(" -> %s (%s)", nombres_aeropuertos[destino], iniciales_aeropuertos[destino]);
}


void rutaMasCorta(Grafo* grafo, int origen, int destino) {
    int dist[MAX_VERTICES];
    int previo[MAX_VERTICES];

    dijkstra(grafo, origen, dist, previo);

    if (dist[destino] == INF) {
        printf("\n>>> No hay ruta disponible de %s%s%s (%s) a %s%s%s (%s).\n\n",
               dorado, nombres_aeropuertos[origen], reset, iniciales_aeropuertos[origen],
               dorado, nombres_aeropuertos[destino], reset, iniciales_aeropuertos[destino]);
    } else {
        printf("\nRuta más corta de %s%s%s (%s) a %s%s%s (%s):\n",
               dorado, nombres_aeropuertos[origen], reset, iniciales_aeropuertos[origen],
               dorado, nombres_aeropuertos[destino], reset, iniciales_aeropuertos[destino]);

        mostrarRuta(destino, previo);

        printf("\nDuración total: %d horas\n\n", dist[destino]);
    }
}

void mostrarRutasDesdeOrigen(Grafo* grafo, int origen) {
    int dist[MAX_VERTICES];
    int previo[MAX_VERTICES];

    dijkstra(grafo, origen, dist, previo);

    int destinos[MAX_VERTICES];
    int numDestinos = 0;

    for (int i = 0; i < grafo->numVertices; i++) {
        if (i != origen && dist[i] != INF) {
            destinos[numDestinos++] = i;
        }
    }

    // Ordenar destinos por duración ascendente
    for (int i = 0; i < numDestinos - 1; i++) {
        for (int j = i + 1; j < numDestinos; j++) {
            if (dist[destinos[i]] > dist[destinos[j]]) {
                int temp = destinos[i];
                destinos[i] = destinos[j];
                destinos[j] = temp;
            }
        }
    }

    // Imprimir cabecera con anchos: Destino (17), Duración (8), Ruta (resto)
    printf("\nRutas más cortas desde %s%s (%s):%s\n\n", dorado, nombres_aeropuertos[origen], iniciales_aeropuertos[origen], reset);
    printf("%s%-17s %8s  %s\n", dorado, "Destino", "Duración", "Ruta");
    printf("--------------------------------------------------------------------------%s\n", reset);

    for (int i = 0; i < numDestinos; i++) {
        int destino = destinos[i];

        char rutaStr[256] = "";
        int rutaOrdenada[MAX_VERTICES];
        int idx = 0;
        int actual = destino;

        while (actual != -1) {
            rutaOrdenada[idx++] = actual;
            actual = previo[actual];
        }

        for (int j = idx - 1; j >= 0; j--) {
            strcat(rutaStr, nombres_aeropuertos[rutaOrdenada[j]]);
            if (j > 0) strcat(rutaStr, " -> ");
        }

        // Duración
        printf("%s%-17s%s %7dh  %s\n", cyan, nombres_aeropuertos[destino], reset, dist[destino], rutaStr);
    }
    printf("\n");
}

// Liberar memoria del grafo
void freeGraph(Grafo* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        nodoAdy* current = graph->array[i].head;
        while (current != NULL) {
            nodoAdy* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

