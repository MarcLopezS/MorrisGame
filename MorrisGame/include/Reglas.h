#ifndef REGLAS_H
#define REGLAS_H

#include "Jugador.h"
//#include "Ficha.h"
#include "Tablero.h"

class Reglas
{
public:
    Reglas();
    virtual ~Reglas();

    bool cogerFicha(Jugador, Ficha);
    bool posicionLibre(Tablero, int x, int y);

    bool moverHoriz(Tablero, Ficha, int, int);
    bool moverVert(Tablero, Ficha, int, int);

    bool movimientoValido(Tablero, Jugador, Ficha, int, int);

    bool isPhase1Finished(Jugador, Jugador);
    bool isWin(Jugador, Jugador);


protected:
private:
};

#endif // REGLAS_H
