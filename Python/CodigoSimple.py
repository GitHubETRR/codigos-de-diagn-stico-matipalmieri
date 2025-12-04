import json
from enum import Enum
from typing import List, Dict

DATA_FILE = "tareas.json"

class Menu(Enum):
    AGREGAR = "1"
    MOSTRAR = "2"
    COMPLETAR = "3"
    DESCOMPLETAR = "4"
    GUARDAR = "5"
    SALIR = "6"

tareas: List[Dict] = []


def cargar_tareas():
    global tareas
    try:
        with open(DATA_FILE, "r", encoding="utf-8") as f:
            tareas = json.load(f)
    except FileNotFoundError:
        tareas = []
    except Exception as e:
        print(f"Error al cargar tareas: {e}")
        tareas = []


def guardar_tareas():
    try:
        with open(DATA_FILE, "w", encoding="utf-8") as f:
            json.dump(tareas, f, ensure_ascii=False, indent=2)
        print("Tareas guardadas correctamente.")
    except Exception as e:
        print(f"Error al guardar: {e}")


def mostrar_menu():
    print("\n - - - MENU DE TAREAS - - - ")
    for item in Menu:
        name = item.name.capitalize()
        print(f"{item.value}. {name}")


def agregar_tarea():
    tarea = input("Ingrese la tarea: ").strip()
    if tarea:
        tareas.append({"nombre": tarea, "completada": False})
        print("Tarea agregada exitosamente.")
    else:
        print("Tarea vacía, no se agregó.")


def mostrar_tareas():
    if not tareas:
        print("No hay tareas registradas.")
        return

    print("\nLista de tareas:")
    for i, t in enumerate(tareas, start=1):
        estado = "completa" if t.get("completada") else "incompleta"
        mark = "✓" if t.get("completada") else "✗"
        print(f"{i}. {t.get('nombre')} [{estado}] {mark}")


def seleccionar_indice(prompt: str) -> int:
    try:
        num = int(input(prompt))
        if 1 <= num <= len(tareas):
            return num - 1
        else:
            print("Número fuera de rango.")
            return -1
    except ValueError:
        print("Entrada inválida; ingresa un número.")
        return -1


def completar_tarea():
    if not tareas:
        print("No hay tareas para completar.")
        return

    mostrar_tareas()
    idx = seleccionar_indice("Ingresa el número de la tarea a completar: ")

    if idx >= 0:
        if tareas[idx].get("completada"):
            print("Esa tarea ya estaba completada.")
        else:
            tareas[idx]["completada"] = True
            print("Tarea marcada como completada.")


def descompletar_tarea():
    if not tareas:
        print("No hay tareas registradas.")
        return

    mostrar_tareas()
    idx = seleccionar_indice("Ingresa el número de la tarea a descompletar: ")

    if idx >= 0:
        if not tareas[idx].get("completada"):
            print("Esa tarea ya está incompleta.")
        else:
            tareas[idx]["completada"] = False
            print("Tarea desmarcada como completada.")


def main():
    cargar_tareas()
    while True:
        mostrar_menu()
        opcion = input("\nSelecciona una opción: ").strip()

        if opcion == Menu.AGREGAR.value:
            agregar_tarea()
        elif opcion == Menu.MOSTRAR.value:
            mostrar_tareas()
        elif opcion == Menu.COMPLETAR.value:
            completar_tarea()
        elif opcion == Menu.DESCOMPLETAR.value:
            descompletar_tarea()
        elif opcion == Menu.GUARDAR.value:
            guardar_tareas()
        elif opcion == Menu.SALIR.value:
            guardar_tareas()
            print("¡Hasta pronto!")
            break
        else:
            print("Opción inválida, intenta de nuevo.")


if __name__ == "__main__":
    main()

