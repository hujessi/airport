//
// Created by User on 6/3/2025.
//

#include "aeropuertos.h"
// Definiciones reales (una vez y solo aquí)
const char *nombres_aeropuertos[TOTAL_AEROPUERTOS] = {
    "MADRID", "BARCELONA", "PARIS", "LONDRES", "ROMA", "BERLIN", "AMSTERDAM", "LISBOA", "PRAGA",
    "ATENAS", "JOHANNESBURGO", "ESTAMBUL", "DUBAI", "NUEVA YORK", "LOS ANGELES",
    "CIUDAD DE MEXICO", "BUENOS AIRES", "RIO DE JANEIRO", "TOKIO", "SIDNEY", "PEKIN"
};

const char *iniciales_aeropuertos[TOTAL_AEROPUERTOS] = {
    "MAD", "BCN", "CDG", "LHR", "FCO", "BER", "AMS", "LIS", "PRG",
    "ATH", "JNB", "IST", "DXB", "JFK", "LAX", "MEX", "EZE", "GIG", "NRT", "SYD", "PEK"
};


void mostrar_ciudades() {
    printf("\n%s=== CIUDADES DISPONIBLES ===%s\n\n", dorado, reset);

    for (int i = 0; i < TOTAL_AEROPUERTOS; i++) {
        printf("  %s[%d]%s %s (%s)\n", cyan, i + 1, reset, nombres_aeropuertos[i], iniciales_aeropuertos[i]);
    }
    printf("\n%s──────────────────────────────%s\n\n", dorado, reset);
}

// Función para pedir una ciudad válida
int pedir_ciudad(const char *tipo) {
    int opcion;
    while (1) {
        printf("Introduzca el número asociado a la ciudad de %s: ", tipo);
        if (scanf("%d", &opcion) != 1 || opcion < 1 || opcion > TOTAL_AEROPUERTOS) {
            printf("\n*** Error, no existe ninguna ciudad asociada al número %d ***\n\n", opcion);
            while (getchar() != '\n'); // limpiar el búfer
        } else {
            return opcion - 1;
        }
    }
}

void addTodosVuelos(Grafo * grafo) {


    // MADRID
    addVuelo(grafo, MADRID, PARIS, 2);
    addVuelo(grafo, MADRID, LONDRES, 2);
    addVuelo(grafo, MADRID, ROMA, 2);

    // BARCELONA
    addVuelo(grafo, BARCELONA, AMSTERDAM, 1);
    addVuelo(grafo, BARCELONA, PARIS, 2);

    // PARIS
    addVuelo(grafo, PARIS, PRAGA, 2);
    addVuelo(grafo, PARIS, LONDRES, 2);
    addVuelo(grafo, PARIS, ROMA, 2);
    addVuelo(grafo, PARIS, BARCELONA, 2);
    addVuelo(grafo, PARIS, MADRID, 2);

    // LONDRES
    addVuelo(grafo, LONDRES, NUEVA_YORK, 7);
    addVuelo(grafo, LONDRES, DUBAI, 6);
    addVuelo(grafo, LONDRES, PARIS, 2);
    addVuelo(grafo, LONDRES, MADRID, 2);

    // ROMA
    addVuelo(grafo, ROMA, ESTAMBUL, 3);
    addVuelo(grafo, ROMA, ATENAS, 2);
    addVuelo(grafo, ROMA, PARIS, 2);
    addVuelo(grafo, ROMA, MADRID, 2);

    // BERLIN
    addVuelo(grafo, BERLIN, PEKIN, 9);
    addVuelo(grafo, BERLIN, AMSTERDAM, 2);

    // AMSTERDAM
    addVuelo(grafo, AMSTERDAM, NUEVA_YORK, 8);
    addVuelo(grafo, AMSTERDAM, BERLIN, 2);
    addVuelo(grafo, AMSTERDAM, BARCELONA, 1);

    // LISBOA
    addVuelo(grafo, LISBOA, CIUDAD_MEXICO, 9);
    addVuelo(grafo, LISBOA, MADRID, 1);

    // PRAGA
    addVuelo(grafo, PRAGA, TOKIO, 11);
    addVuelo(grafo, PRAGA, PARIS, 2);

    // ATENAS
    addVuelo(grafo, ATENAS, ROMA, 2);

    // JOHANNESBURGO
    addVuelo(grafo, JOHANNESBURGO, CIUDAD_MEXICO, 14);
    addVuelo(grafo, JOHANNESBURGO, DUBAI, 9);

    // ESTAMBUL
    addVuelo(grafo, ESTAMBUL, ROMA, 3);

    // DUBAI
    addVuelo(grafo, DUBAI, PRAGA, 6);
    addVuelo(grafo, DUBAI, JOHANNESBURGO, 9);
    addVuelo(grafo, DUBAI, LONDRES, 6);
    addVuelo(grafo, DUBAI, TOKIO, 10);

    // NUEVA YORK
    addVuelo(grafo, NUEVA_YORK, RIO_JANEIRO, 9);
    addVuelo(grafo, NUEVA_YORK, LOS_ANGELES, 6);
    addVuelo(grafo, NUEVA_YORK, AMSTERDAM, 8);
    addVuelo(grafo, NUEVA_YORK, LONDRES, 7);

    // LOS ANGELES
    addVuelo(grafo, LOS_ANGELES, CIUDAD_MEXICO, 4);
    addVuelo(grafo, LOS_ANGELES, NUEVA_YORK, 6);

    // CIUDAD DE MEXICO
    addVuelo(grafo, CIUDAD_MEXICO, LOS_ANGELES, 4);
    addVuelo(grafo, CIUDAD_MEXICO, BUENOS_AIRES, 10);
    addVuelo(grafo, CIUDAD_MEXICO, LISBOA, 9);
    addVuelo(grafo, CIUDAD_MEXICO, JOHANNESBURGO, 14);

    // BUENOS AIRES
    addVuelo(grafo, BUENOS_AIRES, RIO_JANEIRO, 3);
    addVuelo(grafo, BUENOS_AIRES, SIDNEY, 17);

    // RIO DE JANEIRO
    addVuelo(grafo, RIO_JANEIRO, NUEVA_YORK, 9);
    addVuelo(grafo, RIO_JANEIRO, BUENOS_AIRES, 3);

    // TOKIO
    addVuelo(grafo, TOKIO, PRAGA, 11);
    addVuelo(grafo, TOKIO, SIDNEY, 9);
    addVuelo(grafo, TOKIO, PEKIN, 5);
    addVuelo(grafo, TOKIO, DUBAI, 10);

    // SIDNEY
    addVuelo(grafo, SIDNEY, TOKIO, 9);
    addVuelo(grafo, SIDNEY, BUENOS_AIRES, 17);

    // PEKIN
    addVuelo(grafo, PEKIN, BERLIN, 9);
    addVuelo(grafo, PEKIN, TOKIO, 5);


}



void mostrar_spinner(const char* mensaje, int duracion_ms) {
    const char sp[] = "|/-\\";
    int pasos = duracion_ms / 100; // cambio cada 100 ms

    printf("%s ", mensaje);
    fflush(stdout);

    for (int i = 0; i < pasos; i++) {
        printf("\r%s [%c]", mensaje, sp[i % 4]);
        fflush(stdout);

    #ifdef _WIN32
            Sleep(100);
    #else
            usleep(100000);
    #endif
    }

    printf("\r%s [✓]\n", mensaje); // Mensaje final con check
}
