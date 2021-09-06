#include "../include/Tablero.h"
#include <iostream>
#include <windows.h>

using namespace std;

Tablero::Tablero()
{
    inicializarTablero();
}

Tablero::~Tablero()
{
    //dtor
}

void Tablero::modoTest()
{
    // o----o----o
    tablero[0][0].setValor("X");
    tablero[1][1].setValor("Z");
    tablero[2][2].setValor("X");
    tablero[4][4].setValor("Z");
    tablero[5][5].setValor("X");
    tablero[6][6].setValor("Z");

    tablero[0][6].setValor("Z");
    tablero[1][5].setValor("X");
    tablero[2][4].setValor("X");
    tablero[4][2].setValor("Z");
    tablero[5][1].setValor("X");
    tablero[6][3].setValor("X");

    tablero[3][0].setValor("X");
    tablero[3][1].setValor("Z");
    tablero[3][2].setValor("Z");
    tablero[3][4].setValor("X");
    tablero[3][5].setValor("Z");
    tablero[3][6].setValor("Z");
}

void Tablero::inicializarTablero()
{
    //Fichas sin valor o con un 0 son casillas no validas, es decir, el jugador no puede colocar ficha allí
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            tablero[i][j].setX(i);
            tablero[i][j].setY(j);
        }
    }

    // o----o----o
    tablero[0][0].setValor("o");
    tablero[0][3].setValor("o");
    tablero[0][6].setValor("o");

    // | o--o--o |
    tablero[1][1].setValor("o");
    tablero[1][3].setValor("o");
    tablero[1][5].setValor("o");

    // |   ooo   |
    // o-o-o o-o-o
    // |   ooo   |
    for (int i = 0; i < 3; i++)
    {
        tablero[2][2 + i].setValor("o");
        tablero[3][0 + i].setValor("o");
        tablero[3][4 + i].setValor("o");
        tablero[4][2 + i].setValor("o");
    }

    // | o--o--o |
    tablero[5][1].setValor("o");
    tablero[5][3].setValor("o");
    tablero[5][5].setValor("o");

    // o----o----o
    tablero[6][0].setValor("o");
    tablero[6][3].setValor("o");
    tablero[6][6].setValor("o");

    //valor del centro para determinar limites de columna y fila del centro
    tablero[3][3].setValor("0");
}

void Tablero::setFicha(Jugador player, int x, int y)
{
    tablero[x][y].setValor(player.getSpriteJugador());
    tablero[x][y].setX(x);
    tablero[x][y].setY(y);
}

Ficha Tablero::getFicha(int x, int y)
{
    return tablero[x][y];
}

bool Tablero::moverFicha(Jugador jugador)
{
    int fila = 0;
    int col = 0;
    int x = 0;
    int y = 0;

    bool molino = false;

    cout << "\n\tQue ficha quieres mover? " << endl;
    //x = cinFila();
    //int fila = 0;
    cout << "\n\tFila: ";
    cin >> fila;
    while (fila < 0 || fila > 6)
    {
        printTablero();
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\tFila: ";
        cin >> fila;
    }
    y = cinColumna(fila);

    //comprueba si la ficha pertenece al jugador
    if (jugador.getSpriteJugador() == tablero[x][y].getValor())
    {
        //si la ficha tiene algún movimiento posible
        if (moverHoriz(tablero[x][y]) || moverVert(tablero[x][y]))
        {
            cout << "\n\tDonde quieres mover la ficha? " << endl;
            fila = cinFila();
            col = cinColumna(fila);

            if (moverHoriz(tablero[x][y], fila, col) || moverVert(tablero[x][y], fila, col))
            {
                tablero[fila][col].setValor(jugador.getSpriteJugador());
                tablero[x][y].setValor("o");

                molino = checkMolino(tablero[fila][col], jugador);
            }
        }
        else
        {
            cout << "\n\tEsta ficha no se puede mover. Coge otra\n"
                 << endl;
        }
    }
    else
    {
        cout << "\n\tMovimiento no valido\n"
             << endl;
    }

    return molino;
}