"""
Con colorama:
Antes de correr: ejecutar en la terminal una vez
pip install colorama

import json
from enum import Enum
from colorama import Fore, init
from typing import List, Dict

init(autoreset=True)

DATA_FILE = "tareas.json"

class Menu(Enum):
    AGREGAR = "1"
    MOSTRAR = "2"
    COMPLETAR = "3"
    DESCOMPLETAR = "4"
    GUARDAR = "5"
    SALIR = "6"

tareas: List[Dict] = []

def cargar_tareas():
    global tareas
    try:
        with open(DATA_FILE, "r", encoding="utf-8") as f:
            tareas = json.load(f)
    except FileNotFoundError:
        tareas = []
    except Exception as e:
        print(Fore.RED + f"Error al cargar tareas: {e}")
        tareas = []

def guardar_tareas():
    try:
        with open(DATA_FILE, "w", encoding="utf-8") as f:
            json.dump(tareas, f, ensure_ascii=False, indent=2)
        print(Fore.GREEN + "Tareas guardadas correctamente.")
    except Exception as e:
        print(Fore.RED + f"Error al guardar: {e}")

def mostrar_menu():
    print(Fore.CYAN + "\n - - - MENU DE TAREAS - - - ")
    for item in Menu:
        name = item.name.capitalize()
        print(f"{item.value}. {name}")

def agregar_tarea():
    tarea = input("Ingrese la tarea: ").strip()
    if tarea:
        tareas.append({"nombre": tarea, "completada": False})
        print(Fore.GREEN + "Tarea agregada exitosamente")
    else:
        print(Fore.RED + "Tarea vacía, no se agregó.")

def mostrar_tareas():
    if not tareas:
        print(Fore.YELLOW + "No hay tareas registradas.")
        return
    print("\nLista de tareas:")
    for i, t in enumerate(tareas, start=1):
        estado = "completa" if t.get("completada") else "incompleta"
        mark = Fore.GREEN + "✓" if t.get("completada") else Fore.RED + "✗"
        print(f"{i}. {t.get('nombre')} [{estado}] {mark}")

def seleccionar_indice(prompt: str) -> int:
    try:
        num = int(input(prompt))
        if 1 <= num <= len(tareas):
            return num - 1
        else:
            print(Fore.RED + "Número fuera de rango.")
            return -1
    except ValueError:
        print(Fore.RED + "Entrada inválida; ingresa un número.")
        return -1

def completar_tarea():
    if not tareas:
        print(Fore.YELLOW + "No hay tareas para completar.")
        return
    mostrar_tareas()
    idx = seleccionar_indice("Ingresa el número de la tarea a completar: ")
    if idx >= 0:
        if tareas[idx].get("completada"):
            print(Fore.YELLOW + "Esa tarea ya estaba completada.")
        else:
            tareas[idx]["completada"] = True
            print(Fore.GREEN + "Tarea marcada como completada.")

def descompletar_tarea():
    if not tareas:
        print(Fore.YELLOW + "No hay tareas registradas.")
        return
    mostrar_tareas()
    idx = seleccionar_indice("Ingresa el número de la tarea a descompletar: ")
    if idx >= 0:
        if not tareas[idx].get("completada"):
            print(Fore.YELLOW + "Esa tarea ya está incompleta.")
        else:
            tareas[idx]["completada"] = False
            print(Fore.GREEN + "Tarea desmarcada como completada.")

def main():
    cargar_tareas()
    while True:
        mostrar_menu()
        opcion = input("\nSelecciona una opcion: ").strip()
        if opcion == Menu.AGREGAR.value:
            agregar_tarea()
        elif opcion == Menu.MOSTRAR.value:
            mostrar_tareas()
        elif opcion == Menu.COMPLETAR.value:
            completar_tarea()
        elif opcion == Menu.DESCOMPLETAR.value:
            descompletar_tarea()
        elif opcion == Menu.GUARDAR.value:
            guardar_tareas()
        elif opcion == Menu.SALIR.value:
            guardar_tareas()
            print(Fore.CYAN + "¡Hasta pronto!")
            break
        else:
            print(Fore.RED + "Opcion invalida, intenta de nuevo")

if __name__ == "__main__":
    main()
"""
