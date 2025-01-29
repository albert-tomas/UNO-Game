#include <stdio.h>
#include <stdlib.h>
#include "colores.h"
#include <time.h>
#include "players.h"
/*
 * Se escoge la cantidad de jugadores, que habra en la partida, de 3 a 5 siendo uno un jugador siempre y los otros con opciones aleatorias.
*/
void EscogerJugadores(TJugadores *jugs)
{
int num;
	printf("Introduzca cantidad de jugadores(3-5): ");	
		scanf("%d%*c",&num);
	
	while(num < 3 || num > 5)
	{
		printf("Cantidad incorrecta, introduzque otra vez: ");
		scanf("%d%*c",&num);
	}
jugs->NumeroDeJugadores = num;
}
/*
 * Calcula las jugadas posibles del jugador que se le entrega y se devuelven esas jugadas.
*/
TJugadas CalcularJugada(TJugador *plturno, TCarta cartad)
{
  TJugadas poss;
  poss.NumeroDeJugadas=0;
  int i=0;
  int j=0;
  int col=0;
  poss.PosiblesJugadas.NumeroDeCartas=0;
  
  for(i=0; i< plturno->Mano.NumeroDeCartas; i++)
  {
    if(plturno->Mano.Cartas[i].Valor == 13)
    {
        poss.PosiblesJugadas.Cartas[j]= plturno->Mano.Cartas[i];
        poss.PosicionCarta[j] = i;
        poss.PosiblesJugadas.NumeroDeCartas++;
        j++;
        poss.NumeroDeJugadas++;   
    }
    else if((plturno->Mano.Cartas[i].Valor == cartad.Valor || plturno->Mano.Cartas[i].Color == cartad.Color) && (plturno->Mano.Cartas[i].Valor!=14 && plturno->Mano.Cartas[i].Valor!=13))
    {
	poss.PosiblesJugadas.Cartas[j]= plturno->Mano.Cartas[i];
        poss.PosicionCarta[j] = i;
        poss.PosiblesJugadas.NumeroDeCartas++;
        j++;
	poss.NumeroDeJugadas++;
        if(plturno->Mano.Cartas[i].Color == cartad.Color) col++;
		//posicion de la carta en la mano
    }
  }

  if(poss.NumeroDeJugadas == 0 || poss.NumeroDeJugadas > 0 && col==0)
  {
    for(i=0; i< plturno->Mano.NumeroDeCartas; i++)
    {
      if(plturno->Mano.Cartas[i].Valor == 14)
      {
        poss.PosiblesJugadas.Cartas[j] = plturno->Mano.Cartas[i];
        poss.PosiblesJugadas.NumeroDeCartas++;
        poss.NumeroDeJugadas++;
        poss.PosicionCarta[j] = i;
        j++;
      }
    }
  }

  /*if(numjugadas==0)
  {
    //funcion robar_carta
  }*/
  return(poss);
}
/*
 * Muestra las jugadas, dependiendo del modo y del jugador.
*/
void MostrarJugadas(TJugadas *plays)
{
	int i;
        
	for(i=0;i<plays->NumeroDeJugadas;i++)
        {
            printf("%d(|",i);
            cambiar_color_letra(WHITE);
		switch(plays->PosiblesJugadas.Cartas[i].Color)
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

		switch(plays->PosiblesJugadas.Cartas[i].Valor)
		{
		default:printf(" %d ",plays->PosiblesJugadas.Cartas[i].Valor);
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
		printf("|) ");
default_attributes();
        }
printf("       ");	
}	
/*
 * Inicializa los jugadores, se escanea un nombre para el jugador principal y se le asignan nombres a los diferentes robots.
*/
void InicializarJugador(TJugadores *jugadores)
{
	int i=0;
        char x;
        int MAX=15;
	printf("Tu nombre? ");
		scanf("%s%*c", jugadores->Players[i].Nombre);
                jugadores->Players[i].NumeroDeTurno = i;
	jugadores->Players[0].Nombre[15] = '\n';
        for(i=1;i<jugadores->NumeroDeJugadores;i++)
        {
            x='0'+i;
            jugadores->Players[i].Nombre[0]= 'R';
            jugadores->Players[i].Nombre[1]= 'o';
            jugadores->Players[i].Nombre[2]= 'b';
            jugadores->Players[i].Nombre[3]= 'o';
            jugadores->Players[i].Nombre[4]= 't';
            jugadores->Players[i].Nombre[5]= x;
            jugadores->Players[i].Nombre[6]= '\0';
            jugadores->Players[i].NumeroDeTurno = i;
        }
}
/*
 * Se escoge la jugada, siendo aleatoria la de los robots y se escanea la del jugador principal.
*/
int EscogerJugada(int turnojug, TJugadores jugs,TJugadas x)
{
    int num,q;

        if(turnojug == jugs.Players[0].NumeroDeTurno)
        {
            printf("\n");
            do{
                printf("Que carta tiras? [0-%d]:",x.NumeroDeJugadas-1);
                scanf("%d%*c",&q);
            }while(q < 0 || q > x.NumeroDeJugadas-1);
            num= x.PosicionCarta[q];
            //printf("Tira: ");
        }
        else 
        {
            //printf("Tira: ");
            srand(time(NULL));
            if(x.NumeroDeJugadas > 1) num=x.PosicionCarta[rand()%x.NumeroDeJugadas];
            else num=x.PosicionCarta[0];
        }
    return(num);  
}
/*
 * Se avanza el Turno del jugador, dependiendo del sentido.
*/
int AvanzarTurno(int turnojug,int numjugs, int sentido)
{
    int i;
    if(sentido == 0)
    {
        i=turnojug+1;
                if(i==numjugs) i=0;
    }
    else if(sentido == 1)
    {
        i=turnojug-1;
                if(i== -1) i=numjugs-1;
    }
    return(i);
}	
/*
 * Se cambia el parametro del sentido de la partida.
*/
int CambiarSentido(int sentido)
{
	if(sentido == 1) sentido=0;
	else sentido=1;
        return(sentido);
}

	
	
	
