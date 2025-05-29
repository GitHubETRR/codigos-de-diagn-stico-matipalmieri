#include <stdio.h>
#include <string.h>
#include "file_utils.h"

enum MENU{
    AGREGAR=1,
    MOSTRAR,
    SALIR
};

int main() {
    int opcion;
    char nombre[100];
    do{
        printf("\n- - - - Menu - - - -\n");
        printf("%d. Agregar nombre\n", AGREGAR);
        printf("%d. Mostrar nombres\n", MOSTRAR);
        printf("%d. Salir\n", SALIR);
        printf("Tu eleccion: ");
        scanf("%d", &opcion);
        getchar();
        switch(opcion){
            case 1:
                printf("Ingresa un nombre: ");
                fgets(nombre, sizeof(nombre), stdin);
                guardar_nombre(nombre);
                break;
            case 2:
                mostrar_nombres();
                break;
            case 3:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while(opcion != 3);

    return 0;
}