int Tablero::cinFila()
{
    int fila = 0;
    cout << "\n\tFila: ";
    cin >> fila;
    while (fila < 0 || fila > 6)
    {
        printTablero();
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\tFila: ";
        cin >> fila;
    }

    return fila;
}

int Tablero::cinColumna(int fila)
{
    int col = 0;

    cout << "\n\tColumna: ";
    cin >> col;
    while (col < 0 || col > 6)
    {
        printTablero();
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\tFila: " << fila << endl;
        cout << "\n\tColumna: ";
        cin >> col;
    }

    return col;
}

/**************************************************************
 * Comprueba si el movimiento horizontal es valido para las   *
 * coordenadas que el jugador ha puesto                       *
 * ************************************************************/
bool Tablero::moverHoriz(Ficha ficha)
{
    int k = 1;

    int colAuxPos = 0;
    int colAuxNeg = 0;

    if (ficha.getX() == 0 || ficha.getX() == 6)
    {
        k = 3;
    }
    else
    {
        if (ficha.getX() == 1 || ficha.getX() == 5)
        {
            k = 2;
        }
    }

    colAuxNeg = ficha.getY() - k;
    colAuxPos = ficha.getY() + k;

    if (ficha.getY() == 0)
    {
        //si la casilla esta libre
        if (getFicha(ficha.getX(), colAuxPos).getValor() == "o")
        {
            return true;
        }
    }
    else
    {
        if (ficha.getY() == 6)
        {
            //si la casilla esta libre
            if (getFicha(ficha.getX(), colAuxNeg).getValor() == "o")
            {
                return true;
            }
        }
        else
        {
            //si la casilla esta libre
            if (getFicha(ficha.getX(), colAuxPos).getValor() == "o" || getFicha(ficha.getX(), colAuxNeg).getValor() == "o")
            {
                return true;
            }
        }
    }

    return false;
}

