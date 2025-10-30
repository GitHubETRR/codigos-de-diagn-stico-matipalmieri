from enum import Enum

pip install colorama #solo hace falta una vez y es para poder usar colorama
from colorama import Fore init
init(autoreset=True) #para que despues de cada print, vuelva a la normalidad

class Menu(Enum):
    AGREGAR = "1"
    MOSTRAR = "2"
    COMPLETAR = "3"
    SALIR = "4"

tareas = []

def mostrar_menu():
    print(Fore.CYAN + "\n - - - MENU DE TAREAS - - - ")
    print(f"{Menu.AGREGAR.value}. Agregar tarea")
    print(f"{Menu.MOSTRAR.value}. Mostrar tareas")
    print(f"{Menu.COMPLETAR.value}. Completar tarea")
    print(f"{Menu.SALIR.value}. Salir")

def agregar_tarea():
    tarea = input("Ingrese la tarea: ")
    tareas.append({"nombre": tarea, "completada": False})
    print(Fore.GREEN + "Tarea agregada exitosamente")

def mostrar_tareas():
    if not tareas:
        print(Fore.RED + "No hay tareas pendientes")
    else:
        print("\nLista de tareas:")
        for i, t in enumerate(tareas):
            estado = "completa" if t["completada"] else "incompleta"
            print(f"{i+1}. {t['nombre']} [{estado}]")

def completar_tarea():
    mostrar_tareas()
    if tareas:
        num = int(input("Ingresa el numero de la tarea a completar: "))
        if 1 <= num <= len(tareas):
            tareas[num-1]["completada"] = True
            print(Fore.GREEN + "Tarea completada exitosamente")
        else:
            print(Fore.RED + "Numero invalido")

while True:
    mostrar_menu()
    opcion = input("\nSelecciona una opcion: ")

    if opcion == Menu.AGREGAR.value:
        agregar_tarea()
    elif opcion == Menu.MOSTRAR.value:
        mostrar_tareas()
    elif opcion == Menu.COMPLETAR.value:
        completar_tarea()
    elif opcion == Menu.SALIR.value:
        print("¡Hasta pronto!")
        break
    else:
        print(Fore.RED + "Opcion invalida, intenta de nuevo")
