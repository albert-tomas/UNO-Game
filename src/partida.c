#include "partida.h"
#include <stdio.h>
#include <stdlib.h>
#include "colores.h"
#include <time.h>
/*
 * Muestra el turno de la partida.
*/
void MostrarTurno(TPartida *p)
{
    printf("Turno actual: %d\n",p->TurnoGlobal);
}
/*
 * Funcion con la que se inicializa la partida, se definen ciertos parametros, se inician los diferentes mazos...
*/
void InicializarPartida(TPartida *p)
{
char b,c;
TCarta x;
c='n';
srand(time(NULL));
p->Mode=3;
	CrearCartas(&p->Baraja);
	MezclarCartas(&p->Baraja);
	EscogerJugadores(&p->Jugadores);
        InicializarJugador(&p->Jugadores);
        do{
            printf("Quieres ejecutar en modo COMPROBACION? [s/n]: ");
            scanf("%c%*c",&b);
            if(b == 's') p->Mode = 1;
            if(b == 'n') p->Mode = 0;
        }while(p->Mode!=0 && p->Mode!=1);

	x = EliminarCarta(0,&p->Baraja);
	p->MazoDescartes.NumeroDeCartas = 0;
	AnadirCarta(x,&p->MazoDescartes);
        p->Descarte=p->MazoDescartes.Cartas[0];
p->TurnoGlobal = 1;
p->TurnoJugador = rand()%p->Jugadores.NumeroDeJugadores;
}//FIN FUNCION
/*
 * Muestra descartes.
*/
void MostrarDescartes(TPartida mode,TPartida *p)
{
	MostrarCartaDescartes(mode.Mode,&p->MazoDescartes,p->Descarte);
}//FIN FUNCION
/*
 * Muestra la baraja.
*/
void MostrarBaraja(TPartida *mode,TPartida *p)
{
	MostrarCartasMazo(&mode->Mode,&p->Baraja);
}//FIN FUNCION
/*
 * Reparte las cartas a los jugadores, de la baraja al inicio de la partida, una a cada jugador durante siete veces.
*/
void RepartirCartasJugadores(TPartida *ma,TPartida *jugs)
{
int i,j,k,numm,numjugadores;
numjugadores = jugs->Jugadores.NumeroDeJugadores;
numm = ma->Baraja.NumeroDeCartas - 1;

for(i=0;i<numjugadores;i++)
{
jugs->Jugadores.Players[i].Mano.NumeroDeCartas = 0;
jugs->Jugadores.Players[i].NumeroDeTurno = i;
}

for(j=0;j<7;j++)
{
	for(i=0;i < numjugadores ;i++)
	{
		jugs->Jugadores.Players[i].Mano.Cartas[j] = ma->Baraja.Cartas[0];
		jugs->Jugadores.Players[i].Mano.NumeroDeCartas++;
		for(k=0;k<numm;k++)
		{
		ma->Baraja.Cartas[k] = ma->Baraja.Cartas[k+1];
		}
		numm--;
	}
}
ma->Baraja.NumeroDeCartas = numm+1;
}
/*
 * Muestra las cartas de los jugadores dependiendo del modo de juego, las cartas normales en comprobacion y un uno en modo normal, excepto el jugador.
*/
void MostrarCartasJugador(TPartida mode,TPartida turno,TPartida *jugs)
{	
int i,j;

if(mode.Mode == 0)//MODO PLAY
{	
    printf("\n");
		printf("%s:\n",mode.Jugadores.Players[0].Nombre);
               if(mode.Jugadores.Players[0].Mano.NumeroDeCartas >0) printf("|");
		for(i=0; i < jugs->Jugadores.Players[0].Mano.NumeroDeCartas ;i++)
		{
                    cambiar_color_letra(WHITE);
			switch(jugs->Jugadores.Players[0].Mano.Cartas[i].Color)
			{
			case 1: cambiar_color_fondo(YELLOW);
				break;
			case 2:	cambiar_color_fondo(RED);
				break;
			case 3:	cambiar_color_fondo(GREEN);
				break;
			case 4: cambiar_color_fondo(BLUE);
				break;
			case 5:	cambiar_color_fondo(WHITE);
				cambiar_color_letra(BLACK);
				break;
			}
			switch(jugs->Jugadores.Players[0].Mano.Cartas[i].Valor)
			{
			default:printf(" %d ",jugs->Jugadores.Players[0].Mano.Cartas[i].Valor);
				break;
			case 10:printf("+2 ");
				break;
			case 11:printf(" R ");
				break;
			case 12:printf(" S ");
				break;
			case 13:printf(" W ");
				break;
			case 14:printf("W+4");
				break;
			} default_attributes();
			printf("|");
			default_attributes();
                Uno(mode.Jugadores.Players[0].Mano);        
		}
	printf("\n");	
        for(i=1;i<mode.Jugadores.NumeroDeJugadores;i++)
        { 
            printf("%s\n",mode.Jugadores.Players[i].Nombre);
            if(mode.Jugadores.Players[i].Mano.NumeroDeCartas >0) printf("|");
            for(j=0;j<jugs->Jugadores.Players[i].Mano.NumeroDeCartas;j++)
            {
                
                cambiar_color_fondo(WHITE);
                cambiar_color_letra(RED);
                printf("UNO");
                default_attributes();
                
                printf("|");
            }
            Uno(mode.Jugadores.Players[i].Mano);   
            printf("\n");
            
        }
}
else//MODO TEST
{
printf("\n");
for(j=0;j<jugs->Jugadores.NumeroDeJugadores;j++)
{
    printf("%s:\n",mode.Jugadores.Players[j].Nombre);
if(mode.Jugadores.Players[j].Mano.NumeroDeCartas >0) printf("|");
    for(i=0; i < jugs->Jugadores.Players[j].Mano.NumeroDeCartas ;i++)
    {
    cambiar_color_letra(WHITE);
		switch(jugs->Jugadores.Players[j].Mano.Cartas[i].Color)
		{
		case 1: cambiar_color_fondo(YELLOW);
			break;
		case 2:	cambiar_color_fondo(RED);
			break;
		case 3:	cambiar_color_fondo(GREEN);
			break;
		case 4: cambiar_color_fondo(BLUE);
			break;
		case 5:	cambiar_color_fondo(WHITE);
			cambiar_color_letra(BLACK);
			break;
		}

		switch(jugs->Jugadores.Players[j].Mano.Cartas[i].Valor)
		{
		default:printf(" %d ",jugs->Jugadores.Players[j].Mano.Cartas[i].Valor);
			break;
		case 10:printf("+2 ");
			break;
		case 11:printf(" R ");
			break;
		case 12:printf(" S ");
			break;
		case 13:printf(" W ");
			break;
		case 14:printf("W+4");
			break;
		} default_attributes();
		printf("|");
        default_attributes();
        
    }
Uno(turno.Jugadores.Players[j].Mano); 
printf("\n");
}
}
}
/*
 * Se le dan la baraja y la carta descartes y a partir de eso se calcula la jugada, y dependiendo del turno, se muestran o no, y despues se escoge la jugada.
*/
int Jugadas(TPartida turno, TPartida *jugturno, TPartida *md)
{
    TJugadas x;
    int c;
	x = CalcularJugada(&jugturno->Jugadores.Players[turno.TurnoJugador], md->Descarte);
        jugturno->Plays = x;
        if(turno.Mode==1)
        {
            cambiar_color_letra(RED);
            printf("\nTurno %s, ",jugturno->Jugadores.Players[turno.TurnoJugador].Nombre);
            default_attributes();
            if(jugturno->Plays.NumeroDeJugadas==0)  printf("Coge del mazo: ");
            else  
            {
                printf("Jugadas posibles: ");
                MostrarJugadas(&jugturno->Plays);
            }
        }
        else 
        {
            cambiar_color_letra(RED);
            printf("\nTurno %s, ",jugturno->Jugadores.Players[turno.TurnoJugador].Nombre);
            default_attributes();
            if(turno.TurnoJugador==jugturno->Jugadores.Players[0].NumeroDeTurno)
            {
                
                if(jugturno->Plays.NumeroDeJugadas==0)  printf("Coge del mazo: ");
                else 
                {
                printf("Jugadas posibles: ");
                MostrarJugadas(&jugturno->Plays);
                }
                printf("    ");
            }
            else
            {
                if(jugturno->Plays.NumeroDeJugadas==0) printf("Coge del mazo. ");
                
            }
        }
	if(jugturno->Plays.NumeroDeJugadas>=1) c = EscogerJugada(turno.TurnoJugador,turno.Jugadores, jugturno->Plays);
        
        default_attributes();
        return(c);
}
/*
 * Comprueba la cantidad de cartas en la baraja.
*/
void ComprobarBaraja(TPartida *game)
{
    BarajaVacia(&game->Baraja,&game->MazoDescartes);
}
/*
 * Elimina la carta de la mano elegida, la muestra, comprueba si es la ultima y despues la añade al mazo descartes.
*/
TCarta CartaJugada(int num,TPartida *game)
{
    TCarta x;
    x = EliminarCarta(num, &game->Jugadores.Players[game->TurnoJugador].Mano);
    MostrarCarta(x);
    Uno(game->Jugadores.Players[game->TurnoJugador].Mano);   
    AnadirCartaDescartes(x,&game->MazoDescartes);
    return(x);
}
/*
 * Aqui se calcula que acciones se deven tomar en funcion de la carta que ha llegado al mazo descartes.
*/
void Acciones(TPartida *game)
{
    int i;
    TCarta x;
    switch(game->Descarte.Valor)
    {
        case 10:
            game->TurnoJugador = AvanzarTurno(game->TurnoJugador,game->Jugadores.NumeroDeJugadores,game->Sentido);
            for(i=0;i<2;i++)
            {
                BarajaVacia(&game->Baraja,&game->MazoDescartes);
                x = EliminarCarta(0,&game->Baraja);
                AnadirCarta(x,&game->Jugadores.Players[game->TurnoJugador].Mano);
            }
            game->TurnoJugador = AvanzarTurno(game->TurnoJugador,game->Jugadores.NumeroDeJugadores,game->Sentido);
            break;
        case 11:
            game->Sentido = CambiarSentido(game->Sentido);
            game->TurnoJugador = AvanzarTurno(game->TurnoJugador,game->Jugadores.NumeroDeJugadores,game->Sentido);
            break;
        case 12:
            for(i=0;i<2;i++)
            {
                game->TurnoJugador = AvanzarTurno(game->TurnoJugador,game->Jugadores.NumeroDeJugadores,game->Sentido);
            }
            break;
        case 13:
            game->Descarte.Color = CambiarColor(game->TurnoJugador,game->Jugadores.NumeroDeJugadores);
            game->TurnoJugador = AvanzarTurno(game->TurnoJugador,game->Jugadores.NumeroDeJugadores,game->Sentido);
            break;
        case 14:
            game->Descarte.Color = CambiarColor(game->TurnoJugador,game->Jugadores.NumeroDeJugadores);
            game->TurnoJugador = AvanzarTurno(game->TurnoJugador,game->Jugadores.NumeroDeJugadores,game->Sentido);
            for(i=0;i<4;i++)
            {
                BarajaVacia(&game->Baraja,&game->MazoDescartes);
                x = EliminarCarta(0,&game->Baraja);
                AnadirCarta(x,&game->Jugadores.Players[game->TurnoJugador].Mano);
            }
            game->TurnoJugador = AvanzarTurno(game->TurnoJugador,game->Jugadores.NumeroDeJugadores,game->Sentido);
            break;
        default:    
            game->TurnoJugador = AvanzarTurno(game->TurnoJugador,game->Jugadores.NumeroDeJugadores,game->Sentido);
            break;
    }
                game->TurnoGlobal++;
}
/*
 * Cuando el jugador no tiene jugada, se elimina la carta del mazo y despues se muestra dependiendo del modo la carta o un uno.
 * Despues con esta carta misma se calcula si es posible ser jugada o no y de ser posible se juega inmediatamente, poniendola en el mazo descartes. 
*/
int SinJugada(TPartida *game)
{
    int num;
    TCarta x;
    TJugadas j;
    x= EliminarCarta(0,&game->Baraja);
    if(game->Mode == 1) MostrarCarta(x);
    else if(game->TurnoJugador == 0) MostrarCarta(x);
    else MostrarUno();
    printf("    ");
    AnadirCarta(x,&game->Jugadores.Players[game->TurnoJugador].Mano);
    j = CalcularJugada(&game->Jugadores.Players[game->TurnoJugador], game->Descarte);
    num = game->Jugadores.Players[game->TurnoJugador].Mano.NumeroDeCartas-1;
    if(j.NumeroDeJugadas < 1)  num = -1;
    return(num);
}
/*
 * Comprueba las manos y modifica el parametro del ganador, si un jugador se queda con 0 cartas.
*/
void ComprobarManos(TPartida *game)
{
    int i;
    for(i=0;i<game->Jugadores.NumeroDeJugadores;i++)
    {
        if(game->Jugadores.Players[i].Mano.NumeroDeCartas == 0) 
        {
            game->Ganador = 1;
            game->JugadorGanador = i;
        }
     
    }
}





