/*Este es el código simple que hice el 15/5 en papel. Es simple porque no teníamos las compus o wifi y porque es solo 
para entender sobre las listas enlazadas.*/

#include <stdio.h>
#include <stdlib.h>

#define VAL1 10
#define VAL2 20
#define VAL3 30

typedef struct nodo {
    int dato;
    struct nodo* siguiente; //para enlazar un nodo con el siguiente
}nodo;

nodo* CrearNodo(int);
void AgregarFinal(nodo** first, int);
void MostrarLista(nodo* first);
void LiberarLista(nodo* first);

int main(){
    nodo* lista = NULL; //puntero que apunta al incio arranca apuntando a NULL
    AgregarFinal(&lista,VAL1);
    AgregarFinal(&lista,VAL2); //agrego tres nodos al final
    AgregarFinal(&lista,VAL3);
    printf("\033[1;31m\033[1m- - - - LISTA ENLAZADA - - - -\033[0m\033[0m\n");
    MostrarLista(lista);
    LiberarLista(lista);
    return 0;
}

nodo* CrearNodo(int valor){
    nodo* nuevo = (nodo*)malloc(sizeof(nodo)); //pido la memoria que necesito
    nuevo->dato = valor; //le asigno a "dato" el valor recibido
    nuevo->siguiente = NULL;
    return nuevo;
}

void AgregarFinal(nodo** first, int valor){ //doble puntero para poder modificarlo si es que *first=NULL
    nodo* nuevo = CrearNodo(valor); //creo el nodo nuevo
    if(*first == NULL){
        *first = nuevo; //si estaba vacía, ahora este nodo será el nuevo first
    }else{
        nodo* actual = *first;
        while(actual->siguiente!=NULL){ //recorro hasta encontrar el último nodo (el que apunte a NULL)
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo; //enlazo el campo "siguiente" del último nodo al nuevo nodo
    }
}

void MostrarLista(nodo*first){
    nodo* actual = first; //se crea el puntero y apunta al primero
    while(actual!=NULL){ //si actual apunta a NULL, deja de recorrer
        printf("%d->",actual->dato);
        actual = actual->siguiente; //avanza al siguiente nodo luego de haberlo impreso
    }
    printf("NULL\n - - - - - - - - - - - - - - -"); //por ej: 10->20->30->NULL
}

void LiberarLista(nodo* first){
    nodo*actual = first;
    while(actual!=NULL){
        nodo* temporal = actual;
        actual = actual->siguiente;
        free(temporal); // voy liberando cada nodo
    }
}