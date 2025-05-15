#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_CARTAS 52
#define MANO_JUGADOR 2
#define CARTAS_MESA 5
#define MAX_CARTAS_COMBINADAS 7
#define FICHAS_INICIALES 5000

const char* nombres_valores[] = {"", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const char* nombres_palos[] = {"Corazones", "Diamantes", "Tréboles", "Picas"};
const char* simbolos_palos[] = {"♥", "♦", "♣", "♠"};
const char* colores_palos[] = {"\033[31m", "\033[31m", "\033[30m", "\033[30m"};

const char* RESET_COLOR = "\033[0m";

typedef struct {
    int valor;
    int palo;
} Carta;

typedef struct {
    Carta cartas[MAX_CARTAS_COMBINADAS];
    int categoria;
    int valor_alto;
} ManoEvaluada;

void crearBaraja(Carta* baraja) {
    int i = 0;
    for (int valor = 2; valor <= 14; valor++) {
        for (int palo = 0; palo < 4; palo++) {
            baraja[i].valor = valor;
            baraja[i].palo = palo;
            i++;
        }
    }
}

void mezclarBaraja(Carta* baraja) {
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        Carta temp = baraja[i];
        baraja[i] = baraja[j];
        baraja[j] = temp;
    }
}

void mostrarCarta(Carta c) {
    printf("%s%s%s%s de %s",
           colores_palos[c.palo],
           nombres_valores[c.valor],
           simbolos_palos[c.palo],
           RESET_COLOR,
           nombres_palos[c.palo]);
}

void mostrarCartas(Carta* cartas, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("  ");
        mostrarCarta(cartas[i]);
        printf("\n");
    }
}

int compararCartas(const void* a, const void* b) {
    return ((Carta*)b)->valor - ((Carta*)a)->valor;
}

void copiarCartas(Carta* destino, Carta* mano, Carta* mesa, int cant_mano, int cant_mesa) {
    for (int i = 0; i < cant_mano; i++) destino[i] = mano[i];
    for (int i = 0; i < cant_mesa; i++) destino[cant_mano + i] = mesa[i];
}

int contarValores(Carta* cartas, int cantidad, int* conteo) {
    for (int i = 0; i < 15; i++) conteo[i] = 0;
    for (int i = 0; i < cantidad; i++) conteo[cartas[i].valor]++;
    return 0;
}

int esColor(Carta* cartas, int cantidad) {
    int palos[4] = {0};
    for (int i = 0; i < cantidad; i++) palos[cartas[i].palo]++;
    for (int i = 0; i < 4; i++) if (palos[i] >= 5) return 1;
    return 0;
}

int esEscalera(Carta* cartas, int cantidad) {
    int valores[15] = {0};
    for (int i = 0; i < cantidad; i++) valores[cartas[i].valor] = 1;
    for (int i = 14; i >= 5; i--) {
        if (valores[i] && valores[i-1] && valores[i-2] && valores[i-3] && valores[i-4])
            return 1;
    }
    return (valores[14] && valores[2] && valores[3] && valores[4] && valores[5]);
}

void evaluarMano(Carta* cartas, int cantidad, ManoEvaluada* resultado) {
    qsort(cartas, cantidad, sizeof(Carta), compararCartas);

    int conteo[15] = {0};
    contarValores(cartas, cantidad, conteo);

    int pares = 0, trio = 0, poker = 0;
    for (int i = 2; i <= 14; i++) {
        if (conteo[i] == 2) pares++;
        if (conteo[i] == 3) trio = i;
        if (conteo[i] == 4) poker = i;
    }

    int color = esColor(cartas, cantidad);
    int escalera = esEscalera(cartas, cantidad);

    if (escalera && color) {
        resultado->categoria = 8;
    } else if (poker) {
        resultado->categoria = 7;
        resultado->valor_alto = poker;
    } else if (trio && pares) {
        resultado->categoria = 6;
        resultado->valor_alto = trio;
    } else if (color) {
        resultado->categoria = 5;
    } else if (escalera) {
        resultado->categoria = 4;
    } else if (trio) {
        resultado->categoria = 3;
        resultado->valor_alto = trio;
    } else if (pares == 2) {
        resultado->categoria = 2;
    } else if (pares == 1) {
        resultado->categoria = 1;
    } else {
        resultado->categoria = 0;
        resultado->valor_alto = cartas[0].valor;
    }
}

const char* nombreCategoria(int cat) {
    const char* nombres[] = {
        "Carta alta", "Pareja", "Doble pareja", "Trío", "Escalera",
        "Color", "Full", "Póker", "Escalera de color"
    };
    return nombres[cat];
}

int apuestaComputadora(int fichas_computadora, int ronda) {
    if (ronda == 0) return 100;
    if (ronda == 1) return 200;
    if (ronda == 2) return 300;
    return 400;
}

