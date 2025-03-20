/*Crear un sistema que gestione un inventario de productos. Debe permitir realizar las siguientes 
operaciones:
- Agregar productos al inventario.
- Consultar el inventario y mostrar los productos almacenados.
- Actualizar la cantidad de un producto.
- Eliminar productos del inventario.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTOS 5
#define MAX_LETRAS 50

struct producto{
    char nombre[MAX_LETRAS];
    int id;
    int stock;
    float precio;
};

int bienvenida(void);
void limpiarBuffer(void);
void agregarProducto(struct producto productos[],int *contador);
void mostrarInventario(struct producto productos[],int contador);
void actualizarCantidad(struct producto productos[],int contador);
void eliminarProducto(struct producto productos[],int *contador);

int main(){
    int contador=0,choice;
    struct producto productos[MAX_PRODUCTOS];
    do{
        choice = bienvenida();
        limpiarBuffer();
        switch (choice){
        case 1:
            agregarProducto(productos,&contador);
            break;
        case 2:
            mostrarInventario(productos,contador);
            break;
        case 3:
            actualizarCantidad(productos,contador);
            break;
        case 4:
            eliminarProducto(productos,&contador);
            break;
        case 5:
            printf("Saliendo...");
            break;
        default:
            printf("Opción no valida, intente de nuevo. \n");
        }
    }while (choice!=5);
    return 0;
}

int bienvenida(){
    int choice;
    printf("\033[0;34mEste programa gestiona un inventario de productos de una tienda.\033[0m\n");
    printf("\033[0;36mIngrese:\033[0m\n");
    printf("\033[0;32m(1)\033[0m Para agregar un producto. \n");
    printf("\033[0;32m(2)\033[0m Para mostrar el inventario. \n");
    printf("\033[0;32m(3)\033[0m Para actualizar el stock de un producto. \n");
    printf("\033[0;32m(4)\033[0m Para eliminar un producto. \n");
    printf("\033[0;32m(5)\033[0m Para salir del programa. \n");
    scanf("%d",&choice);
    return choice;
}

void limpiarBuffer() {
    while (getchar() != '\n'); //lee los carácteres y los va eliminando
}

void agregarProducto(struct producto productos[],int *contador ){
    if(*contador < MAX_PRODUCTOS){
        printf("Ingrese el nombre del producto: ");
        scanf("%s",productos[*contador].nombre);
        limpiarBuffer();

        printf("Ingrese el código del producto: ");
        scanf("%d", &productos[*contador].id);

        printf("Ingrese la cantidad disponible: ");
        scanf("%d", &productos[*contador].stock);

        printf("Ingrese el precio del producto (use punto en vez de coma): ");
        scanf("%f", &productos[*contador].precio);
        
        (*contador)++;
    }
    else printf("\033[0;31mEl inventario esta lleno. Deberás eliminar un producto si quieres añadir otro.\033[0m");
}

void mostrarInventario(struct producto productos[], int contador){
    if(contador==0) printf("\033[0;31mEl inventario esta vacío.\033[0m\n");
    else{
        printf("\n\033[4m\033[1m- - - INVENTARIO - - -\033[0m\033[0m\n\n");
        for(int i=0;i<contador;i++){
        printf("Nombre: %s \n",productos[i].nombre);
        printf("ID: %d \n",productos[i].id);
        printf("Stock: %d \n",productos[i].stock);
        printf("Precio: %.2f \n\033[0;35m-----------------\033[0m\n",productos[i].precio);
        }
    }
}

void actualizarCantidad(struct producto productos[], int contador){
    int id, cantidad;
    printf("\nIngrese el código del producto a actualizar: ");
    scanf("%d", &id);
    for(int i=0;i<contador;i++){
        if(productos[i].id == id){
            printf("Ingrese la nueva cantidad de stock: ");
            scanf("%d",&productos[i].stock);
            printf("La carga se ha realizado con éxito.\n");
            return;
        }
    }
    printf("\033[0;31mNo se ha encontrado un producto con ID %d en el inventario.\033[0m\n",id);
}

void eliminarProducto(struct producto productos[], int *contador){
    int id;
    printf("\nIngrese el código del producto a eliminar: ");
    scanf("%d",&id);
    for(int i=0;i<*contador;i++){
        if(productos[i].id == id){
            for(int j=i;j<*contador-1;j++){
                productos[j] = productos[j+1];
            }
            (*contador)--;
            printf("Producto eliminado con éxito.\n");
            return;
        }
    }
    printf("\033[0;31mNo se ha encontrado un producto con ID %d en el inventario.\033[0m\n",id);
}