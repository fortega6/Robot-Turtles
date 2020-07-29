#ifndef PUNTUACIONES_H
#define PUNTUACIONES_H

#include <string>
#include "juego.h"

typedef struct
{
    std::string nombre;
    int puntaje;
} tPuntJugador;

typedef struct
{
    tPuntJugador ranking[MAX_JUGADORES];
    int numJugadores;
} tPuntuaciones;

bool cargarPuntuaciones(tPuntuaciones& p);
void guardarPuntuaciones(const tPuntuaciones& p);
void mostrarPuntuaciones(const tPuntuaciones& p);
bool actualizarPuntuaciones(tPuntuaciones& p, const std::string& nomb, int incr);
bool cmpPuntaje(tPuntJugador j1, tPuntJugador j2);

#endif  //PUNTUACIONES_H
