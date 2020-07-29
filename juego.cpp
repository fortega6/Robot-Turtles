#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "juego.h"

/**
 * @brief enumDireccion Devuelve la enumeracion de direccion asociada con una letra dada.
 * @param c Caracter que representa en forma textual un posible direccion de una tortuga.
 * @return  Enumeracion de direccion correspondiente a c.
 */
tDir enumDireccion(char c)
{
    tDir dir;
    switch (c)
    {
    case 'U':
        dir = NORTE;
        break;

    case 'D':
        dir = SUR;
        break;

    case 'R':
        dir = ESTE;
        break;

    case 'L':
        dir = OESTE;
        break;
    }

    return dir;
}

/**
 * @brief enumCasilla Devuelve la enumeracion de casilla asociada con un caracter dado.
 * @param c Caracter que representa en forma textual un posible estado de una casilla.
 * @return  Enumeracion de estado de casilla correspondiente a c.
 */
tEstadoCasilla enumCasilla(char c)
{
    tEstadoCasilla casilla;
    switch (c)
    {
    case ' ':
        casilla = VACIA;
        break;

    case '#':
        casilla = MURO;
        break;

    case '@':
        casilla = HIELO;
        break;

    case '$':
        casilla = JOYA;
        break;

    case 'C':
        casilla = CAJA;
        break;

    case 'U':
    case 'D':
    case 'R':
    case 'L':
        casilla = TORTUGA;
        break;
    }

    return casilla;
}

/**
 * @brief cargarJuego   Carga el tablero de juego y el numero de jugadores, desde un fichero.
 *                      Tambien inicializa los mazos y manos de cada jugador.
 * @param juego
 * @return
 */

bool cargarJuego(tJuego& juego)
{
    bool cargado = false;

    //ruta del fichero de tablero
    std::string nomFich;

    system("cls");
    std:: cout << "\n\t>. Fichero de tableros: ";
    std::cin >> nomFich;

    std::ifstream fich(nomFich.c_str());

    if (fich.is_open())
    {
        //datos de la partida: numero de jugadores
        int numJugadores;
        std::cout << "\t>. Cantidad de jugadores: ";
        std::cin >> numJugadores;

        if (numJugadores >= 1 && numJugadores <= MAX_JUGADORES)
        {
            juego.numJugadores = numJugadores;

            int num;
            std::string text[NUM_FIL_TAB];

            //cargar el tablero desde el archivo
            while (!cargado && !fich.eof())
            {
                //cargar el tablero en representacion textual
                fich >> num;
                fich.ignore(100,'\n');

                for (int j = 0; j < NUM_FIL_TAB; ++j)
                    std::getline(fich, text[j]);

                //tablero buscado -> procesar
                if (num == numJugadores)
                {
                    int contJugadProc = 0;
                    for (int j = 0; j < NUM_FIL_TAB; ++j)
                    {
                        for (int k = 0; k < NUM_COL_TAB; ++k)
                        {
                            tEstadoCasilla estdCasilla = enumCasilla(text[j][k]);
                            juego.tablero[j][k].estado = estdCasilla;

                            if (estdCasilla == TORTUGA) //jugador detectado: inicializar datos
                            {
                                //datos de la tortuga
                                juego.tablero[j][k].tortuga.numero = contJugadProc;
                                juego.tablero[j][k].tortuga.direccion = enumDireccion(text[j][k]);

                                //nombre de jugador asociado
                                std::cout << "\t>. Nombre Jugador " << contJugadProc + 1 << ": ";
                                std::cin >> juego.jugadores[contJugadProc].nombre;

                                //ubicacion del jugador en el tablero
                                juego.jugadores[contJugadProc].coordAct.fil = j;
                                juego.jugadores[contJugadProc].coordAct.col = k;

                                //mazo de cartas y mano
                                crearMazoAleatorio(juego.jugadores[contJugadProc].mazo);
                                manoVacia(juego.jugadores[contJugadProc].mano);

                                tCarta c1, c2, c3;
                                sacar(juego.jugadores[contJugadProc].mazo, c1);
                                incluirCarta(juego.jugadores[contJugadProc].mano, c1);

                                sacar(juego.jugadores[contJugadProc].mazo, c2);
                                incluirCarta(juego.jugadores[contJugadProc].mano, c2);

                                sacar(juego.jugadores[contJugadProc].mazo, c3);
                                incluirCarta(juego.jugadores[contJugadProc].mano, c3);

                                //actualizar cuenta de jugadores procesados
                                ++contJugadProc;
                            }
                        }
                    }

                    juego.turno = 0;
                    juego.finalizado = false;
                    cargado = true;
                }
            }

            fich.close();
        }
        else{ std::cerr << "\n\t*** Error: numero invalido de jugadores (" << numJugadores << ") ***\n\t\a"; }
    }
    else{ std::cerr << "\n\t*** No se puede abrir el fichero \"" << nomFich << "\" ***\n\t\a"; }

    return cargado;
}

