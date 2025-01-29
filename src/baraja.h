#ifndef BARAJA_H
#define BARAJA_H
#define BAR 108
#define MAXBAR 108
#define MAXJUG 5

typedef struct{
int Valor;
int Color;
}TCarta;

typedef struct{
int NumeroDeCartas;
TCarta Cartas[BAR];
}TBaraja;

void CrearCartas(TBaraja *ma);
void MezclarCartas(TBaraja *ma);
void MostrarCartasMazo(int *mode,TBaraja *ma);
void MostrarCartaDescartes(int mode,TBaraja *md, TCarta descarte);
void AnadirCarta(TCarta x,TBaraja *deck);
TCarta EliminarCarta(int num,TBaraja *deck);
void BarajaVacia(TBaraja *mazo, TBaraja *descartes);
void Uno(TBaraja actual);
void MostrarCarta(TCarta c);
void MostrarSentido(int sentido);
int CambiarColor(int turnojug,int numjugs);
void AnadirCartaDescartes(TCarta x,TBaraja *descartes);
void MostrarUno();
#endif //BARAJA_H
