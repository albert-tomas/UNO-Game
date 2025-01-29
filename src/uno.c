#include "partida.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
TPartida g;
int num;
g.Ganador = 0;
g.Sentido = 0;
InicializarPartida(&g);
RepartirCartasJugadores(&g,&g);
    while(g.Ganador!=1)
    {
        MostrarTurno(&g);
        MostrarBaraja(&g,&g);
        MostrarDescartes(g,&g);
        MostrarSentido(g.Sentido);
        MostrarCartasJugador(g,g,&g);
        num=Jugadas(g,&g,&g);
        if(g.Plays.NumeroDeJugadas==0) num=SinJugada(&g);
        if(num!=-1)
        {
            printf("Tira: ");
            g.Descarte = CartaJugada(num,&g);
            Acciones(&g);
            printf("\n");
        }
        else 
        {
            printf("\tHa pasado.\n");
            g.TurnoJugador= AvanzarTurno(g.TurnoJugador,g.Jugadores.NumeroDeJugadores,g.Sentido);
            g.TurnoGlobal++;
        }
        ComprobarBaraja(&g);
        ComprobarManos(&g);
        printf("Press RETURN to continue ==>");
        scanf("%*c");
    }
printf("===>>> FIN PARTIDA <<<===\n");
g.TurnoGlobal--;
g.Mode = 1;
        MostrarTurno(&g);
        MostrarBaraja(&g,&g);
        MostrarDescartes(g,&g);
        MostrarSentido(g.Sentido);
        MostrarCartasJugador(g,g,&g);
printf("\n");        
printf("===>>> HA GANADO %s ¡FELICIDADES! <<<===\n",g.Jugadores.Players[g.JugadorGanador].Nombre);
}