bool Tablero::moverHoriz(Ficha ficha, int x, int y)
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
        if (tablero[x][y].getValor() == "o")
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
bool Tablero::moverVert(Ficha ficha)
{
    int i = 1;

    int filaAuxPos = 0;
    int filaAuxNeg = 0;

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

    filaAuxPos = ficha.getX() + i;
    filaAuxNeg = ficha.getX() - i;

    //Se comprueban casos específicos debido a la distancia que hay entre casillas
    // porque crea bugs
    if (ficha.getX() == 4)
    {
        //Caso de la columna del medio
        if (ficha.getY() == 3)
        {
            if (getFicha(filaAuxPos, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }
        else
        {
            if (getFicha(filaAuxNeg, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }
    }

    if (ficha.getX() == 5)
    {
        if (ficha.getY() == 3)
        {
            filaAuxPos = ficha.getX() + 1;
            filaAuxNeg = ficha.getX() - 1;

            if (getFicha(filaAuxPos, ficha.getY()).getValor() == "o" || getFicha(filaAuxNeg, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }
        else
        {
            if (getFicha(filaAuxNeg, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }
    }

    if (ficha.getX() == 2)
    {
        //Caso de la columna del medio
        if (ficha.getY() == 3)
        {
            if (getFicha(filaAuxNeg, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }
        else
        {
            if (getFicha(filaAuxPos, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }
    }

    if (ficha.getX() == 0)
    {
        /*if (ficha.getY() == 3)
        {
            if (getFicha(filaAuxPos, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }*/

        if (getFicha(filaAuxPos, ficha.getY()).getValor() == "o")
        {
            return true;
        }
    }
    else
    {
        if (ficha.getX() == 6)
        {
            /*if (ficha.getY() == 3)
            {
                if (getFicha(filaAuxNeg, ficha.getY()).getValor() == "o")
                {
                    return true;
                }
            }*/

            if (getFicha(filaAuxNeg, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }
        else
        {
            if (filaAuxPos == 7)
            {
                filaAuxPos = 5;
            }

            //si la casilla esta libre
            if (getFicha(filaAuxPos, ficha.getY()).getValor() == "o" || getFicha(filaAuxNeg, ficha.getY()).getValor() == "o")
            {
                return true;
            }
        }
    }

    return false;
}

bool Tablero::moverVert(Ficha ficha, int x, int y)
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
        if (tablero[x][y].getValor() == "o")
        {
            return true;
        }
    }

    return false;
}

void Tablero::setFichaDefecto(int x, int y)
{
    tablero[x][y].setValor("o");
}

void Tablero::printTablero()
{
    cout << "\t\t  0      1   2  3  4   5      6 " << endl;
    cout << "\t\t0 " << tablero[0][0].getValor() << "-------------" << tablero[0][3].getValor() << "-------------" << tablero[0][6].getValor() << endl;

    cout << "\t\t  |             |             |" << endl;
    cout << "\t\t1 |      " << tablero[1][1].getValor() << "------" << tablero[1][3].getValor() << "------" << tablero[1][5].getValor() << "      |" << endl;
    cout << "\t\t  |      |      |      |      |" << endl;
    cout << "\t\t2 |      |   " << tablero[2][2].getValor() << "--" << tablero[2][3].getValor() << "--" << tablero[2][4].getValor() << "   |      |" << endl;
    cout << "\t\t  |      |   |     |   |      |" << endl;
    cout << "\t\t3 " << tablero[3][0].getValor() << "------" << tablero[3][1].getValor() << "---" << tablero[3][2].getValor() << "     " << tablero[3][4].getValor() << "---" << tablero[3][5].getValor() << "------" << tablero[3][6].getValor() << endl;
    cout << "\t\t  |      |   |     |   |      |" << endl;
    cout << "\t\t4 |      |   " << tablero[4][2].getValor() << "--" << tablero[4][3].getValor() << "--" << tablero[4][4].getValor() << "   |      |" << endl;
    cout << "\t\t  |      |      |      |      |" << endl;
    cout << "\t\t5 |      " << tablero[5][1].getValor() << "------" << tablero[5][3].getValor() << "------" << tablero[5][5].getValor() << "      |" << endl;
    cout << "\t\t  |             |             |" << endl;

    cout << "\t\t6 " << tablero[6][0].getValor() << "-------------" << tablero[6][3].getValor() << "-------------" << tablero[6][6].getValor() << endl;
    cout << "\n";
    //TABLERO IDEAL?
    // o-------------o-------------o
    // |             |             |
    // |      o------o------o      |
    // |      |      |      |      |
    // |      |   o--o--o   |      |
    // |      |   |     |   |      |
    // o------o---o     o---o------o
    // |      |   |     |   |      |
    // |      |   o--o--o   |      |
    // |      |      |      |      |
    // |      o------o------o      |
    // |             |             |
    // o-------------o-------------o
}

bool Tablero::posicionLibre(int x, int y)
{
    //falla la comparación, no detecta el caracter del tablero como libre

    return getFicha(x, y).getValor() == "o";
}

bool Tablero::checkMolino(Ficha ficha, Jugador player)
{
    int i = 1;
    int v = 1;
    int molinoA3H = 0;
    int molinoA3V = 0;

    bool molino = false;

    //cout << "Valor X de la ficha: " << ficha.getX() << endl;
    //cout << "Valor Y de la ficha: " << ficha.getY() << endl;

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

    if (ficha.getY() == 0 || ficha.getY() == 6)
    {
        v = 3;
    }
    else
    {
        if (ficha.getY() == 1 || ficha.getY() == 5)
        {
            v = 2;
        }
    }

    //comprovar primero solo la horizontal y luego la vertical
    molinoA3H = comprovarMolinoHor(i, ficha, player);
    molinoA3V = comprovarMolinoVert(v, ficha, player);

    if (molinoA3H == 3 || molinoA3V == 3)
    {
        molino = true;
    }

    molinoA3H = 0;
    molinoA3V = 0;

    return molino;
}

/************************************************
 * La ficha se elimina debido al molino formado *
 * y se deja la posición libre                  *
 * **********************************************/
bool Tablero::eliminarFichaMolino(int x, int y, Jugador player)
{
    if (tablero[x][y].getValor() != player.getSpriteJugador())
    {
        tablero[x][y].setValor("o");
        return true;
    }
    else
    {
        cout << "\n\tNo puedes eliminar una ficha que te pertenece. Selecciona otra ficha\n"
             << endl;
    }

    return false;
}

int Tablero::comprovarMolinoHor(int i, Ficha ficha, Jugador player)
{
    //comprovar primero solo la horizontal y luego la vertical
    int plus = 0;
    int molinoA3H = 0;

    for (int j = 0; j < 3; j++)
    {
        //cout << "He entrado!!!!!!!     " << ficha.getX() << endl;
        if (ficha.getX() == 3)
        {
            if (ficha.getY() > 3)
            {
                plus = 4;
            }

            if (tablero[ficha.getX()][j + plus].getValor() == player.getSpriteJugador())
            {

                molinoA3H++;
            }
        }
        else
        {
            if (ficha.getX() == 1 || ficha.getX() == 5)
            {
                if (tablero[ficha.getX()][1 + i * j].getValor() == player.getSpriteJugador())
                {
                    molinoA3H++;
                }
            }
            else
            {
                if (ficha.getX() == 2 || ficha.getX() == 4)
                {
                    if (tablero[ficha.getX()][j + 2].getValor() == player.getSpriteJugador())
                    {
                        molinoA3H++;
                    }
                }
                else
                {
                    if (tablero[ficha.getX()][i * j].getValor() == player.getSpriteJugador())
                    {
                        molinoA3H++;
                    }
                }
            }
        }
    }

    return molinoA3H;
}

int Tablero::comprovarMolinoVert(int i, Ficha ficha, Jugador player)
{
    //comprovar primero solo la horizontal y luego la vertical
    int plus = 0;
    int molinoA3V = 0;

    for (int j = 0; j < 3; j++)
    {
        if (ficha.getY() == 3 || ficha.getY() == 4 || ficha.getY() == 2)
        {
            if (ficha.getY() == 2 || ficha.getY() == 4)
            {
                plus = 2;
            }

            if (ficha.getY() == 3 && ficha.getX() > 3)
            {
                plus = 4;
            }

            if (tablero[j + plus][ficha.getY()].getValor() == player.getSpriteJugador())
            {
                molinoA3V++;
            }
        }
        else
        {

            if (ficha.getY() == 1 || ficha.getY() == 5)
            {
                if (tablero[1 + i * j][ficha.getY()].getValor() == player.getSpriteJugador())
                {
                    molinoA3V++;
                }
            }
            else
            {
                if (tablero[i * j][ficha.getY()].getValor() == player.getSpriteJugador())
                {
                    molinoA3V++;
                }
            }
        }
    }

    return molinoA3V;
}

int Tablero::comprovarFichasJugador(Jugador player)
{
    int resultado = 0;

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (tablero[i][j].getValor() == player.getSpriteJugador())
            {
                resultado++;
            }
        }
    }

    return resultado;
}

int Tablero::playerBlocked(Jugador player)
{
    int fichasBloqueadas = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (player.getSpriteJugador() == tablero[i][j].getValor())
            {
                if (!moverHoriz(tablero[i][j]) && !moverVert(tablero[i][j]))
                {
                    fichasBloqueadas++;
                }
            }
        }
    }

    return fichasBloqueadas;
}