int main() {
    srand(time(NULL));
    int fichas_jugador = FICHAS_INICIALES;
    int fichas_computadora = FICHAS_INICIALES;
    char seguir;

    do {
        if (fichas_jugador <= 0) {
            printf("\nTe quedaste sin fichas. ¡Perdiste!\n");
            break;
        }

        Carta baraja[TOTAL_CARTAS];
        crearBaraja(baraja);
        mezclarBaraja(baraja);

        Carta mano_jugador[2] = {baraja[0], baraja[1]};
        Carta mano_computadora[2] = {baraja[2], baraja[3]};
        Carta mesa[5] = {baraja[4], baraja[5], baraja[6], baraja[7], baraja[8]};

        int cartas_mostradas = 0;
        int ronda = 0;
        int pot = 0;
        int retiro = 0;
        int apuesta_actual = 0;

        printf("\nTus cartas:\n");
        mostrarCartas(mano_jugador, 2);

        while (cartas_mostradas < 5) {
            int apuesta_jugador = -1;
            int apuesta_cpu = apuestaComputadora(fichas_computadora, ronda);

            printf("\nCartas en la mesa:\n");
            mostrarCartas(mesa, cartas_mostradas);

            while (apuesta_jugador < 0 || apuesta_jugador < apuesta_actual) {
                printf("\nTenés %d fichas. (Apuesta actual: %d).\n", fichas_jugador, apuesta_actual);
                printf("Escribí tu apuesta (igualar o subir). Escribí 0 para hacer check (si se puede), o -1 para retirarte: ");
                scanf("%d", &apuesta_jugador);

                if (apuesta_jugador == -1) {
                    printf("Te retiraste.\n");
                    retiro = 1;
                    break;
                } else if (apuesta_jugador == 0 && apuesta_actual > 0) {
                    printf("No podés hacer check, la computadora ya apostó.\n");
                    apuesta_jugador = -1;
                }
            }

            if (retiro) break;

            if (apuesta_actual == 0 && apuesta_cpu > 0) {
                printf("La computadora apuesta %d fichas.\n", apuesta_cpu);
                apuesta_actual = apuesta_cpu;
                printf("¿Querés igualar la apuesta de %d? (1 = sí, 0 = no): ");
                int decision;
                scanf("%d", &decision);
                if (!decision) {
                    printf("Te retiraste.\n");
                    retiro = 1;
                    break;
                } else {
                    apuesta_jugador = apuesta_actual;
                }
            }

            fichas_jugador -= apuesta_jugador;
            fichas_computadora -= apuesta_cpu;
            pot += apuesta_jugador + apuesta_cpu;

            if (cartas_mostradas == 0) cartas_mostradas = 3;
            else cartas_mostradas++;

            ronda++;
        }

        printf("\n--- FIN DE MANO ---\n");
        printf("\nTus cartas:\n");
        mostrarCartas(mano_jugador, 2);
        printf("\nCartas de la computadora:\n");
        mostrarCartas(mano_computadora, 2);
        printf("\nCartas en la mesa:\n");
        mostrarCartas(mesa, 5);

        if (!retiro) {
            Carta combinadas_jugador[7];
            Carta combinadas_computadora[7];

            copiarCartas(combinadas_jugador, mano_jugador, mesa, 2, 5);
            copiarCartas(combinadas_computadora, mano_computadora, mesa, 2, 5);

            ManoEvaluada eval_jugador;
            ManoEvaluada eval_cpu;

            evaluarMano(combinadas_jugador, 7, &eval_jugador);
            evaluarMano(combinadas_computadora, 7, &eval_cpu);

            printf("\nTu jugada: %s\n", nombreCategoria(eval_jugador.categoria));
            printf("Jugada de la computadora: %s\n", nombreCategoria(eval_cpu.categoria));

            if (eval_jugador.categoria > eval_cpu.categoria) {
                printf("\n\033[32m¡Ganaste la mano!\033[0m Te llevás el pozo de %d fichas.\n", pot);
                fichas_jugador += pot;
            } else if (eval_cpu.categoria > eval_jugador.categoria) {
                printf("\n\033[31mLa computadora gana la mano.\033[0m\n");
                fichas_computadora += pot;
            } else {
                printf("\n¡Empate! Se reparten las fichas.\n");
                fichas_jugador += pot / 2;
                fichas_computadora += pot / 2;
            }
        } else {
            printf("\nLa computadora se lleva el pozo de %d fichas.\n", pot);
            fichas_computadora += pot;
        }

        printf("\nTus fichas: %d\n", fichas_jugador);
        printf("Fichas de la computadora: %d\n", fichas_computadora);

        printf("\n¿Querés jugar otra mano? (s/n): ");
        scanf(" %c", &seguir);

    } while (seguir == 's' || seguir == 'S');

    printf("\n¡Gracias por jugar!\n");
    return 0;
}
