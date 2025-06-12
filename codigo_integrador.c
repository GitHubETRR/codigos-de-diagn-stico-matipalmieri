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

Contacto* CrearContacto(const char* nombre, const char* telefono, const char* email);
void AgregarContacto(const char* nombre, const char* telefono, const char* email);
void ListarContactos();
void BuscarContacto(const char* nombreBuscado);
void GuardarContactos(const char* archivo);


contacto* lista = NULL

int main(){
    int opcion;
    char nombre[MAX], telefono[MAX], email[MAX];
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
                printf("Nombre: ");
                fgets(nombre, MAX, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                printf("Teléfono: ");
                fgets(telefono, MAX, stdin);
                telefono[strcspn(telefono, "\n")] = '\0';
                printf("Email: ");
                fgets(email, MAX, stdin);
                email[strcspn(email, "\n")] = '\0';
                agregarContacto(nombre, telefono, email);
                break;
            case 2:
                ListarContactos();
                break;
            case 3:
                printf("Nombre para buscar: ");
                fgets(nombre, MAX, stdin);
                nombre[strcpn(nombre, "\n")] = '\0';
                BuscarContacto(nombre);
                break;
            case 4:
                GuardarContactos(archivo);
                LiberarContactos();
                printf("Guardado baa baaaiii");
                break;
            default:
                printf ("Opcion no valida, intenta de nuevo.\n");
        }
    } while(opcion != 4);
    return 0;
}

void AgregarContacto(const char* nombre, const char* telefono, const char* email){
    contacto* nuevo = CrearContacto(nombre, telefono, email);
    nuevo->siguiente = lista;
    lista = nuevo;
}

void ListarContactos(){
    contacto* actual = lista;
    while(actual != NULL){
        printf("Nombre: %s\n", actual->nombre);
        printf("Telefono; %s\n", actual->telefono);
        printf("Email; %s\n", actual->email);
        actual = actual->siguiente;
    }
}

void BuscarContacto(const char* NombreBuscado){
    contacto* actual = lista;
    while(actual != NULL){
        if(strcmp(actual->nombre, NombreBuscado) == 0){
            printf("- Contacto encontrado:");
            printf("Nombre: %s\n", actual->nombre);
            printf("Telefono: %s\n", actual->telefono);
            printf("Email: %s\n", actual->email);
            return;
        }
        actual = actual->siguiente
    }
    printf("No encontre ese contacto, proba otra")
}

void GuardarContacto(const char* archivo){

}