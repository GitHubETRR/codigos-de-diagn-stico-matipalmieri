/*Crear un sistema que gestione un inventario de productos. Debe permitir realizar las siguientes 
operaciones:
- Agregar productos al inventario.
- Consultar el inventario y mostrar los productos almacenados.
- Actualizar la cantidad de un producto.
- Eliminar productos del inventario.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTOS 15
#define MAX_LETRAS 50

int bienvenida(void);
void agregarProducto(struct ,int *contador);
void mostrarInventario(struct ,int contador);
void actualizarCantidad(struct ,int contador);
void eliminarProducto(struct ,int *contador);

struct producto{
    char nombre[MAX_LETRAS];
    int id;
    int stock;
    float precio;
};

int main(){
    int contador = 0;
    struct Producto productos[MAX_PRODUCTOS];
    int bienvenida() = choice;
    do{
    switch (choice){
        case 1:
            agregarProducto(productos, &contador);
            break;
        case 2:
            mostrarInventario(productos,contador);
            break;
        case 3:
            actualizarCantidad(productos,contador);
            break;
        case 4:
            eliminarProducto(productos, contador);
            break;
        case 5:
            printf("Saliendo...");
            break;
        default:
            printf("Opción no valida, intente de nuevo. \n");
        }
    }while (opcion!=5);
    return 0;
}

int bienvenida(){
    int choice;
    printf("Este programa gestiona un inventario de productos de una tienda");
    printf("Ingrese:\n");
    printf("(1) Para agregar un producto \n");
    printf("(2) Para mostrar el inventario \n");
    printf("(3) Para actualizar el stock de un producto \n");
    printf("(4) Para eliminar un producto \n");
    printf("(5) Para salir del programa \n");
    scanf("%d"&choice)
    return choice;
}

agregarProducto(struct Producto productos[],int *contador ){
    if(*contador < MAX_PRODUCTOS){
        printf("Ingrese el nombre del producto: ");
        
        printf("Ingrese el código del producto: ");
        scanf("%d", &productos[*contador].ID);
        printf("Ingrese la cantidad disponible: ");
        scanf("%d", &productos[*contador].stock);
        printf("Ingrese el precio del producto: ");
        scanf("%f", &productos[*contador].precio);
        (*contador)++;
    }
    else printf("El inventario esta lleno. Deberás eliminar un producto si quieres añadir otro.");
}

void mostrarInventario(struct Producto productos[], int contador){
    if(contador==0) printf("El inventario esta vacío.");
    else{
        printf("\n--- INVENTARIO ---\n");
        for(i=0;i<contador;i++){
        printf("Nombre: %s \n"productos[i].nombre);
        printf("ID: %d \n"productos[i].id);
        printf("Stock: %d \n"productos[i].stock);
        printf("Precio: %2.f \n"productos[i].precio);
        }
    }
}

actualizarCantidad(struct Producto productos[], int contador){
    int id, cantidad;
    printf("\nIngrese el código del producto a actualizar: ");
    scanf("%d", &id);
    for(i=0;i<contador;i++){
        
    return;
    }
    printf("No se ha encontrado un producto con ID %d en el inventario. \n"id);
}

eliminarProducto(struct Producto productos[], int *contador){
    int id;
    printf("\nIngrese el código del producto a eliminar: ");
    scanf("%d", &id);
    for(i=0;i<*contador;i++){
    return;
    }
    printf("No se ha encontrado un producto con ID %d en el inventario. \n"id);
}