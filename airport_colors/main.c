#include "aeropuertos.h"





// MAIN
int main() {

    int vertices = 56;
    int** matriz = NULL;

    Grafo* grafo = crearGrafo(TOTAL_AEROPUERTOS);
    addTodosVuelos(grafo);

    int opcionMenu;

    printf("\n%s✈  Bienvenido al Aeropuerto Internacional 'HCG'  ✈ \n%s", dorado, reset);
    printf("\nPrepara tu pasaporte, el sistema está despegando...\n");
    printf("A continuación, se muestra el menú principal.\n\n");


    while (1) {

        printf("%s              ✈ MENÚ ✈%s\n", dorado, reset);
        printf("%s------------------------------------%s\n", dorado, reset);
        printf("%s[1]%s Mostrar Ciudades                 \n", cyan, reset);
        printf("%s[2]%s Buscar Rutas entre Ciudades     \n", cyan, reset);
        printf("%s[3]%s Mostrar Vuelos Disponibles      \n", cyan, reset);
        printf("%s[4]%s Mostrar Lista de Adyacencia     \n", cyan, reset);
        printf("%s[5]%s Mostrar Matriz de Adyacencia    \n", cyan, reset);
        printf("%s[6]%s Salir                          \n", cyan, reset);
        printf("%s------------------------------------%s\n", dorado, reset);
        printf("Seleccione una opción: ");


        if (scanf("%d", &opcionMenu) != 1) {
            printf("\n*** Error, valor introducido incorrecto ***\n");
            while (getchar() != '\n'); // Limpiar búfer
            continue;
        }

        switch (opcionMenu) {
            case 1:
                printf("\n%s>>> OPCIÓN SELECCIONADA: 1 <<<%s\n", cyan, reset);
                mostrar_ciudades();
                break;

            case 2:
                printf("\n%s>>> OPCIÓN SELECCIONADA: 2 <<<%s\n", cyan, reset);

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

                printf("\n%s>>> OPCIÓN SELECCIONADA: 3 <<<%s\n", cyan, reset);

                mostrar_ciudades();

                int origenRutas = pedir_ciudad("origen");
                printf("\nCiudad de origen: %s\n", nombres_aeropuertos[origenRutas]);
                mostrar_spinner("Cargando vuelos disponibles", 4000);
                mostrarRutasDesdeOrigen(grafo, origenRutas);


                break;

            case 4:
                printf("\n%s>>> OPCIÓN SELECCIONADA: 4 <<<%s\n", cyan, reset);

                // Mostrar lista de adyaciencia
                imprimirGrafo(grafo);

                break;

            case 5:

                printf("\n%s>>> OPCIÓN SELECCIONADA: 5 <<<%s\n", cyan, reset);


            printf("\n%s-------------------------------------------- MATRIZ DE ADYACENCIA --------------------------------------------%s\n\n", dorado, reset);
            // Obtener e imprimir matriz de adyacencia
            matriz = matrizAdyacencia(grafo);
            printf("\n%s--------------------------------------------------------------------------------------------------------------%s\n\n", dorado, reset);
            break;

            case 6:
                printf("\n>>> Saliendo del programa. ¡Hasta pronto!\n");

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
