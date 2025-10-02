tareas = []

def mostrar_menu():
    print("\n - - - MENU DE TAREAS - - - ")
    print("1. Agregar tarea")
    print("2. Mostrar tareas")
    print("3. Completar tarea")
    print("4. Salir")

def agregar_tarea():
    tarea = input("Ingrese la tarea: ")
    tareas.append({"nombre": tarea, "completada": False})
    print("Tarea agregada con éxito")

def mostrar_tareas():
    if not tareas:
        print("No hay tareas pendientes.")
    else:
        print("\nLista de tareas:")
        for i, t in enumerate(tareas):
            estado = "ok" if t["completada"] else "no"
            print(f"{i+1}. {t['nombre']} [{estado}]")

def completar_tarea():
    mostrar_tareas()
    if tareas:
        num = int(input("Ingrese el numero de la tarea a completar: "))
        if 1 <= num <= len(tareas):
            tareas[num-1]["completada"] = True
            print("Tarea completada con éxito")
        else:
            print("Numero inválido")

while True:
    mostrar_menu()
    opcion = input("Seleccione una opcion: ")
    if opcion == "1":
        agregar_tarea()
    elif opcion == "2":
        mostrar_tareas()
    elif opcion == "3":
        completar_tarea()
    elif opcion == "4":
        print("¡Hasta luego!")
        break
    else:
        print("Opcion invalida, intente nuevamente.")