/**
 * @brief strVisual
 * @return
 */
std::string strCasilla(tCasilla c)
{
    std::string str;
    switch (c.estado)
    {
    case VACIA:
        str = "  ";
        break;

    case HIELO:
        str = "**";
        break;

    case MURO:
        str = "||";
        break;

    case CAJA:
        str = "[]";
        break;

    case JOYA:
        str = "00";
        break;

    case TORTUGA:
        switch (c.tortuga.direccion)
        {
        case NORTE:
            str = "^^";
            break;

        case ESTE:
            str = ">>";
            break;

        case SUR:
            str = "vv";
            break;

        case OESTE:
            str = "<<";
            break;
        }
        break;
    }

    return str;
}

/**
 * @brief strCarta
 * @param c
 * @return
 */
std::string strCarta(tCarta c)
{
    std::string str;
    switch(c)
    {
    case AVANZAR:
        str = "^";
        break;

    case GIROIZQUIERDA:
        str = "<";
        break;

    case GIRODERECHA:
        str = ">";
        break;

    case PISTLASER:
        str = "~";
        break;
    }

    return str;
}

/**
 * @brief cartaTecla
 * @param t
 * @return
 */
tCarta cartaTecla(tTecla t)
{
    tCarta c;
    switch (t)
    {
    case ARRIBA: c = AVANZAR;
        break;
    case DERECHA: c = GIRODERECHA;
        break;
    case IZQUIERDA: c = GIROIZQUIERDA;
        break;
    case ESPACIO: c = PISTLASER;
        break;
    }

    return c;
}

/**
 * @brief secuenciaValid
 * @param mano
 * @param secu
 * @return
 */
bool secuenciaValid(tMano mano, tMazo secu)
{
    //contar la frecuencia de cada tipo de carta en secu
    int cont[NUM_TIPOS_CARTA];
    for (int i = 0; i < NUM_TIPOS_CARTA; ++i)
        cont[i] = 0;

    for (int i = 0; i < secu.numCartas; ++i)
        cont[secu.secCartas[i]]++;

    //comparar frecuencia de cada tipo de carta en secu
    //con la cantidad disponibles en mano por cada tipo
    bool secuValid = true;
    int i = 0;
    while (secuValid && i < NUM_TIPOS_CARTA)
        if (cont[i] > mano[i])
            secuValid = false;
        else
            ++i;

    return secuValid;
}

/**
 * @brief manoVacia
 * @param mano
 */
void manoVacia(tMano mano)
{
    for (int i = 0; i < NUM_TIPOS_CARTA; ++i)
        mano[i] = 0;
}

/**
 * @brief girarDer
 * @param dir
 */
void girarDer(tDir& dir)
{
    dir = tDir((dir + 1) % 4);
}

/**
 * @brief girarIzq
 * @param dir
 */
void girarIzq(tDir& dir)
{
   dir = tDir((dir + 3) % 4);
}

/**
 * @brief dispararLaser
 * @param tab
 * @param pos
 * @param dir
 */
void dispararLaser(tTablero tab, tCoordenada pos, tDir dir)
{
    bool objAlcanzado = false;
    switch (dir)
    {
    case NORTE:
        for (int i = (pos.fil - 1); !objAlcanzado && i >= 0; --i)
            if (tab[i][pos.col].estado != VACIA)
            {
                objAlcanzado = true;

                if (tab[i][pos.col].estado == HIELO)
                    tab[i][pos.col].estado = VACIA;
            }
        break;

    case ESTE:
        for (int i = (pos.col + 1); !objAlcanzado && i < NUM_COL_TAB; ++i)
            if (tab[pos.fil][i].estado != VACIA)
            {
                objAlcanzado = true;

                if (tab[pos.fil][i].estado == HIELO)
                    tab[pos.fil][i].estado = VACIA;
            }
        break;

    case SUR:
        for (int i = (pos.fil + 1); !objAlcanzado && i < NUM_FIL_TAB; ++i)
            if (tab[i][pos.col].estado != VACIA)
            {
                objAlcanzado = true;

                if (tab[i][pos.col].estado == HIELO)
                    tab[i][pos.col].estado = VACIA;
            }
        break;

    case OESTE:
        for (int i = (pos.col - 1); !objAlcanzado && i >= 0; --i)
            if (tab[pos.fil][i].estado != VACIA)
            {
                objAlcanzado = true;

                if (tab[pos.fil][i].estado == HIELO)
                    tab[pos.fil][i].estado = VACIA;
            }
        break;
    }
}

