"""
import math
import random
import sys
from enum import Enum
from copy import deepcopy

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


def symbol(valor):
    if valor == PLAYER_PIECE:
        return "X"
    elif valor == AI_PIECE:
        return "O"
    else:
        return "."


def imprimir_tablero(tablero):
    print()
    print("  " + " ".join(str(i + 1) for i in range(COLUMNAS)))

    for r in range(FILAS):
        fila = "| " + " ".join(symbol(c) for c in tablero[r]) + " |"
        print(fila)

    print("+" + "---" * COLUMNAS + "+")


def columna_valida(tablero, col):
    return tablero[0][col] == EMPTY


def obtener_fila_libre(tablero, col):
    for f in range(FILAS - 1, -1, -1):
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
    # horizontales
    for r in range(FILAS):
        for c in range(COLUMNAS - 3):
            if all(tablero[r][c + i] == pieza for i in range(4)):
                return True

    # verticales
    for c in range(COLUMNAS):
        for r in range(FILAS - 3):
            if all(tablero[r + i][c] == pieza for i in range(4)):
                return True

    # diagonales /
    for r in range(3, FILAS):
        for c in range(COLUMNAS - 3):
            if all(tablero[r - i][c + i] == pieza for i in range(4)):
                return True

    # diagonales \
    for r in range(FILAS - 3):
        for c in range(COLUMNAS - 3):
            if all(tablero[r + i][c + i] == pieza for i in range(4)):
                return True

    return False


def puntaje_ventana(ventana, pieza):
    puntaje = 0
    oponente = PLAYER_PIECE if pieza == AI_PIECE else AI_PIECE

    if ventana.count(pieza) == 4:
        puntaje += 100
    elif ventana.count(pieza) == 3 and ventana.count(EMPTY) == 1:
        puntaje += 5
    elif ventana.count(pieza) == 2 and ventana.count(EMPTY) == 2:
        puntaje += 2

    if ventana.count(oponente) == 3 and ventana.count(EMPTY) == 1:
        puntaje -= 4

    return puntaje


def puntaje_posicion(tablero, pieza):
    puntaje = 0

    centro = COLUMNAS // 2
    centro_array = [tablero[r][centro] for r in range(FILAS)]
    puntaje += centro_array.count(pieza) * 3

    # horizontales
    for r in range(FILAS):
        fila_array = tablero[r]
        for c in range(COLUMNAS - 3):
            ventana = fila_array[c:c + VENTANA]
            puntaje += puntaje_ventana(ventana, pieza)

    # verticales
    for c in range(COLUMNAS):
        col_array = [tablero[r][c] for r in range(FILAS)]
        for r in range(FILAS - 3):
            ventana = col_array[r:r + VENTANA]
            puntaje += puntaje_ventana(ventana, pieza)

    # diagonales \
    for r in range(FILAS - 3):
        for c in range(COLUMNAS - 3):
            ventana = [tablero[r + i][c + i] for i in range(VENTANA)]
            puntaje += puntaje_ventana(ventana, pieza)

    # diagonales /
    for r in range(3, FILAS):
        for c in range(COLUMNAS - 3):
            ventana = [tablero[r - i][c + i] for i in range(VENTANA)]
            puntaje += puntaje_ventana(ventana, pieza)

    return puntaje


def es_terminal(tablero):
    return revisar_ganador(tablero, PLAYER_PIECE) or revisar_ganador(tablero, AI_PIECE) or es_empate(tablero)


def minimax(tablero, profundidad, alpha, beta, maximizando):
    if profundidad == 0 or es_terminal(tablero):
        if revisar_ganador(tablero, AI_PIECE):
            return (None, 1000000000)
        elif revisar_ganador(tablero, PLAYER_PIECE):
            return (None, -1000000000)
        else:
            return (None, puntaje_posicion(tablero, AI_PIECE))

    movs = movimientos_validos(tablero)

    if maximizando:
        mejor_puntaje = -math.inf
        mejor_col = random.choice(movs)

        for col in movs:
            temp = deepcopy(tablero)
            fila = obtener_fila_libre(temp, col)
            poner_ficha(temp, fila, col, AI_PIECE)
            _, punt = minimax(temp, profundidad - 1, alpha, beta, False)

            if punt > mejor_puntaje:
                mejor_puntaje = punt
                mejor_col = col

            alpha = max(alpha, punt)
            if alpha >= beta:
                break

        return mejor_col, mejor_puntaje

    else:
        mejor_puntaje = math.inf
        mejor_col = random.choice(movs)

        for col in movs:
            temp = deepcopy(tablero)
            fila = obtener_fila_libre(temp, col)
            poner_ficha(temp, fila, col, PLAYER_PIECE)
            _, punt = minimax(temp, profundidad - 1, alpha, beta, True)

            if punt < mejor_puntaje:
                mejor_puntaje = punt
                mejor_col = col

            beta = min(beta, punt)
            if alpha >= beta:
                break

        return mejor_col, mejor_puntaje


def jugar_dos():
    tablero = crear_tablero()
    turno = 0

    while True:
        imprimir_tablero(tablero)

        col = input("Jugador {} elija columna (1-7): ".format(1 if turno == 0 else 2))
        if not col.isdigit() or not (1 <= int(col) <= 7):
            print("Entrada inválida.")
            continue

        col = int(col) - 1

        if not columna_valida(tablero, col):
            print("Columna llena.")
            continue

        fila = obtener_fila_libre(tablero, col)
        pieza = PLAYER_PIECE if turno == 0 else AI_PIECE
        poner_ficha(tablero, fila, col, pieza)

        if revisar_ganador(tablero, pieza):
            imprimir_tablero(tablero)
            print("Ganó el jugador {}".format(1 if turno == 0 else 2))
            break

        if es_empate(tablero):
            imprimir_tablero(tablero)
            print("Empate.")
            break

        turno ^= 1


def jugar_contra_ia():
    tablero = crear_tablero()
    turno = 0

    while True:
        imprimir_tablero(tablero)

        if turno == 0:
            col = input("Tu turno. Elija columna (1-7): ")

            if not col.isdigit() or not (1 <= int(col) <= 7):
                print("Entrada inválida.")
                continue

            col = int(col) - 1

            if not columna_valida(tablero, col):
                print("Columna llena.")
                continue

            fila = obtener_fila_libre(tablero, col)
            poner_ficha(tablero, fila, col, PLAYER_PIECE)

            if revisar_ganador(tablero, PLAYER_PIECE):
                imprimir_tablero(tablero)
                print("Ganaste.")
                break

        else:
            print("Turno de la IA.")
            col, _ = minimax(tablero, 5, -math.inf, math.inf, True)

            fila = obtener_fila_libre(tablero, col)
            poner_ficha(tablero, fila, col, AI_PIECE)

            if revisar_ganador(tablero, AI_PIECE):
                imprimir_tablero(tablero)
                print("La IA ganó.")
                break

        if es_empate(tablero):
            imprimir_tablero(tablero)
            print("Empate.")
            break

        turno ^= 1


def main():
    while True:
        print("\n=== MENU ===")
        print("1. Dos jugadores")
        print("2. Contra IA")
        print("3. Salir")

        opcion = input("Elegir opción: ")

        if opcion == Menu.DOS_JUGADORES.value:
            jugar_dos()

        elif opcion == Menu.CONTRA_IA.value:
            jugar_contra_ia()

        elif opcion == Menu.SALIR.value:
            print("Saliendo...")
            break

        else:
            print("Opción inválida.")


if __name__ == "__main__":
    main()
    
"""
import os
import time
import random
from enum import Enum
from copy import deepcopy

