#include "../include/Game.h"

#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <iostream> // std::cout, std::endl
#include <windows.h>

using namespace std;

Game::Game()
{
    turnoActual = 0;
    jugador1.setSpriteJugador("X");
    jugador2.setSpriteJugador("Z");
    primeraFase = true;

    filaActual = 0;
    colActual = 0;
    //p1Fichas = 0;
    //p2Fichas = 0;
    tablero.modoTest();
    p1Fichas = tablero.comprovarFichasJugador(jugador1);
    p2Fichas = tablero.comprovarFichasJugador(jugador2);
    fichasRestantesP1 = 0;
    fichasRestantesP2 = 0;
}

Game::~Game()
{
    //dtor
}

void Game::printTitle()
{
    srand(time(0));
    cout << "Bienvenido al juego del Molino (o Morris)\n\n"
         << endl;

    cout << "Para empezar, se decide de manera aleatoria que jugador empieza.\n"
         << "El jugador 1 va a ser el --> 'X' mientras que el jugador 2 es el --> 'Z'\n\n"
         << "Decidid quien va a ser quien y luego se decide quien empieza... (teneis 15 segundos para decidirlo)\n"
         << endl;

    cout << "Tiempo de descuento:\n";
    /*for (int i = 15; i > 0; --i)
    {
        cout << i << endl;
        Sleep(1000);
    }*/

    turnoActual = rand() % 2 + 1;

    cout << "\nEmpieza el jugador " << turnoActual << "\n"
         << endl;

    system("pause");

    system("cls");
}

void Game::printFichasColocadas()
{

    cout << "\tEl Jugador 1 (X) ha colocado " << p1Fichas << " fichas" << endl;
    cout << "\tEl Jugador 2 (Z) ha colocado " << p2Fichas << " fichas\n"
         << endl;
}

void Game::printFichasRestantes()
{
    fichasRestantesP1 = tablero.comprovarFichasJugador(jugador1);
    fichasRestantesP2 = tablero.comprovarFichasJugador(jugador2);
    cout << "\tAl Jugador 1 (X) le quedan " << fichasRestantesP1 << " fichas" << endl;
    cout << "\tAl Jugador 2 (Z) le quedan " << fichasRestantesP2 << " fichas\n"
         << endl;
}

void Game::printTurns(Jugador player)
{

    cout << "\tTurno del jugador " << turnoActual << "\n"
         << endl;

    if (primeraFase)
    {
        cout << "\n\tDonde quieres colocar tu ficha?\n"
             << endl;
    }
}

/* ******************************************* *
 * Función encargada de coger el input del     *
 * usuario e introducir la ficha en el tablero *
 * ******************************************* */
void Game::insertarFilasCol(Jugador player)
{
    int fila = 0;
    int col = 0;

    cout << "\tFila: ";
    cin >> fila;

    while (cin.fail() || fila < 0 || fila > 6)
    {
        system("cls");
        tablero.printTablero();
        cout << "\tNumero no valido\n\n\tIntroduce numero entre 0-6" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\tFila: ";
        cin >> fila;
    }

    cout << "\n\tColumna: ";
    cin >> col;
    while (cin.fail() || col < 0 || col > 6)
    {
        system("cls");
        tablero.printTablero();
        cout << "\tNumero no valido\n\n\tIntroduce numero entre 0-6" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\tFila: " << fila << endl;
        cout << "\n\tColumna: ";
        cin >> col;
    }

    if (tablero.posicionLibre(fila, col))
    {
        tablero.setFicha(player, fila, col);
        //fichaActual = tablero.getFicha(fila, col);
        filaActual = fila;
        colActual = col;
    }
    else
    {
        system("cls");
        tablero.printTablero();
        cout << "\tLa casilla esta ocupada o no es valida" << endl;
        insertarFilasCol(player);
    }
}

