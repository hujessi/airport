#include "aeropuertos.h"


// MAIN
int main() {

    int vertices = 56;

    Grafo* grafo = crearGrafo(TOTAL_AEROPUERTOS);
    addTodosVuelos(grafo);

    int** matriz = NULL;

    int opcionMenu;

    printf("\n✈  Bienvenido al Aeropuerto Internacional 'HCG'  ✈ \n");
    printf("\nPrepara tu pasaporte, el sistema está despegando...\n");
    printf("A continuación, se muestra el menú principal.\n\n");


    while (1) {

        printf("              ✈ MENÚ ✈\n");
        printf("------------------------------------\n");
        printf("[1] Mostrar Ciudades                 \n");
        printf("[2] Buscar Rutas entre Ciudades     \n");
        printf("[3] Mostrar Vuelos Disponibles      \n");
        printf("[4] Mostrar Lista de Adyacencia     \n");
        printf("[5] Mostrar Matriz de Adyacencia    \n");
        printf("[6] Salir                          \n");
        printf("------------------------------------\n");
        printf("Seleccione una opción: ");


        if (scanf("%d", &opcionMenu) != 1) {
            printf("\n*** Error, valor introducido incorrecto ***\n");
            while (getchar() != '\n'); // Limpiar búfer
            continue;
        }

        switch (opcionMenu) {
            case 1:
                printf("\n>>> OPCIÓN SELECCIONADA: 1 <<<\n");
                mostrar_ciudades();
                break;

            case 2:
                printf("\n>>> OPCIÓN SELECCIONADA: 2 <<<\n");

                mostrar_ciudades();

                int origen = pedir_ciudad("origen");
                int destino = pedir_ciudad("destino");

                printf("\nCiudad de origen: %s\n", nombres_aeropuertos[origen]);
                printf("Ciudad de destino: %s\n", nombres_aeropuertos[destino]);

                /*// Aquí puedes luego calcular rutas, tiempos, etc.
                printf("\nRuta entre ciudades (MÁS CORTA):\n");
                printf("%s -> %s\n", nombres_aeropuertos[origen], nombres_aeropuertos[destino]);
                printf("Tiempo total: 2 horas.\n"); // Ejemplo fijo*/

                rutaMasCorta(grafo,origen,destino);
                break;

            case 3:

                printf("\n>>> OPCIÓN SELECCIONADA: 3 <<<\n");

                mostrar_ciudades();

                int origenRutas = pedir_ciudad("origen");
                printf("\nCiudad de origen: %s\n", nombres_aeropuertos[origenRutas]);
                printf("\nMostrando vuelos disponibles...\n");
                mostrarRutasDesdeOrigen(grafo, origenRutas);


                break;

            case 4:
                printf("\n>>> OPCIÓN SELECCIONADA: 4 <<<\n");

                // Mostrar lista de adyaciencia
                imprimirGrafo(grafo);

                break;

            case 5:
                printf("\n>>> OPCIÓN SELECCIONADA: 5 <<<\n");

            printf("\n-------------------------------------------- MATRIZ DE ADYACENCIA --------------------------------------------\n\n");
            // Obtener e imprimir matriz de adyacencia
            matriz = matrizAdyacencia(grafo);
            printf("\n--------------------------------------------------------------------------------------------------------------\n\n");
            break;

            case 6:
                printf(">>> Saliendo del programa. ¡Hasta pronto!\n");

                if (matriz != NULL) {
                    for (int i = 0; i < vertices; i++) {
                        free(matriz[i]);
                    }
                    free(matriz);
                }

            freeGraph(grafo);

            return 0;

            default:
                printf("*** Error, valor introducido incorrecto \n\n");
        }
    }

}