# Constantes del juego
ROW_COUNT = 6
COLUMN_COUNT = 7
WINDOW_LENGTH = 4
EMPTY = 0
PLAYER_PIECE = 1  # X
AI_PIECE = 2      # O

WIN_SCORE = 10_000_000
THREE_SCORE = 100
TWO_SCORE = 10
BLOCK_THREE_PENALTY = 80

# Tiempo entre frames de animación (segundos)
ANIM_DELAY = 0.06

class Menu(Enum):
    DOS_JUGADORES = "1"
    CONTRA_IA = "2"
    SALIR = "3"

# -- Utilidades pantalla/tiempo --
def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")

def sleep_seconds(sec):
    time.sleep(sec)

# -- Tablero y presentación --
def create_board():
    return [[EMPTY for _ in range(COLUMN_COUNT)] for _ in range(ROW_COUNT)]

def symbol(val):
    if val == PLAYER_PIECE:
        return "X"
    elif val == AI_PIECE:
        return "O"
    else:
        return "."

def print_board(board):
    # Header columnas
    print()
    header = "  " + " ".join(str(i+1) for i in range(COLUMN_COUNT))
    print(header)
    # Filas (imprime la fila 0 como arriba, fila ROW_COUNT-1 abajo)
    for r in range(ROW_COUNT):
        row = board[r]
        print("| " + " ".join(symbol(c) for c in row) + " |")
    # Línea inferior
    print("+" + "---" * COLUMN_COUNT + "+")

# -- Reglas básicas --
def is_valid_location(board, col):
    return 0 <= col < COLUMN_COUNT and board[0][col] == EMPTY

def get_next_open_row(board, col):
    for r in range(ROW_COUNT-1, -1, -1):
        if board[r][col] == EMPTY:
            return r
    return None

