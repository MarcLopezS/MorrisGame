#ifndef TABLERO_H
#define TABLERO_H

//#include "Ficha.h"
#include "Jugador.h"
//#include "Reglas.h"

const int MAX_TABLERO = 7;

class Tablero
{
public:
    Tablero();
    virtual ~Tablero();

    void modoTest();

    void inicializarTablero();

    //mostrar pistas en modo con ayuda
    void showPistas();

    void setFicha(Jugador, int, int);

    Ficha getFicha(int, int);

    bool moverFicha(Jugador jugador); //Hacer clase ficha?

    int cinFila();
    int cinColumna(int);

    bool moverHoriz(Ficha);
    bool moverHoriz(Ficha, int, int);
    bool moverVert(Ficha);
    bool moverVert(Ficha, int, int);

    void setFichaDefecto(int, int);

    void printTablero();

    bool posicionLibre(int x, int y);

    bool checkMolino(Ficha, Jugador);
    bool eliminarFichaMolino(int, int, Jugador);

    int comprovarMolinoHor(int i, Ficha ficha, Jugador player);
    int comprovarMolinoVert(int i, Ficha ficha, Jugador player);

    int comprovarFichasJugador(Jugador);
    int playerBlocked(Jugador);

protected:
private:
    Ficha tablero[MAX_TABLERO][MAX_TABLERO];
};

#endif // TABLERO_H
