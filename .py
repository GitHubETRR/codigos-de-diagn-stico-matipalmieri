import math
import random
import sys
from enum import Enum
from copy import deepcopy #crea copias completas de estructuras

FILAS = 6
COLUMNAS = 7
EMPTY = 0
PLAYER_PIECE = 1
AI_PIECE = 2
VENTANA = 4

class Menu(Enum):
    DOS_JUGADORES = "1"
    CONTRA_IA = "2"
    SALIR = "3"

def crear_tablero():
    return [[EMPTY for _ in range(COLUMNAS)] for _ in range(FILAS)]

def imprimir_tablero(tablero):
    print("\n  " + "  ".join(str(i+1) for i in range(COLUMNAS)))
    for r in range(FILAS):
        fila = tablero[r]
        print("| " + " ".join(symbol(c) for c in fila) + " |")
    print("-" * (COLUMNAS * 2 + 5))

def symbol(valor):
    if valor == PLAYER_PIECE:
        return "X"
    elif valor == AI_PIECE:
        return "O"
    else:
        return "."

def columna_valida(tablero, col):
    return tablero[0][col] == EMPTY

def obtener_fila_libre(tablero, col):
    for f in range(FILAS-1, -1, -1):
        if tablero[f][col] == EMPTY:
            return f
    return None

def poner_ficha(tablero, fila, col, pieza):
    tablero[fila][col] = pieza

def movimientos_validos(tablero):
    return [c for c in range(COLUMNAS) if columna_valida(tablero, c)]

def es_empate(tablero):
    return all(tablero[0][c] != EMPTY for c in range(COLUMNAS))

def revisar_ganador(tablero, pieza):
    # revisar horizontales
    for r in range(FILAS):
        for c in range(COLUMNAS - 3):
            if all(tablero[r][c+i] == pieza for i in range(4)):
                return True
    # revisar verticales
    for c in range(COLUMNAS):
        for r in range(FILAS - 3):
            if all(tablero[r+i][c] == pieza for i in range(4)):
                return True
    # diagonal(/)
    for r in range(3, FILAS):
        for c in range(COLUMNAS - 3):
            if all(tablero[r-i][c+i] == pieza for i in range(4)):
                return True
    # diagonal(\)
    for r in range(FILAS - 3):
        for c in range(COLUMNAS - 3):
            if all(tablero[r+i][c+i] == pieza for i in range(4)):
                return True
    return False

#de aca en adelante esta todo medio en piloto
def puntaje_ventana(ventana, pieza):
    puntaje = 0
    pieza_oponente = PLAYER_PIECE if pieza == AI_PIECE else AI_PIECE

    if ventana.count(pieza) == 4:
        puntaje += 100
    elif ventana.count(pieza) == 3 and ventana.count(EMPTY) == 1:
        puntaje += 5
    elif ventana.count(pieza) == 2 and ventana.count(EMPTY) == 2:
        puntaje += 2

    if ventana.count(pieza_oponente) == 3 and ventana.count(EMPTY) == 1:
        puntaje -= 4

    return puntaje

def puntaje_posicion(tablero, pieza):
    puntaje = 0

    # preferir columna central
    centro_array = [tablero[r][COLUMNS//2] for r in range(ROWS)]
    centro_count = centro_array.count(pieza)
    puntaje += centro_count * 3

    # horizontales
    for r in range(ROWS):
        fila_array = tablero[r]
        for c in range(COLUMNS - 3):
            ventana = fila_array[c:c+WINDOW_LENGTH]
            puntaje += puntaje_ventana(ventana, pieza)

    # verticales
    for c in range(COLUMNS):
        col_array = [tablero[r][c] for r in range(ROWS)]
        for r in range(ROWS - 3):
            ventana = col_array[r:r+WINDOW_LENGTH]
            puntaje += puntaje_ventana(ventana, pieza)

    # diagonales positivas
    for r in range(ROWS - 3):
        for c in range(COLUMNS - 3):
            ventana = [tablero[r+i][c+i] for i in range(WINDOW_LENGTH)]
            puntaje += puntaje_ventana(ventana, pieza)

    # diagonales negativas
    for r in range(ROWS - 3):
        for c in range(COLUMNS - 3):
            ventana = [tablero[r+3-i][c+i] for i in range(WINDOW_LENGTH)]
            puntaje += puntaje_ventana(ventana, pieza)

    return puntaje

def es_estado_terminal(tablero):
    return revisar_ganador(tablero, PLAYER_PIECE) or revisar_ganador(tablero, AI_PIECE) or es_empate(tablero)
