#include <stdio.h>
#include <stdlib.h>
#include "colores.h"
#include <time.h>
#include "baraja.h"

/*
 * Crea las cartas de la baraja.
*/
void CrearCartas(TBaraja *ma)
{
int i,j;
for(j=0;j<52;j++)
{
		ma->Cartas[j].Valor = j%13;
		ma->Cartas[j].Color = j/13+1;
}

for(j=0;j<48;j++)
{
	ma->Cartas[j+52].Valor = j%12+1;
	ma->Cartas[j+52].Color = j/12+1;
}
for(j=0;j<8;j++)
{
	ma->Cartas[j+100].Valor = 13+j/4;
	ma->Cartas[j+100].Color = 5;
}
ma->NumeroDeCartas = 108;
}
/*
 * Muestra las cartas de la baraja y dependiendo del modo muestra UNO o muestra todas las cartas de la baraja.
*/
void MostrarCartasMazo(int *mode,TBaraja *ma)
{
    if(*mode == 1)
    {
int i,j;
printf("Baraja:");
printf("\n");
printf("|");
for(i=0;i< ma->NumeroDeCartas;i++)
{
    cambiar_color_letra(WHITE);
		switch(ma->Cartas[i].Color)
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

		switch(ma->Cartas[i].Valor)
		{
		default:printf(" %d ",ma->Cartas[i].Valor);
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
if((i+1)%20==0)
{
	printf("\n ");
	for(j=0;j<20;j++)
	{
	printf("---+");
	}
	printf("\n");
        printf("|");
}
}

printf("\n");
default_attributes();
    }
    else 
    {
        printf("|");
        cambiar_color_fondo(WHITE);
        cambiar_color_letra(RED);
        printf("UNO");
        default_attributes();
        printf("|");
        printf(" (%d) ",ma->NumeroDeCartas);
        printf("\n");
    }
}
/*
 * Mezcla las cartas de la baraja que se le entrega de manera aleatoria.
*/
void MezclarCartas(TBaraja *ma)
{
srand(time(NULL));
int i,j;
TCarta aux;	
do
{
	for(i=0;i < ma->NumeroDeCartas;i++)
	{
		j=rand()%MAXBAR;
		aux = ma->Cartas[i];
		ma->Cartas[i] = ma->Cartas[j];
		ma->Cartas[j] = aux;
	}
}while(ma->Cartas[0].Valor==14 || ma->Cartas[0].Valor==13 || ma->Cartas[0].Valor==12 || ma->Cartas[0].Valor==11 || ma->Cartas[0].Valor== 10);	
}
/*
 * Muestra la carta numero 0 del mazo de descartes.
*/
void MostrarCartaDescartes(int mode,TBaraja *md,TCarta descarte)
{
    printf("Mazo descartes: \n");
	printf("|");
        cambiar_color_letra(WHITE);
		switch(md->Cartas[0].Color)
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

		switch(md->Cartas[0].Valor)
		{
		default:printf(" %d ",md->Cartas[0].Valor);
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
        printf(" (%d)",md->NumeroDeCartas);
        printf("\t");
        if(descarte.Valor == 13 || descarte.Valor == 14)
        {
            printf("Color escogido: |");
            switch(descarte.Color)
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
            printf("   ");
            default_attributes();
            printf("|\t");
        }
}
/*
 * Muestra el sentido de la partida dependiendo del valor de este.
*/
void MostrarSentido(int sentido)
{
    printf("Sentido: ");
    cambiar_color_letra(BLUE);
    if(sentido==0) printf("HORARIO");
    else printf("ANTIHORARIO");
    default_attributes();
}
/*
 * Elimina una carta de cualquiermazo y te la devuelve.
*/
TCarta EliminarCarta(int num,TBaraja *deck)
{
int k;
TCarta x;
	x = deck->Cartas[num];
	for(k=num;k<deck->NumeroDeCartas;k++)
	{
		deck->Cartas[k] = deck->Cartas[k+1];
	}
	deck->NumeroDeCartas--;
return(x);
}
/*
 * Añade una carta a cualquier mazo.
*/
void AnadirCarta(TCarta x,TBaraja *deck)
{

deck->Cartas[deck->NumeroDeCartas] = x;
deck->NumeroDeCartas++;
}
/*
 * Coge una carta y se añade a el mazo descartes.
*/
void AnadirCartaDescartes(TCarta x,TBaraja *descartes)
{
    int i;
    for(i = descartes->NumeroDeCartas;i>0;i--)  
    {
        descartes->Cartas[i]=descartes->Cartas[i-1];
    }
    descartes->Cartas[0]=x;
    descartes->NumeroDeCartas++;
}
/*
 * Si la baraja esta vacia, pone todas las cartas menos la primera del mazo descartes en la baraja y despues las mezcla.
*/
void BarajaVacia(TBaraja *mazo, TBaraja *descartes)
{
	int i;

	if(mazo->NumeroDeCartas == 0)
	{
		for (i=1; i<=descartes->NumeroDeCartas; i++)
		{
			mazo->Cartas[i-1].Valor=descartes->Cartas[i].Valor;
			mazo->Cartas[i-1].Color=descartes->Cartas[i].Color;
		}
                mazo->NumeroDeCartas = descartes->NumeroDeCartas-1;
                descartes->NumeroDeCartas=1;
                MezclarCartas(mazo);
	}
}
/*
 * Muestra uno si la cantidad de cartas es 1.
*/
void Uno(TBaraja actual)
{
        if(actual.NumeroDeCartas==1)
        {
        cambiar_color_letra(GREEN);
        printf(" ** UNO **   ");
        default_attributes();
        }
}
/*
 * Muestra una carta.
*/
void MostrarCarta(TCarta c)
{
   printf("|");
        cambiar_color_letra(WHITE);
		switch(c.Color)
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

		switch(c.Valor)
		{
		default:printf(" %d ",c.Valor);
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
/*
 * Cambia el color, y dependiendo de si es el jugador o el robot, es aleatorio o se escanea.
*/
int CambiarColor(int turnojug,int numjugs)
{
	int color;
        if(turnojug!=0)
        {
            srand(time(NULL));
            color = rand()%4 +1;
            printf("    ");
        }
        else
        {
        do
        {
            printf("Que color escoges? [ 1(|");
            cambiar_color_fondo(YELLOW);
            printf("  ");
            default_attributes();
            printf("|) 2(|");
            cambiar_color_fondo(RED);
            printf("  ");
            default_attributes();
            printf("|) 3(|");
            cambiar_color_fondo(GREEN);
            printf("  ");
            default_attributes();	
            printf("|) 4(|");
            cambiar_color_fondo(BLUE);
            printf("  ");
            default_attributes();
            printf("|) ]: ");
           
            scanf("%d%*c", &color);
	
	}while(color<1 || color>4);
        }
            printf("Color escogido: |");
            switch(color)
            {
                case 1:
                    cambiar_color_fondo(YELLOW);
                    break;
                case 2:
                    cambiar_color_fondo(RED);
                    break;
                case 3:
                    cambiar_color_fondo(GREEN);
                    break;
                case 4:
                    cambiar_color_fondo(BLUE);
                    break;
            }		
            printf("  ");
            default_attributes();
            printf("|\n");
            return(color);
}
/*
 * Muestra una carta, cuando se juega en modo no comprobacion.
*/
void MostrarUno()
{
        printf("|");
        cambiar_color_fondo(WHITE);
        cambiar_color_letra(RED);
        printf("UNO");
        default_attributes();
        printf("|");
}







