#ifndef JUGADOR_H
#define JUGADOR_H
#include "Ficha.h"

#include <string>

const int N_FICHAS = 9;

class Jugador
{
public:
    Jugador();
    virtual ~Jugador();

    void setWin(bool isWinner);
    bool getWin();
    void setTurn(bool turn);
    bool getTurn();
    void setBlocked(bool);
    bool getBlocked();

    void setFichasColocadas(int);
    int getFichasColocadas();
    void fichaColocada();

    void setSpriteJugador(string sprite);
    string getSpriteJugador();

    void nextTurn(); //pasa los turnos automaticamente

protected:
private:
    Ficha n_fichas[N_FICHAS];

    string spriteJugador;

    int fichasColocadas;

    bool turno;
    bool win;
    bool blocked;
};

#endif // JUGADOR_H
