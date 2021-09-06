#include "../include/Reglas.h"
#include <iostream>
#include "string"
#include <windows.h>

using namespace std;

Reglas::Reglas()
{
    //ctor
}

Reglas::~Reglas()
{
    //dtor
}

/**************************************************************
 * Comprueba que la ficha que el jugador está seleccionando   *
 * es suya                                                    *
 * ************************************************************/
bool Reglas::cogerFicha(Jugador player, Ficha ficha)
{
    if (player.getSpriteJugador() == ficha.getValor())
    {
        return true;
    }

    return false;
}

bool Reglas::posicionLibre(Tablero tablero, int x, int y)
{
    //falla la comparación, no detecta el caracter del tablero como libre

    cout << "\n\nimprimiendo el valor para testear: " << tablero.getFicha(x, y).getValor() << endl;
    system("pause");
    // bool posFree = tablero.getFicha(x, y).getValor() == 'o' ? true : false;
    return false;
}

/**************************************************************
 * Comprueba si el movimiento horizontal es valido para las   *
 * coordenadas que el jugador ha puesto                       *
 * ************************************************************/
bool Reglas::moverHoriz(Tablero tablero, Ficha ficha, int x, int y)
{
    int i = 1;

    if (ficha.getX() == 0 || ficha.getX() == 6)
    {
        i = 3;
    }
    else
    {
        if (ficha.getX() == 1 || ficha.getX() == 5)
        {
            i = 2;
        }
    }

    //si la siguiente casilla (no matriz, sino casilla del juego) de las disponibles es la seleccionada por el jugador
    if ((ficha.getY() + i == y || ficha.getY() - i == y) && ficha.getX() == x)
    {
        //si la casilla esta libre
        if (tablero.getFicha(x, y).getValor() == "o")
        {
            return true;
        }
    }

    return false;
}

/**************************************************************
 * Comprueba si el movimiento vertical es valido para las     *
 * coordenadas que el jugador ha puesto                       *
 * ************************************************************/
bool Reglas::moverVert(Tablero tablero, Ficha ficha, int x, int y)
{
    int i = 1;

    if (ficha.getY() == 0 || ficha.getY() == 6)
    {
        i = 3;
    }
    else
    {
        if (ficha.getY() == 1 || ficha.getY() == 5)
        {
            i = 2;
        }
    }

    //si la siguiente casilla (no matriz, sino casilla del juego) de las disponibles es la seleccionada por el jugador
    if ((ficha.getX() + i == x || ficha.getX() - i == x) && ficha.getY() == y)
    {
        //si la casilla esta libre
        if (tablero.getFicha(x, y).getValor() == "o")
        {
            return true;
        }
    }

    return false;
}
/**************************************************************
 * Comprueba que la ficha que el jugador está seleccionando   *
 * la puede mover en la posicion que ha indicado y, si lo es, *
 * la coloca                                                  *
 * ************************************************************/
bool Reglas::movimientoValido(Tablero tablero, Jugador player, Ficha ficha, int x, int y)
{
    if (cogerFicha(player, ficha))
    {
        if ((0 <= x && x <= 6 && 0 <= y && y <= 6))
        {
            if (ficha.getX() == x && ficha.getY() == y)
            {
                cout << "La ficha ya esta en la posicion!" << endl;
            }
            else
            {
                if (moverHoriz(tablero, ficha, x, y) || moverVert(tablero, ficha, x, y))
                {
                    tablero.setFicha(player, x, y);
                }
                else
                {

                    cout << "La casilla destino seleccionada no permite colocar ficha porque otro jugador tiene su ficha o la posicion no es valida" << endl;
                }
            }
        }
    }

    return false;
}

/**************************************************************
 * Comprueba si la fase 1 ha terminado.                       *
 *                                                            *
 * La fase 1 trata de que cada jugador coloque fichas en el   *
 * tablero hasta que hayan colocado todas las que tienen      *
 * ************************************************************/
bool Reglas::isPhase1Finished(Jugador player1, Jugador player2)
{
    if (player1.getFichasColocadas() == 9 && player2.getFichasColocadas() == 9)
    {
        return true;
    }

    return false;
}

/**************************************************************
 * Comprueba quien de los jugadores ha ganado                 *
 *                                                            *
 * Para determinar quien pierde se tiene en cuenta 2 cosas:   *
 *  - Que el jugador solamente posea menos de 3 fichas en el  *
 *    tablero                                                 *
 *  - Que el jugador no pueda hacer ningún movimiento         *
 *    (blocked)                                               *
 * ************************************************************/
bool Reglas::isWin(Jugador player1, Jugador player2)
{
    if (player1.getFichasColocadas() == 2 || player1.getBlocked())
    {
        player2.setWin(true);
        return true;
    }
    else
    {
        if (player2.getFichasColocadas() == 2 || player2.getBlocked())
        {
            player1.setWin(true);
            return true;
        }
    }

    return false;
}
