#include <algorithm>
#include "mazo.h"

/**
 * @brief crearVacia Crea un mazo vacio, una secuencia vacia de cartas.
 * @param mazo El Mazo vacio que sera creado
 */
void crearVacia(tMazo& mazo)
{
    mazo.numCartas = 0;
}

/**
 * @brief sacar Saca una carta de la parte superior del mazo. Devuelve true si se ha podido sacar
 *              la carta, false en caso contrario.
 * @param mazo  El mazo del cual sera tomada la carta
 * @param carta La carta tomada del mazo
 * @return      Devuelve true si una carta ha podido ser sacada del mazo, false en caso contrario.
 */
bool sacar(tMazo & mazo, tCarta& carta)
{
    bool sacada = false;

    if (mazo.numCartas > 0)
    {
        carta = mazo.secCartas[0];
        for (int i = 1; i < mazo.numCartas; ++i)
            mazo.secCartas[i - 1] = mazo.secCartas[i];

        mazo.numCartas--;
        sacada = true;
    }

    return sacada;
}

/**
 * @brief insertar Inserta la carta en la parte inferior del mazo.
 * @param mazo     Mazo donde sera insertada la carta
 * @param carta    Carta a ser insertada en el mazo.
 */
void insertar(tMazo& mazo, tCarta carta)
{
    mazo.secCartas[mazo.numCartas] = carta;
    mazo.numCartas++;
}

/**
 * @brief crearMazoAleatorio Crea un mazo lleno de cartas, dispuestas en orden aleatorio.
 * @param mazo  Mazo de cartas aleatorio creado.
 */
void crearMazoAleatorio(tMazo& mazo)
{
    //crear un mazo con todas las cartas disponibles
    int i = 0;
    for ( ; i < MAX_CAVANZAR; ++i)
        mazo.secCartas[i] = AVANZAR;

    for ( ; i < MAX_CAVANZAR + MAX_CGIRODER; ++i)
        mazo.secCartas[i] = GIRODERECHA;

    for ( ; i < MAX_CAVANZAR + MAX_CGIRODER + MAX_CGIROIZQ; ++i)
        mazo.secCartas[i] = GIROIZQUIERDA;

    for ( ; i < MAX_CAVANZAR + MAX_CGIRODER + MAX_CGIROIZQ + MAX_CLASER; ++i)
        mazo.secCartas[i] = PISTLASER;

    mazo.numCartas = MAX_CARTAS_MAZO;

    //barajar el mazo de cartas
    std::random_shuffle(mazo.secCartas, mazo.secCartas + MAX_CARTAS_MAZO);
}
