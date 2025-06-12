#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct contacto{
    char nombre[MAX];
    char telefono[MAX];
    char email[MAX];
    struct contacto* siguiente;
}contacto;

faltan prototipos

contacto* lista = NULL

int main(){
    int opcion;
    const char* archivo = "contactos.txt"
    CargarContactos(archivo);
    do{
        printf("\n1. Agregar contacto");
        printf("\n2. Listar contactos");
        printf("\n3. Buscar contacto");
        printf("\n4. Salir");
        printf("Selecciona una opcion: ");
        scanf("%d",&opcion);
        getchar();//para sacar el salto de línea

        switch(opcion){
            case 1:
                break;
            case 2:
                ListarContactos();
                break;
            case 3:
                printf("Nombre para buscar: ");
                break;
            case 4:
                break;
            default:
                printf ("Opcion no valida, intenta de nuevo.\n");
        }
    } while(opcion != 4);
    return 0;
}

