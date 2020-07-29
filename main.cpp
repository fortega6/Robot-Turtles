#include <iostream>
#include "puntuaciones.h"
#include "juego.h"

int menu();

int main(void)
{
    tPuntuaciones puntJuego;
    tJuego nuevJuego;

    cargarPuntuaciones(puntJuego);

    int opc;
    while ((opc = menu()) != 0)
    {
        switch(opc)
        {
        case 1:
            if (cargarJuego(nuevJuego))
            {
                std::cout << "\n\tTablero/Juego Cargado Exitosamente!!!\n\t";
                system("pause");
                system("cls");

                //jugar
                while (!esFinDePartida(nuevJuego))
                {
                    bool ganador = ejecutarTurno(nuevJuego);
                    if (!ganador)
                        cambiarTurno(nuevJuego);
                }

                mostrarGanador(nuevJuego);
                actualizarPuntuaciones(puntJuego,
                                       nuevJuego.jugadores[nuevJuego.turno].nombre,
                                       nuevJuego.numJugadores);
            }
            else
            {
                std::cout << "\n\t*** Error al cargar el tablero/juego ***\n\t\a";
                system("pause");
            }

            break;

        case 2:
            mostrarPuntuaciones(puntJuego);
            std::cout << "\n\t";
            system("pause");
            break;

        default:
            std::cout << "\n\n\t*** Opcion Invalida ***\n\t\a";
            system("pause");
            break;
        }
    }

    // Salir
    std::cout << "\n    ";
    system("pause");
    system("cls");

    return 0;
}

int menu()
{
    system("cls");

    colorFondo(NEGRO);
    std::cout << "\n\t+--------------------+\n\t|";
    colorFondo(VERDE_OSCURO);
    std::cout << " TORTUGAS ROBOTICAS ";
    colorFondo(NEGRO);
    std::cout << "|\n\t+--------------------+\n\n";
    std::cout << "    1. Jugar" << std::endl;
    std::cout << "    2. Mostrar Puntuaciones" << std::endl << std::endl;
    std::cout << "    0. Salir" << "\n >. #: ";

    int opc;
    std::cin >> opc;

    return opc;
}