/**
 * @brief avanzar   Dentro del tablero tab, avanza una tortuga en la posicion pos, con direccion dir.
 *                  Si tras avanzar la tortuga alcanza una joya, joy es puesto a true.
 * @param tab
 * @param pos
 * @param dir
 * @param joy
 */
void avanzar(tTablero tab, tCoordenada& pos, tDir dir, bool& joy)
{
    joy = false;
    switch (dir)
    {
    case NORTE:
        if (pos.fil > 0)
            if (tab[pos.fil - 1][pos.col].estado == VACIA)
            {
                tab[pos.fil - 1][pos.col] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.fil--;
            }
            else if (tab[pos.fil - 1][pos.col].estado == JOYA)
            {
                tab[pos.fil - 1][pos.col] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.fil--;
                joy = true;
            }
            else if (pos.fil > 1 && tab[pos.fil - 1][pos.col].estado == CAJA
                                 && tab[pos.fil - 2][pos.col].estado == VACIA)
            {
                tab[pos.fil - 2][pos.col].estado = CAJA;
                tab[pos.fil - 1][pos.col] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.fil--;
            }
        break;

    case ESTE:
        if (pos.col < NUM_COL_TAB - 1)
            if (tab[pos.fil][pos.col + 1].estado == VACIA)
            {
                tab[pos.fil][pos.col + 1] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.col++;
            }
            else if (tab[pos.fil][pos.col + 1].estado == JOYA)
            {
                tab[pos.fil][pos.col + 1] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.col++;
                joy = true;
            }
            else if (pos.col < (NUM_COL_TAB - 2) && tab[pos.fil][pos.col + 1].estado == CAJA
                                                 && tab[pos.fil][pos.col + 2].estado == VACIA)
            {
                tab[pos.fil][pos.col + 2].estado = CAJA;
                tab[pos.fil][pos.col + 1] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.col++;
            }
        break;

    case SUR:
        if (pos.fil < NUM_FIL_TAB - 1)
            if (tab[pos.fil + 1][pos.col].estado == VACIA)
            {
                tab[pos.fil + 1][pos.col] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.fil++;
            }
            else if (tab[pos.fil + 1][pos.col].estado == JOYA)
            {
                tab[pos.fil + 1][pos.col] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.fil++;
                joy = true;
            }
            else if (pos.fil < (NUM_FIL_TAB - 2) && tab[pos.fil + 1][pos.col].estado == CAJA
                                                 && tab[pos.fil + 2][pos.col].estado == VACIA)
            {
                tab[pos.fil + 2][pos.col].estado = CAJA;
                tab[pos.fil + 1][pos.col] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.fil++;
            }
        break;

    case OESTE:
        if (pos.col > 0)
            if (tab[pos.fil][pos.col - 1].estado == VACIA)
            {
                tab[pos.fil][pos.col - 1] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.col--;
            }
            else if (tab[pos.fil][pos.col - 1].estado == JOYA)
            {
                tab[pos.fil][pos.col - 1] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.col--;
                joy = true;
            }
            else if (pos.col > 1 && tab[pos.fil][pos.col - 1].estado == CAJA
                                 && tab[pos.fil][pos.col - 2].estado == VACIA)
            {
                tab[pos.fil][pos.col - 2].estado = CAJA;
                tab[pos.fil][pos.col - 1] = tab[pos.fil][pos.col];
                tab[pos.fil][pos.col].estado = VACIA;
                pos.col--;
            }
        break;
    }
}

/**
 * @brief mostrarJuego  Visualiza el estado actual del juego en la pantalla.
 * @param juego Juego que sera visualizado.
 */
