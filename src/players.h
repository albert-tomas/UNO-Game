#ifndef PLAYERS_H
#define PLAYERS_H
#include "baraja.h"

#define MAXJUG 5

typedef struct{
TBaraja Mano;
int NumeroDeTurno;
char Nombre[15];
}TJugador;

typedef struct{
TJugador Players[MAXJUG];
int NumeroDeJugadores;
}TJugadores;

typedef struct{
TBaraja PosiblesJugadas;
int NumeroDeJugadas;
int PosicionCarta[BAR];
}TJugadas;

void EscogerJugadores(TJugadores *jugs);
TJugadas CalcularJugada(TJugador *plturno, TCarta cartad);
void MostrarJugadas(TJugadas *plays);
void InicializarJugador(TJugadores *jugadores);
int EscogerJugada(int turnojug, TJugadores jugs, TJugadas x);
int AvanzarTurno(int turnojug, int numjugs, int sentido);
int CambiarSentido(int sentido);
#endif //PLAYERS_H