def drop_piece(board, row, col, piece):
    board[row][col] = piece

def get_valid_locations(board):
    return [c for c in range(COLUMN_COUNT) if is_valid_location(board, c)]

def is_terminal_node(board):
    return winning_move(board, PLAYER_PIECE) or winning_move(board, AI_PIECE) or len(get_valid_locations(board)) == 0

def winning_move(board, piece):
    # Horizontales
    for r in range(ROW_COUNT):
        for c in range(COLUMN_COUNT - 3):
            if all(board[r][c+i] == piece for i in range(WINDOW_LENGTH)):
                return True
    # Verticales
    for c in range(COLUMN_COUNT):
        for r in range(ROW_COUNT - 3):
            if all(board[r+i][c] == piece for i in range(WINDOW_LENGTH)):
                return True
    # Diagonales positivas (\)
    for r in range(ROW_COUNT - 3):
        for c in range(COLUMN_COUNT - 3):
            if all(board[r+i][c+i] == piece for i in range(WINDOW_LENGTH)):
                return True
    # Diagonales negativas (/)
    for r in range(3, ROW_COUNT):
        for c in range(COLUMN_COUNT - 3):
            if all(board[r-i][c+i] == piece for i in range(WINDOW_LENGTH)):
                return True
    return False

def evaluate_window(window, piece):
    score = 0
    opp_piece = PLAYER_PIECE if piece == AI_PIECE else AI_PIECE

    if window.count(piece) == 4:
        score += WIN_SCORE
    elif window.count(piece) == 3 and window.count(EMPTY) == 1:
        score += THREE_SCORE
    elif window.count(piece) == 2 and window.count(EMPTY) == 2:
        score += TWO_SCORE

    if window.count(opp_piece) == 3 and window.count(EMPTY) == 1:
        score -= BLOCK_THREE_PENALTY

    return score

def score_position(board, piece):
    score = 0
    # Preferir columna central
    center_col = COLUMN_COUNT // 2
    center_array = [board[r][center_col] for r in range(ROW_COUNT)]
    center_count = center_array.count(piece)
    score += center_count * 6

    # Horizontales
    for r in range(ROW_COUNT):
        row_array = board[r]
        for c in range(COLUMN_COUNT - 3):
            window = row_array[c:c+WINDOW_LENGTH]
            score += evaluate_window(window, piece)

    # Verticales
    for c in range(COLUMN_COUNT):
        col_array = [board[r][c] for r in range(ROW_COUNT)]
        for r in range(ROW_COUNT - 3):
            window = col_array[r:r+WINDOW_LENGTH]
            score += evaluate_window(window, piece)

    # Diagonales positivas (\)
    for r in range(ROW_COUNT - 3):
        for c in range(COLUMN_COUNT - 3):
            window = [board[r+i][c+i] for i in range(WINDOW_LENGTH)]
            score += evaluate_window(window, piece)

    # Diagonales negativas (/)
    for r in range(ROW_COUNT - 3):
        for c in range(COLUMN_COUNT - 3):
            window = [board[r+3-i][c+i] for i in range(WINDOW_LENGTH)]
            score += evaluate_window(window, piece)

    return score

def minimax(board, depth, alpha, beta, maximizingPlayer):
    valid_locations = get_valid_locations(board)
    is_terminal = is_terminal_node(board)
    if depth == 0 or is_terminal:
        if is_terminal:
            if winning_move(board, AI_PIECE):
                return (None, WIN_SCORE)
            elif winning_move(board, PLAYER_PIECE):
                return (None, -WIN_SCORE)
            else:  # empate
                return (None, 0)
        else:
            return (None, score_position(board, AI_PIECE))

    if maximizingPlayer:
        value = -float('inf')
        best_col = random.choice(valid_locations) if valid_locations else None
        for col in valid_locations:
            row = get_next_open_row(board, col)
            if row is None:
                continue
            b_copy = deepcopy(board)
            drop_piece(b_copy, row, col, AI_PIECE)
            new_score = minimax(b_copy, depth-1, alpha, beta, False)[1]
            if new_score > value:
                value = new_score
                best_col = col
            alpha = max(alpha, value)
            if alpha >= beta:
                break
        return best_col, value
    else:
        value = float('inf')
        best_col = random.choice(valid_locations) if valid_locations else None
        for col in valid_locations:
            row = get_next_open_row(board, col)
            if row is None:
                continue
            b_copy = deepcopy(board)
            drop_piece(b_copy, row, col, PLAYER_PIECE)
            new_score = minimax(b_copy, depth-1, alpha, beta, True)[1]
            if new_score < value:
                value = new_score
                best_col = col
            beta = min(beta, value)
            if alpha >= beta:
                break
        return best_col, value

