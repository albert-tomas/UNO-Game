#ifndef PARTIDA_H
#define PARTIDA_H
#include "baraja.h"
#include "players.h"

typedef struct{
//int numj;
TBaraja Baraja,MazoDescartes;
TJugadores Jugadores;
int Mode;
int TurnoGlobal;
TCarta Descarte;
TJugadas Plays;
int TurnoJugador;
int Ganador;
int Sentido;
int JugadorGanador;
}TPartida;

void MostrarTurno(TPartida *p);
void InicializarPartida(TPartida *p);
void MostrarBaraja(TPartida *mode,TPartida *p);
void MostrarDescartes(TPartida mode,TPartida *p);
void RepartirCartasJugadores(TPartida *ma,TPartida *jugs);
void MostrarCartasJugador(TPartida mode,TPartida turno,TPartida *jugs);
int Jugadas(TPartida turno, TPartida *jugturno, TPartida *md);
void ComprobarBaraja(TPartida *game);
TCarta CartaJugada(int num,TPartida *game);
void Acciones(TPartida *game);
int SinJugada(TPartida *game);
void ComprobarManos(TPartida *game);
#endif //PARTIDA_H
