#include "../include/Jugador.h"

Jugador::Jugador()
{
    for (int i = 0; i < N_FICHAS; i++)
    {
        n_fichas[i].setValor(spriteJugador);
    }

    turno = false;
    win = false;

    fichasColocadas = 1;
}

Jugador::~Jugador()
{
    //dtor
}

void Jugador::setWin(bool isWinner)
{
    win = isWinner;
}

bool Jugador::getWin()
{
    return win;
}

void Jugador::setTurn(bool turn)
{
    turno = turn;
}

bool Jugador::getTurn()
{
    return turno;
}

void Jugador::setBlocked(bool block)
{
    blocked = block;
}

bool Jugador::getBlocked()
{
    return blocked;
}

void Jugador::setFichasColocadas(int nFichas)
{
    fichasColocadas = nFichas;
}

int Jugador::getFichasColocadas()
{
    return fichasColocadas;
}

void Jugador::fichaColocada()
{
    fichasColocadas++;
}

void Jugador::setSpriteJugador(string sprite)
{
    spriteJugador = sprite;
}

string Jugador::getSpriteJugador()
{
    return spriteJugador;
}

void Jugador::nextTurn()
{
    if (turno)
    {
        turno = false;
    }
    else
    {
        turno = true;
    }
}