def pick_best_move(board, piece):
    valid_locations = get_valid_locations(board)
    best_score = -float('inf')
    best_col = random.choice(valid_locations) if valid_locations else None
    for col in valid_locations:
        row = get_next_open_row(board, col)
        if row is None:
            continue
        temp_board = deepcopy(board)
        drop_piece(temp_board, row, col, piece)
        score = score_position(temp_board, piece)
        if score > best_score:
            best_score = score
            best_col = col
    return best_col

# -- Animación de caída --
def animate_drop(board, col, piece, delay=ANIM_DELAY):
    final_row = get_next_open_row(board, col)
    if final_row is None:
        return None
    # Animar desde la fila 0 hasta final_row
    for r in range(0, final_row + 1):
        temp = deepcopy(board)
        temp[r][col] = piece
        clear_screen()
        print_board(temp)
        sleep_seconds(delay)
    # Al final colocar en el tablero real
    drop_piece(board, final_row, col, piece)
    return final_row

# -- Entrada del jugador --
def player_move(board):
    while True:
        entrada = input(f"Elige columna (1-{COLUMN_COUNT}): ").strip()
        if not entrada.isdigit():
            print("Debes ingresar un numero.")
            continue
        col = int(entrada) - 1
        if col < 0 or col >= COLUMN_COUNT:
            print("Columna fuera de rango.")
            continue
        if not is_valid_location(board, col):
            print("Columna llena. Elegi otra.")
            continue
        return col

# -- Partida 1 vs 1 --
def play_two_players():
    board = create_board()
    turn = 0  # 0 -> Jugador 1 (X), 1 -> Jugador 2 (O)
    while True:
        clear_screen()
        print_board(board)
        print(f"Turno: Jugador {1 if turn==0 else 2} ({'X' if turn==0 else 'O'})")
        col = player_move(board)
        row = animate_drop(board, col, PLAYER_PIECE if turn==0 else AI_PIECE)
        if row is None:
            print("Error al colocar ficha.")
            continue
        # revisar ganador
        pieza = PLAYER_PIECE if turn==0 else AI_PIECE
        if winning_move(board, pieza):
            clear_screen()
            print_board(board)
            print(f"Gano el jugador {1 if turn==0 else 2}.")
            break
        if len(get_valid_locations(board)) == 0:
            clear_screen()
            print_board(board)
            print("Empate.")
            break
        turn ^= 1

# -- Partida vs IA --
def play_vs_ai(ai_depth):
    board = create_board()
    turn = 0  # 0 -> humano (X), 1 -> IA (O)
    while True:
        clear_screen()
        print_board(board)
        if turn == 0:
            print("Tu turno (X)")
            col = player_move(board)
            row = animate_drop(board, col, PLAYER_PIECE)
            if row is None:
                print("Error al colocar ficha.")
                continue
            if winning_move(board, PLAYER_PIECE):
                clear_screen()
                print_board(board)
                print("Has ganado.")
                break
        else:
            print("Turno de la IA (O). Pensando...")
            # intentar minimax; si devuelve None, fallback a heurística
            col, score = minimax(board, ai_depth, -float('inf'), float('inf'), True)
            if col is None or not is_valid_location(board, col):
                col = pick_best_move(board, AI_PIECE)
            # breve pausa antes de animar
            sleep_seconds(0.3)
            row = animate_drop(board, col, AI_PIECE)
            if row is None:
                # si algo falla, saltar
                print("IA no pudo colocar ficha.")
            if winning_move(board, AI_PIECE):
                clear_screen()
                print_board(board)
                print("La IA gano.")
                break
        if len(get_valid_locations(board)) == 0:
            clear_screen()
            print_board(board)
            print("Empate.")
            break
        turn ^= 1

# -- Menú principal --
def main():
    random.seed()
    while True:
        print("\n= = = CONECTA 4 = = =")
        print(f"{Menu.DOS_JUGADORES.value}. 2 Jugadores")
        print(f"{Menu.CONTRA_IA.value}. Contra IA")
        print(f"{Menu.SALIR.value}. Salir")
        opcion = input("Elegi una opcion: ").strip()
        if opcion == Menu.DOS_JUGADORES.value:
            play_two_players()
        elif opcion == Menu.CONTRA_IA.value:
            profundidad = 4
            d = input("Elegi dificultad IA (1-6, recomendado 4): ").strip()
            if d.isdigit():
                profundidad = max(1, min(6, int(d)))
            play_vs_ai(profundidad)
        elif opcion == Menu.SALIR.value:
            print("Saliendo...")
            break
        else:
            print("Opcion no valida. Intenta de nuevo.")

if __name__ == "__main__":
    main()
