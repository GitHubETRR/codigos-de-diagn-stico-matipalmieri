#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"

void guardar_nombre(const char *nombre){
    FILE *archivo = fopen("nombres.txt", "a"); // la a es porq guarda el dato al final
    fprintf(archivo, "%s\n", nombre); // (file)printf escribe en el archivo
    fclose(archivo);
}

void mostrar_nombres(){
    FILE *archivo = fopen("nombres.txt", "r"); // la r es porq lo abro solo para lectura
    char linea[100];
    printf("\n--- Lista de nombres ---\n");
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea);
    }
    printf("------------------------\n");
    fclose(archivo);
}