void Game::inputEliminar(Jugador player)
{
    int fila = 0;
    int col = 0;

    bool correct = false;

    system("cls");
    tablero.printTablero();

    cout
        << "\tHas formado un Molino! Puedes eliminar una ficha del oponente\n"
        << "\t(eliminar una ficha de un molino solo se puede hacer cuando todas sus fichas forman molinos)" << endl;

    cout << "\n\tIndica la ficha que quieres eliminar (fila, columna)\n"
         << endl;

    do
    {
        cout << "\tFila: ";
        cin >> fila;

        while (cin.fail() || fila < 0 || fila > 6)
        {
            system("cls");
            tablero.printTablero();
            cout << "\tNumero no valido\n\n\tIntroduce numero entre 0-6" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n\tFila: ";
            cin >> fila;
        }

        cout << "\n\tColumna: ";
        cin >> col;
        while (cin.fail() || col < 0 || col > 6)
        {
            system("cls");
            tablero.printTablero();
            cout << "\tNumero no valido\n\n\tIntroduce numero entre 0-6" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n\tFila: " << fila << endl;
            cout << "\n\tColumna: ";
            cin >> col;
        }

        if (tablero.posicionLibre(fila, col))
        {
            cout << "\n\tAqui no hay ninguna ficha. Selecciona otra casilla\n"
                 << endl;
        }
        else
        {
            correct = tablero.eliminarFichaMolino(fila, col, player);
        }

    } while (!correct);
}

void Game::pasarTurno()
{
    if (turnoActual == 1)
    {
        turnoActual = 2;
    }
    else
    {
        turnoActual = 1;
    }
}

bool Game::isPhase1Finished()
{
    if (p1Fichas == 9 && p2Fichas == 9)
    {
        tablero.printTablero();
        cout << "\n\tHa acabado la primera fase! \n\tAhora teneis que mover las fichas que teneis en el tablero por donde podais.\n"
             << endl;
        primeraFase = false;
        return true;
    }

    return false;
}

bool Game::isPhase2Finished()
{
    if (fichasRestantesP1 < 3 || fichasRestantesP2 < 3)
    {
        tablero.printTablero();
        cout << "\n\tSe ha acabado el juego. Los resultados de la partida estan a continuacion: " << endl;
        cout << "\n\tHa ganado el jugador " << turnoActual << endl;
        return true;
    }

    return false;
}

void Game::playPhase1()
{
    printTitle();
    bool molino;

    Jugador player;
    while (!isPhase1Finished())
    {
        molino = false;
        player = (turnoActual == 1 ? jugador1 : jugador2);
        tablero.printTablero();

        printFichasColocadas();
        printTurns(player);
        insertarFilasCol(player);

        turnoActual == 1 ? p1Fichas++ : p2Fichas++;

        molino = tablero.checkMolino(tablero.getFicha(filaActual, colActual), player);
        //mirar si se elimina alguna ficha del oponente por tener molino
        if (molino)
        {
            inputEliminar(player);
        }
        pasarTurno();
        system("cls");
    }
}

void Game::playPhase2()
{
    bool molino;
    Jugador player;
    int fichasRestantes = 0;
    int fichasActuales = 0;

    fichasRestantesP1 = tablero.comprovarFichasJugador(jugador1);
    fichasRestantesP2 = tablero.comprovarFichasJugador(jugador2);

    do
    {
        molino = false;
        player = (turnoActual == 1 ? jugador1 : jugador2);
        fichasActuales = (turnoActual == 1 ? fichasRestantesP1 : fichasRestantesP2);
        tablero.printTablero();
        fichasRestantes = tablero.playerBlocked(player);
        printFichasRestantes();
        printTurns(player);
        moverFicha(player);

        if (fichasRestantes == fichasActuales)
        {
            cout << "\n\t El jugador " << turnoActual << " tiene todas las fichas bloqueadas.\nPor tanto, pasa el turno al otro jugador\n"
                 << endl;
            system("pause");
            pasarTurno();
            system("cls");
            continue;
        }

        molino = tablero.checkMolino(tablero.getFicha(filaActual, colActual), player);

        if (molino)
        {
            inputEliminar(player);
        }

        pasarTurno();
        system("cls");
    } while (!isPhase2Finished());
}

void Game::play()
{
    playPhase1();
    system("pause");
    system("cls");
    playPhase2();

    //cout << "Fichas que le quedan al jugador 1: " << fichasRestantesP1 << endl;
    //cout << "Fichas que le quedan al jugador 2: " << fichasRestantesP2 << endl;
    tablero.printTablero();
}

