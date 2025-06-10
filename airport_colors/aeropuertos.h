//
// Created by User on 6/3/2025.
//

#ifndef AEROPUERTOS_H
#define AEROPUERTOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"


// añadido aparte
#ifdef _WIN32
#include <windows.h> // Sleep()
#else
#include <unistd.h>  // usleep()
#endif


// Enumeración de aeropuertos
typedef enum {
    MADRID, BARCELONA, PARIS, LONDRES, ROMA, BERLIN, AMSTERDAM, LISBOA, PRAGA,
    ATENAS, JOHANNESBURGO, ESTAMBUL, DUBAI, NUEVA_YORK, LOS_ANGELES,
    CIUDAD_MEXICO, BUENOS_AIRES, RIO_JANEIRO, TOKIO, SIDNEY, PEKIN,
    TOTAL_AEROPUERTOS
} Airport;

// Declaraciones
extern const char *nombres_aeropuertos[TOTAL_AEROPUERTOS];
extern const char *iniciales_aeropuertos[TOTAL_AEROPUERTOS];

// Funciones
void mostrar_ciudades();
int pedir_ciudad(const char *tipo);
void addTodosVuelos(Grafo * grafo);

void mostrar_spinner(const char* mensaje, int duracion_ms);

#endif //AEROPUERTOS_H
