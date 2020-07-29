#ifndef MAZO_H
#define MAZO_H

const int MAX_CARTAS_MAZO = 38;
const int NUM_TIPOS_CARTA = 4;
const int MAX_CAVANZAR = 18;
const int MAX_CGIRODER = 8;
const int MAX_CGIROIZQ = 8;
const int MAX_CLASER = 4;

enum tCarta { AVANZAR, GIROIZQUIERDA, GIRODERECHA, PISTLASER };

struct tMazo
{
    tCarta secCartas[MAX_CARTAS_MAZO];
    int numCartas;
};

void crearVacia(tMazo& mazo);
bool sacar(tMazo& mazo, tCarta& carta);
void insertar(tMazo& mazo, tCarta carta);
void crearMazoAleatorio(tMazo& mazo);

#endif  //MAZO_H
