#ifndef GAME_H
#define GAME_H

#include "Jugador.h"
#include "Tablero.h"
#include "Reglas.h"
#include <string>

class Game
{
public:
    Game();
    virtual ~Game();

    void printTitle();
    void printFichasColocadas();
    void printFichasRestantes();
    void printTurns(Jugador);

    void insertarFilasCol(Jugador player);
    void inputEliminar(Jugador);

    void pasarTurno();

    bool isPhase1Finished();
    bool isPhase2Finished();

    void playPhase1();
    void playPhase2();

    void play();

    void moverFicha(Jugador);

protected:
private:
    Jugador jugador1;
    Jugador jugador2;

    Tablero tablero;
    Tablero tableroTest;

    Ficha fichaActual;
    int filaActual;
    int colActual;

    int p1Fichas;
    int p2Fichas;

    int fichasRestantesP1;
    int fichasRestantesP2;

    int turnoActual;
    bool primeraFase;
};

#endif // GAME_H