void mostrarJuego(const tJuego& juego)
{
    //dibujar tablero
    system("cls");
    colorFondo(NEGRO);
    std::cout << "\n\n";

    for (int i = 0; i < NUM_FIL_TAB; ++i)
    {
        colorFondo(NEGRO);
        std::cout << "\t";

        for (int j = 0; j < NUM_COL_TAB; ++j)
        {
            tEstadoCasilla tipoCasilla = juego.tablero[i][j].estado;
            int numJugador = (tipoCasilla == TORTUGA) ? juego.tablero[i][j].tortuga.numero : 0;

            colorFondo(PALETA[tipoCasilla + numJugador]);   //color de fondo asociado
            std::cout << strCasilla(juego.tablero[i][j]);   //string correspondiente
        }

        colorFondo(NEGRO);
        std::cout << "\n";
    }

    //manos de jugadores
    int anchMax = juego.jugadores[0].nombre.size();
    for (int i = 1; i < juego.numJugadores; ++i)
        if (juego.jugadores[i].nombre.size() > anchMax)
            anchMax = juego.jugadores[i].nombre.size();

    std::cout << "\n\nJUGADORES:\n\n";
    for (int i = 0; i < juego.numJugadores; ++i)
    {
        //imprimir nombre del jugador
        colorFondo(PALETA[NUM_ITEMS_VISUAL + i]);  //color del jugador i

        char prompt = (juego.turno == i) ? '>' : ' ';
        std::string nomb = juego.jugadores[i].nombre;
        std::string pad(anchMax - nomb.size(), ' ');
        std::cout << prompt << " " << i + 1 << ". " << pad << nomb << ":";

        //imprimir la mano de cartas
        for (int j = 0; j < NUM_TIPOS_CARTA; ++j)
        {
            colorFondo(NEGRO);
            printf("%3d",juego.jugadores[i].mano[j]);

            colorFondo(CIAN_OSCURO);
            std::cout << " " << strCarta(tCarta(j)) << " ";
        }

        std::cout << "\n";
    }

    colorFondo(NEGRO);
}

/**
 * @brief accionRobar
 * @param juego
 * @return
 */
bool accionRobar(tJuego& juego)
{
    bool robada;
    tCarta c;

    if ((robada = sacar(juego.jugadores[juego.turno].mazo, c))) //se pudo tomar carta del mazo?
        incluirCarta(juego.jugadores[juego.turno].mano, c);     //agregar a la mano

    return robada;
}

/**
 * @brief mostrarProgSecu
 * @param secu
 */
void mostrarEjecSecu(tMazo secu, int ejectdo)
{
    std::cout << "\n\n\tEJECUCION SECUENCIA: ";

    colorFondo(VERDE_OSCURO);
    int j = 0;
    for ( ; j < ejectdo; ++j)
        std::cout << strCarta(secu.secCartas[j]);

    colorFondo(NEGRO);
    for ( ; j < secu.numCartas; ++j)
        std::cout << strCarta(secu.secCartas[j]);

    std::cout << "\n\t";
    system("pause");
}

/**
 * @brief accionSecuencia
 * @param juego
 * @param cartas
 * @return
 */
bool accionSecuencia(tJuego& juego, tMazo& cartas)
{
    bool joyaAlcanzada = false;
    int turn = juego.turno;
    int fil = juego.jugadores[turn].coordAct.fil;
    int col = juego.jugadores[turn].coordAct.col;

    //mostrar progreso de ejecucion 0
    mostrarJuego(juego);
    mostrarEjecSecu(cartas, 0);

    for (int i = 0; !joyaAlcanzada && i < cartas.numCartas; ++i)
    {
        //ejecutar accion de carta
        switch (cartas.secCartas[i])
        {
        case AVANZAR:
            avanzar(juego.tablero,
                    juego.jugadores[turn].coordAct,
                    juego.tablero[fil][col].tortuga.direccion,
                    joyaAlcanzada);

            //nueva coordenada actual
            fil = juego.jugadores[turn].coordAct.fil;
            col = juego.jugadores[turn].coordAct.col;
            break;

        case GIRODERECHA:
            girarDer(juego.tablero[fil][col].tortuga.direccion);
            break;

        case GIROIZQUIERDA:
            girarIzq(juego.tablero[fil][col].tortuga.direccion);
            break;

        case PISTLASER:
            dispararLaser(juego.tablero, juego.jugadores[turn].coordAct,
                          juego.tablero[fil][col].tortuga.direccion);
            break;
        }

        //descartar la carta e insertar en el fondo del mazo
        descartCarta(juego.jugadores[turn].mano, cartas.secCartas[i]);
        insertar(juego.jugadores[turn].mazo, cartas.secCartas[i]);

        //mostrar progreso de la ejecucion en la pantalla del juego
        mostrarJuego(juego);
        mostrarEjecSecu(cartas, i + 1);
    }

    return joyaAlcanzada;
}

/**
 * @brief ejecutarTurno
 * @param juego
 * @return
 */
