#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

enum MENU{
    AGREGAR=1,
    LISTAR,
    BUSCAR,
    SALIR
};

typedef struct contacto{
    char nombre[MAX];
    char telefono[MAX];
    char email[MAX];
    struct contacto* siguiente;
}contacto;

contacto* CrearContacto(const char* nombre, const char* telefono, const char* email);
void AgregarContacto(const char* nombre, const char* telefono, const char* email);
void ListarContactos();
void BuscarContacto(const char* nombreBuscado);
void GuardarContactos(const char* archivo);
void CargarContactos(const char* archivo);
void LiberarContactos();

contacto* lista = NULL;

int main(){
    int eleccion;
    char nombre[MAX], telefono[MAX], email[MAX];
    const char* archivo = "contactos.txt";
    CargarContactos(archivo);
    do{
        printf("\n\033[1;32m- - - MENU - - -\033[0m\n");
        printf("%d. Agregar contacto", AGREGAR);
        printf("\n%d. Listar contactos", LISTAR);
        printf("\n%d. Buscar contacto", BUSCAR);
        printf("\n%d. Salir", SALIR);
        printf("\nIngresa tu una eleccion: ");
        scanf("%d",&eleccion);
        getchar();//para sacar el salto de línea

        switch(eleccion){
            case AGREGAR:
                printf("\nNombre: ");
                fgets(nombre, MAX, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                printf("Teléfono: ");
                fgets(telefono, MAX, stdin);
                telefono[strcspn(telefono, "\n")] = '\0';
                printf("Email: ");
                fgets(email, MAX, stdin);
                email[strcspn(email, "\n")] = '\0';
                AgregarContacto(nombre, telefono, email);
                break;
            case LISTAR:
                ListarContactos();
                break;
            case BUSCAR:
                printf("\nNombre para buscar: ");
                fgets(nombre, MAX, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                BuscarContacto(nombre);
                break;
            case SALIR:
                GuardarContactos(archivo);
                LiberarContactos();
                printf("\n\033[1;31mGuardado baa baaaiii\033[0m");
                break;
            default:
                printf ("\033[1;31mOpcion no valida, intenta de nuevo.\033[0m\n");
        }
    } while(eleccion != 4);
    return 0;
}

contacto* CrearContacto(const char* nombre, const char* telefono, const char* email) {
    contacto* nuevo = (contacto*)malloc(sizeof(contacto));
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->telefono, telefono);
    strcpy(nuevo->email, email);
    nuevo->siguiente = NULL;
    return nuevo;
}
void AgregarContacto(const char* nombre, const char* telefono, const char* email){
    contacto* nuevo = CrearContacto(nombre, telefono, email);
    nuevo->siguiente = lista;
    lista = nuevo;
}

void ListarContactos(){
    contacto* actual = lista;
    int num = 1;
        printf("\n\033[1;36m- - - Lista de contactos - - - \033[0m\n");
        while(actual != NULL){
        printf(" \n- Contacto %d -  ",num);
        printf("\nNombre: %s\n", actual->nombre);
        printf("Telefono: %s\n", actual->telefono);
        printf("Email: %s\n", actual->email);
        actual = actual->siguiente;
        num++;
        }
        printf("\n\033[1;36m- - - - - - - - - -\033[0m\n");
}

void BuscarContacto(const char* NombreBuscado){
    contacto* actual = lista;
    while(actual != NULL){
        if(strcmp(actual->nombre, NombreBuscado) == 0){
            printf("\n\033[1;35m- Contacto encontrado -\033[0m\n");
            printf("Nombre: %s\n", actual->nombre);
            printf("Telefono: %s\n", actual->telefono);
            printf("Email: %s\n", actual->email);
            return;
        }
        actual = actual->siguiente;
    }
    printf("\n\033[1;31mNo encontre ese contacto, proba otra vez.\033[0m\n");
}

void GuardarContactos(const char* archivo){
    FILE* f = fopen(archivo, "w");
    if(!f){
        printf("\033[1;31mNo se pudo abrir el archivo.\033[0m\n");
        return;
    }
    contacto* actual = lista;
    while(actual != NULL){
        fprintf(f,"%s;%s;%s\n", actual->nombre, actual->telefono, actual->email);
        actual = actual->siguiente;
    }
    fclose(f);
}

void CargarContactos(const char* archivo) {
    FILE* f = fopen(archivo, "r");
    if (!f) return;
    char linea[3 * MAX];
    while (fgets(linea, sizeof(linea), f)) {
        char nombre[MAX], telefono[MAX], email[MAX];
        if (sscanf(linea, "%99[^;];%99[^;];%99[^\n]", nombre, telefono, email) == 3){
            AgregarContacto(nombre, telefono, email);
        }
    }
    fclose(f);
}

void LiberarContactos() {
    contacto* actual = lista;
    while (actual != NULL) {
        contacto* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}
