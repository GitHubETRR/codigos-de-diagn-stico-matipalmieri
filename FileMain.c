#include <stdio.h>
#include <string.h>
#include "FileExt.h"

enum MENU{
    AGREGAR=1,
    MOSTRAR,
    SALIR
};

int main(){
    int opcion;
    char nombre[100];
    do{
        printf("\n\033[1;31m- - - - Menu - - - -\033[0m\n");
        printf("%d. Agregar nombre\n", AGREGAR);
        printf("%d. Mostrar nombres\n", MOSTRAR);
        printf("%d. Salir\n", SALIR);
        printf("Tu eleccion: ");
        scanf("%d", &opcion);
        getchar();
        switch(opcion){
            case AGREGAR:
                printf("Ingresa un nombre: ");
                fgets(nombre, sizeof(nombre), stdin);
                guardar_nombre(nombre);
                break;
            case MOSTRAR:
                mostrar_nombres();
                break;
            case SALIR:
                printf("Saliendo...\n");
                break;
        default:
                printf("Opcion no valida.\n");
        }
    }while(opcion != 3);
    return 0;
}
