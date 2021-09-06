#include "../include/Ficha.h"

Ficha::Ficha()
{
    posX = NULL;
    posY = NULL;
    valor = "";
}

Ficha::Ficha(int x, int y, string val)
{
    posX = x;
    posY = y;
    valor = val;
}

Ficha::~Ficha()
{
    //dtor
}

void Ficha::setX(int x)
{
    posX = x;
}

void Ficha::setY(int y)
{
    posY = y;
}

void Ficha::setValor(string value)
{
    valor = value;
}

int Ficha::getX()
{
    return posX;
}

int Ficha::getY()
{
    return posY;
}

string Ficha::getValor()
{
    return valor;
}

void Ficha::dead()
{
    posX = NULL;
    posY = NULL;
    valor = "";
}