void Game::moverFicha(Jugador jugador)
{
    int fila = 0;
    int col = 0;
    int x = 0;
    int y = 0;

    cout << "\n\tQue ficha quieres mover? " << endl;
    cout << "\n\tFila: ";
    cin >> x;

    while (cin.fail() || x < 0 || x > 6)
    {
        system("cls");
        tablero.printTablero();
        cout << "\n\tTurno del jugador " << ((jugador.getSpriteJugador() == "X")?"1 ":"2 ") << "(" << jugador.getSpriteJugador() << ")" << endl;
        cout << "\tNumero no valido\n\n\tIntroduce numero entre 0-6" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\tFila: ";
        cin >> x;
    }

    cout << "\tColumna: ";
    cin >> y;
    while (cin.fail() || y < 0 || y > 6)
    {
        system("cls");
        tablero.printTablero();
        cout << "\n\tTurno del jugador " << ((jugador.getSpriteJugador() == "X")?"1 ":"2 ") << "(" << jugador.getSpriteJugador() << ")" << endl;
        cout << "\tNumero no valido\n\n\tIntroduce numero entre 0-6" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\tFila: " << x << endl;
        cout << "\n\tColumna: ";
        cin >> y;
    }

    //Si la ficha que está cogiendo es la suya
    if (tablero.getFicha(x, y).getValor() == jugador.getSpriteJugador())
    {
        if (tablero.moverHoriz(tablero.getFicha(x,y)) || tablero.moverVert(tablero.getFicha(x,y)))
        {
            cout << "\n\tA que casilla la quieres mover? " << endl;
            cout << "\n\tFila: ";
            cin >> fila;

            while (cin.fail() || fila < 0 || fila > 6)
            {
                system("cls");
                tablero.printTablero();
                cout << "\n\tTurno del jugador " << ((jugador.getSpriteJugador() == "X")?"1 ":"2 ") << "(" << jugador.getSpriteJugador() << ")" << endl;
                cout << "\tNumero no valido\n\n\tIntroduce numero entre 0-6" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n\tFicha que quieres mover --> Fila: " << x << " Columna: " << y << endl;
                cout << "\n\tFila: ";
                cin >> fila;
            }

            cout << "\tColumna: ";
            cin >> col;
            while (cin.fail() || col < 0 || col > 6)
            {
                system("cls");
                tablero.printTablero();
                cout << "\n\tTurno del jugador " << ((jugador.getSpriteJugador() == "X")?"1 ":"2 ") << "(" << jugador.getSpriteJugador() << ")" << endl;
                cout << "\tNumero no valido\n\n\tIntroduce numero entre 0-6" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n\tFila: " << fila << endl;
                cout << "\n\tColumna: ";
                cin >> col;
            }

            if (tablero.posicionLibre(fila, col) && (fila == x || col == y))
            {
                tablero.setFicha(jugador, fila, col);
                tablero.setFichaDefecto(x, y);
                fichaActual = tablero.getFicha(fila, col);
                filaActual = fila;
                colActual = col;
            }
            else
            {
                system("cls");
                tablero.printTablero();
                cout << "\n\tTurno del jugador " << ((jugador.getSpriteJugador() == "X")?"1 ":"2 ") << "(" << jugador.getSpriteJugador() << ")" << endl;
                cout << "\tSolo puedes mover la ficha a distancia de una casilla en vertical o en horizontal." << endl;
                moverFicha(jugador);
            }
        }
        else
        {
            system("cls");
            tablero.printTablero();
            cout << "\n\tTurno del jugador " << ((jugador.getSpriteJugador() == "X")?"1 ":"2 ") << "(" << jugador.getSpriteJugador() << ")" << endl;
            cout << "\tNo se puede mover esta ficha. Selecciona otra.\n"
                 << endl;
            moverFicha(jugador);
        }
    }
    else
    {
        system("cls");
        tablero.printTablero();
        cout << "\n\tTurno del jugador " << ((jugador.getSpriteJugador() == "X")?"1 ":"2 ") << "(" << jugador.getSpriteJugador() << ")" << endl;


        if(tablero.getFicha(x,y).getValor() == "o"){//si selecciona una casilla vacía
            cout << "\tEn esta casilla no hay fichas. Selecciona una casilla donde tengas ficha.\n"
             << endl;
        }else{ //si selecciona una casilla del oponente
            cout << "\tNo puedes mover las fichas del oponente. Selecciona una de las tuyas.\n"
             << endl;
        }

        moverFicha(jugador);
    }

    /*cout << "\n\tQue ficha quieres mover? " << endl;
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
*/
}
