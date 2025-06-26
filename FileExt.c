#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void guardar_nombre(char *nombre){
    FILE *archivo = fopen("nombres.txt", "a"); // la a es porq guarda el dato al final, solo le doy un nombre porque quiero que abra dicho archivo en la misma carpeta donde estoy trabajando
    fprintf(archivo, "%s\n", nombre); // (file)printf escribe en el archivo
    fclose(archivo);
}

void mostrar_nombres(){
    FILE *archivo = fopen("nombres.txt", "r"); // la r es porq lo abro solo para lectura
    char linea[100]; // creo un lugar donde colocar los nombres, que luego voy a recorrer e imprimir
    printf("\n\033[1;36m - - - Lista de nombres - - - \033[0m\n");
    while (fgets(linea, sizeof(linea), archivo)){
        //linea[strcspn(linea, "\n")] = 0; ---> esto me lo recomendo chat, porque no sabía como eliminar un enter que se generaba automaticamente por el fgets, pero me elimina todos y no solo el ultimo
        printf("%s", linea);
    }
    printf("\033[1;36m------------------------\033[0m\n");
    fclose(archivo);
}