bool ejecutarTurno(tJuego& juego)
{
    bool joyaAlcanzada = false;
    bool turnEjecutado = false;

    while (!juego.finalizado && !turnEjecutado)
    {
        mostrarJuego(juego);
        char opc;
        std::cout << "\n\n\tQUE JUGADA DESEA REALIZAR?\n"
                     "\t(R) Robar una carta del mazo\n"
                     "\t(E) Ejecutar una secuencia\n\t>";
        std::cin >> opc;

        switch (opc)
        {
        case 'r':
        case 'R':
            turnEjecutado = accionRobar(juego);
            if (!turnEjecutado)
            {
                std::cout << "\n\tMazo vacio, no se puede tomar mas cartas!!!\n\t\a";
                system("pause");
            }
            break;

        case 'e':
        case 'E':
            tMazo nuevSecu;
            crearVacia(nuevSecu);

            mostrarJuego(juego);
            std::cout << "\n\n\tSECUENCIA: ";

            //leer nueva secuencia de ejecucion
            tTecla tecla;
            while ((tecla = leerTecla()) != ENTER)
            {
                if (tecla != OTRA && tecla != ABAJO)
                    insertar(nuevSecu, cartaTecla(tecla));

                mostrarJuego(juego);
                std::cout << "\n\n\tSECUENCIA: ";
                for (int i = 0; i < nuevSecu.numCartas; ++i)
                    std::cout << strCarta(nuevSecu.secCartas[i]) << " ";
            }

            //secuencia valida? -> ejecutar
            if (secuenciaValid(juego.jugadores[juego.turno].mano, nuevSecu))
            {
                //ejecutar secuencia
                joyaAlcanzada = accionSecuencia(juego, nuevSecu);
                turnEjecutado = true;
            }
            else{ std::cout << "\n\t*** Error, Secuencia Invalida ***\n\t\a"; system("pause"); }

            break;

        default:
            std::cout << "\n\n\t*** Error, opcion de juego invalida ***\n\t\a";
            system("pause");
            break;
        }
    }

    if (joyaAlcanzada)  //joya alcanzada? -> juego finalizado
        juego.finalizado = true;

    return joyaAlcanzada;
}

/**
 * @brief cambiarTurno
 * @param juego
 */
void cambiarTurno(tJuego& juego)
{
    juego.turno =  (juego.turno + 1) % juego.numJugadores;
}

/**
 * @brief esFinDePartida
 * @param juego
 * @return
 */
bool esFinDePartida(const tJuego &juego)
{
    return juego.finalizado;
}

/**
 * @brief mostrarGanador
 * @param juego
 */
void mostrarGanador(const tJuego& juego)
{
    mostrarJuego(juego);

    if (juego.finalizado)
    {
        std::cout << "\n\n\t";

        colorFondo(VERDE_OSCURO);
        std::cout << "JOYA ALCANZADA: "
                  << juego.jugadores[juego.turno].nombre
                  << " gana el juego!!!";
    }

    colorFondo(NEGRO);
    std::cout << "\n\n\t";
    system("pause");
}

/**
 * @brief colorFondo
 * @param color
 */
void colorFondo(int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 15 | (color << 4));
}

/**
 * @brief leerTecla
 * @return
 */
tTecla leerTecla()
{
    std::cin.sync();

    tTecla tecla;
    int dir = _getch();

    if (dir == 0xe0)    //tecla especial!
    {
        dir = _getch(); //obtener el codigo
        switch(dir)
        {
            case 72: tecla = ARRIBA;
                break;
            case 77: tecla = DERECHA;
                break;
            case 80: tecla = ABAJO;
                break;
            case 75: tecla = IZQUIERDA;
                break;
        }

    }
    else if (dir == 13)
        tecla = ENTER;
    else if (dir == 32)
        tecla = ESPACIO;
    else                //otra tecla
        tecla = OTRA;

    return tecla;
}

/**
 * @brief incluirCarta Incluye una nueva carta en la mano de un jugador.
 * @param mano  Mano en que sera incluida la carta
 * @param carta Tipo de carta que se agregara a la mano.
 */
void incluirCarta(tMano& mano, tCarta carta)
{
    mano[carta]++;
}

/**
 * @brief descartCarta Descarta una carta de la mano de un jugador.
 * @param mano  Mano de la que se tomara la carta.
 * @param carta Tipo de carta que sera descartada.
 */
void descartCarta(tMano mano, tCarta carta)
{
    if (mano[carta] > 0)
        --mano[carta];
}
