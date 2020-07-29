#include <iostream>
#include <fstream>
#include <algorithm>
#include "puntuaciones.h"
#include "juego.h"

/**
 * @brief cargarPuntuaciones    Carga en memoria las puntuaciones de los jugadores
 *                              desde el fichero Puntuaciones.txt.
 * @param p Estructura donde son cargadas puntuaciones y nombres de los jugadores.
 * @return  Devuelve true si el fichero ha sido cargado correctamente a memoria,
 *          false en caso contrario.
 */
bool cargarPuntuaciones(tPuntuaciones& p)
{
    bool cargado = false;
    std::ifstream fich("Puntuaciones.txt");

    if (fich.is_open())
    {
        int i = 0;
        while (!fich.eof() && i < MAX_JUGADORES)
        {
            fich >> p.ranking[i].nombre >> p.ranking[i].puntaje;
            ++i;
        }

        p.numJugadores = i;
        std::sort(p.ranking, p.ranking + p.numJugadores, cmpPuntaje);
        fich.close();
        cargado = true;
    }

    return cargado;
}

/**
 * @brief guardarPuntuaciones
 * @param p
 */
void guardarPuntuaciones(const tPuntuaciones& p)
{
    std::ofstream fich("Puntuaciones.txt");
    if (fich.is_open())
    {
        for (int i = 0; i < p.numJugadores; ++i)
            fich << p.ranking[i].nombre << " " << p.ranking[i].puntaje << std::endl;

        fich.close();
    }
}

/**
 * @brief mostrarPuntuaciones
 * @param p
 */
void mostrarPuntuaciones(const tPuntuaciones& p)
{
    system("cls");
    colorFondo(NEGRO);
    std::cout << "\n\tPUNTUACIONES\n\n"
              << "\t  Nro.\t\tJugador\t\tPuntuacion\n"
              << "\t+------------------------------------------+\n";
    for (int i = 0; i <	p.numJugadores; ++i)
    {
        colorFondo(NEGRO);
        std::cout << "\t|";

        colorFondo(VERDE_OSCURO);
        std::cout << " "<< i + 1 << "\t\t";
        std::cout << p.ranking[i].nombre << "\t\t" ;
        std::cout << p.ranking[i].puntaje << "          ";

        colorFondo(NEGRO);
        std::cout << "|\n";
    }

    std::cout << "\t+------------------------------------------+\n";
}

/**
 * @brief actualizarPuntuaciones
 * @param p
 * @param nomb
 * @param nuevPto
 * @return
 */
bool actualizarPuntuaciones(tPuntuaciones& p, const std::string& nomb, int incr)
{
    bool actualizado = false;

    int i = 0;
    while (nomb != p.ranking[i].nombre && i < p.numJugadores)
        i++;

    if (i < p.numJugadores)     //jugador esta en el ranking
    {
        p.ranking[i].puntaje += incr;

        std::sort(p.ranking, p.ranking + p.numJugadores, cmpPuntaje);
        actualizado = true;
    }
    else if (i < MAX_JUGADORES) //jugador nuevo y con espacio
    {
        p.ranking[i].nombre = nomb;
        p.ranking[i].puntaje = incr;
        p.numJugadores++;

        std::sort(p.ranking, p.ranking + p.numJugadores, cmpPuntaje);
        actualizado = true;
    }
    else    //no hay espacio
    {
        if ( p.ranking[MAX_JUGADORES - 1].puntaje < incr)
        {
            p.ranking[MAX_JUGADORES - 1].nombre  = nomb;
            p.ranking[MAX_JUGADORES - 1].puntaje = incr;

            std::sort(p.ranking, p.ranking + p.numJugadores, cmpPuntaje);
            actualizado = true;
        }
    }

    return actualizado;
}

/**
 * @brief cmpPuntaje
 * @param j1
 * @param j2
 * @return
 */
bool cmpPuntaje(tPuntJugador j1, tPuntJugador j2)
{
   return (j1.puntaje > j2.puntaje);
}
