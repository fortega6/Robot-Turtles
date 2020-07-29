#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include "mazo.h"

////////////////////////////////////////////////////////////////////////////////////
///TIPOS DE DATOS
/////////////////
typedef enum { NEGRO, AZUL_OSCURO, VERDE_OSCURO, CIAN_OSCURO, ROJO_OSCURO,
               VIOLETA_OSCURO, AMARILLO_OSCURO, GRIS_CLARO, GRIS_OSCURO,
               AZUL_CLARO, VERDE_CLARO, CIAN_CLARO, ROJO_CLARO,
               VIOLETA_CLARO, AMARILLO_CLARO, BLANCO } tColor;

typedef enum { NORTE, ESTE, SUR, OESTE } tDir;
typedef enum { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA } tEstadoCasilla;
typedef enum { ARRIBA, ABAJO, DERECHA, IZQUIERDA, ESPACIO, ENTER, OTRA } tTecla;
typedef enum { ROBAR_CART, EJEC_SECU } tAccion;

const int NUM_COL_TAB = 8;
const int NUM_FIL_TAB = 8;
const int MAX_JUGADORES = 4;
const int NUM_ITEMS_VISUAL = 5;
const int PALETA[NUM_ITEMS_VISUAL + MAX_JUGADORES] = { AZUL_OSCURO, CIAN_CLARO, GRIS_OSCURO,
                                                       ROJO_OSCURO, ROJO_CLARO,
                                                       VIOLETA_CLARO, VERDE_OSCURO,
                                                       VIOLETA_OSCURO, AZUL_CLARO };

typedef struct
{
    int numero;
    tDir direccion;
}tTortuga;

typedef struct
{
    tEstadoCasilla estado;
    tTortuga tortuga;
}tCasilla;

typedef tCasilla tTablero[NUM_FIL_TAB][NUM_COL_TAB];

typedef struct
{
    int fil;
    int col;
} tCoordenada;

typedef int tMano[NUM_TIPOS_CARTA];

typedef struct
{
    std::string nombre;
    tMazo mazo;
    tMano mano;
    tCoordenada coordAct;
} tJugador;

typedef struct
{
    tTablero tablero;
    int numJugadores;
    tJugador jugadores[MAX_JUGADORES];
    int turno;
    bool finalizado;
} tJuego;
////////////////////////////////////////////////////////////////////////////////////

tEstadoCasilla enumCasilla(char c);
tDir enumDireccion(char c);
std::string strCasilla(tCasilla c);
std::string strCarta(tCarta c);
tCarta cartaTecla(tTecla t);

bool secuenciaValid(tMano mano, tMazo secu);
void manoVacia(tMano mano);
void incluirCarta(tMano& mano, tCarta carta);
void descartCarta(tMano mano, tCarta carta);

void girarDer(tDir& dir);
void girarIzq(tDir& dir);
void dispararLaser(tTablero tab, tCoordenada pos, tDir dir);
void avanzar(tTablero tab, tCoordenada& pos, tDir dir, bool& joy);

bool cargarJuego(tJuego& juego);
void iniciarJuego(tJuego& juego);
void mostrarJuego(const tJuego& juego);
void mostrarEjecSecu(tMazo secu, int ejectdo);

bool accionRobar(tJuego& juego);
bool accionSecuencia(tJuego& juego, tMazo& cartas);
bool ejecutarTurno(tJuego& juego);
void cambiarTurno(tJuego& juego);
bool esFinDePartida(const tJuego& juego);
void mostrarGanador(const tJuego& juego);

void colorFondo(int color);
tTecla leerTecla();

#endif  //JUEGO_H
