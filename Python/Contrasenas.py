import random
import string
from enum import Enum


class Menu(Enum):
    GENERAR = "1"
    VALIDAR = "2"
    GUARDAR = "3"
    LEER = "4"
    ESTADISTICAS = "5"
    SALIR = "6"


def generar_contraseña(longitud=12):
    caracteres = string.ascii_letters + string.digits + string.punctuation
    return "".join(random.choice(caracteres) for _ in range(longitud))


def validar_contraseña(password):
    criterios = {
        "mayuscula": any(c.isupper() for c in password),
        "minuscula": any(c.islower() for c in password),
        "numero": any(c.isdigit() for c in password),
        "especial": any(c in string.punctuation for c in password),
        "longitud": len(password) >= 8
    }

    puntaje = sum(criterios.values())

    if puntaje == 5:
        return "Fuerte"
    elif puntaje >= 3:
        return "Media"
    else:
        return "Débil"


def guardar(password, archivo="passwords.txt"):
    try:
        with open(archivo, "a") as f:
            f.write(password + "\n")
        print("Contraseña guardada.")
    except Exception as e:
        print("Error al guardar:", e)


def leer_passwords(archivo="passwords.txt"):
    try:
        with open(archivo, "r") as f:
            return [line.strip() for line in f]
    except FileNotFoundError:
        print("No hay contraseñas guardadas.")
        return []


def estadisticas(passwords):
    conteo = {"Fuerte": 0, "Media": 0, "Débil": 0}
    for p in passwords:
        nivel = validar_contraseña(p)
        conteo[nivel] += 1

    print("\n=== ESTADÍSTICAS ===")
    for nivel, cantidad in conteo.items():
        print(f"{nivel}: {cantidad}")


def main():
    passwords_generadas = []
    while True:
        print("\n=== MENÚ ===")
        print("1. Generar contraseña")
        print("2. Validar contraseña")
        print("3. Guardar contraseña generada")
        print("4. Leer contraseñas guardadas")
        print("5. Ver estadísticas")
        print("6. Salir")

        opcion = input("Elegí una opción: ")

        if opcion == Menu.GENERAR.value:
            try:
                long = int(input("Longitud de la contraseña (mínimo 8): "))
                if long < 8:
                    print("La longitud mínima es 8.")
                    continue
                pwd = generar_contraseña(long)
                passwords_generadas.append(pwd)
                print("Contraseña generada:", pwd)
            except ValueError:
                print("Debes ingresar un número válido.")

        elif opcion == Menu.VALIDAR.value:
            pwd = input("Ingresá la contraseña: ")
            print("Nivel:", validar_contraseña(pwd))

        elif opcion == Menu.GUARDAR.value:
            if passwords_generadas:
                guardar(passwords_generadas[-1])
            else:
                print("No hay contraseñas generadas aún.")

        elif opcion == Menu.LEER.value:
            lista = leer_passwords()
            print("\nContraseñas guardadas:")
            for p in lista:
                print("-", p)

        elif opcion == Menu.ESTADISTICAS.value:
            lista = leer_passwords()
            estadisticas(lista)

        elif opcion == Menu.SALIR.value:
            print("Saliendo...")
            break

        else:
            print("Opción no válida.")


if __name__ == "__main__":
    main()

"""
con colorama incluido:
import random
import string
from enum import Enum
from colorama import Fore, init

init(autoreset=True)  # Restablece colores después de cada print


class Menu(Enum):
    GENERAR = "1"
    VALIDAR = "2"
    GUARDAR = "3"
    LEER = "4"
    ESTADISTICAS = "5"
    SALIR = "6"


def generar_contraseña(longitud=12):
    caracteres = string.ascii_letters + string.digits + string.punctuation
    return "".join(random.choice(caracteres) for _ in range(longitud))


def validar_contraseña(password):
    criterios = {
        "mayuscula": any(c.isupper() for c in password),
        "minuscula": any(c.islower() for c in password),
        "numero": any(c.isdigit() for c in password),
        "especial": any(c in string.punctuation for c in password),
        "longitud": len(password) >= 8
    }

    puntaje = sum(criterios.values())

    if puntaje == 5:
        return "Fuerte"
    elif puntaje >= 3:
        return "Media"
    else:
        return "Débil"


def guardar(password, archivo="passwords.txt"):
    try:
        with open(archivo, "a") as f:
            f.write(password + "\n")
        print(Fore.GREEN + "Contraseña guardada.")
    except Exception as e:
        print(Fore.RED + "Error al guardar:", e)


def leer_passwords(archivo="passwords.txt"):
    try:
        with open(archivo, "r") as f:
            return [line.strip() for line in f]
    except FileNotFoundException:
        print(Fore.RED + "No hay contraseñas guardadas.")
        return []


def mostrar_menu():
    print(Fore.CYAN + "\n=== MENÚ DE CONTRASEÑAS ===")
    print(f"{Menu.GENERAR.value}. Generar contraseña")
    print(f"{Menu.VALIDAR.value}. Validar contraseña")
    print(f"{Menu.GUARDAR.value}. Guardar última contraseña generada")
    print(f"{Menu.LEER.value}. Leer contraseñas guardadas")
    print(f"{Menu.ESTADISTICAS.value}. Ver estadísticas")
    print(f"{Menu.SALIR.value}. Salir")


def estadisticas(passwords):
    conteo = {"Fuerte": 0, "Media": 0, "Débil": 0}
    for p in passwords:
        nivel = validar_contraseña(p)
        conteo[nivel] += 1

    print(Fore.CYAN + "\n=== ESTADÍSTICAS ===")
    for nivel, cantidad in conteo.items():
        color = Fore.GREEN if nivel == "Fuerte" else Fore.YELLOW if nivel == "Media" else Fore.RED
        print(color + f"{nivel}: {cantidad}")


def main():
    passwords_generadas = []

    while True:
        mostrar_menu()
        opcion = input(Fore.YELLOW + "\nElegí una opción: ")

        if opcion == Menu.GENERAR.value:
            try:
                long = int(input("Longitud de la contraseña (mínimo 8): "))
                if long < 8:
                    print(Fore.RED + "La longitud mínima es 8.")
                    continue
                pwd = generar_contraseña(long)
                passwords_generadas.append(pwd)
                print(Fore.GREEN + "Contraseña generada:", Fore.YELLOW + pwd)
            except ValueError:
                print(Fore.RED + "Debes ingresar un número válido.")

        elif opcion == Menu.VALIDAR.value:
            pwd = input("Ingresá la contraseña: ")
            nivel = validar_contraseña(pwd)

            color = Fore.GREEN if nivel == "Fuerte" else Fore.YELLOW if nivel == "Media" else Fore.RED
            print(color + f"Nivel de seguridad: {nivel}")

        elif opcion == Menu.GUARDAR.value:
            if passwords_generadas:
                guardar(passwords_generadas[-1])
            else:
                print(Fore.RED + "No hay contraseñas generadas aún.")

        elif opcion == Menu.LEER.value:
            lista = leer_passwords()
            print(Fore.CYAN + "\nContraseñas guardadas:")
            if not lista:
                print(Fore.RED + "No se encontraron contraseñas.")
            for p in lista:
                print(Fore.YELLOW + "- " + p)

        elif opcion == Menu.ESTADISTICAS.value:
            lista = leer_passwords()
            estadisticas(lista)

        elif opcion == Menu.SALIR.value:
            print(Fore.CYAN + "Saliendo...")
            break

        else:
            print(Fore.RED + "Opción no válida.")


if __name__ == "__main__":
    main()

"""
