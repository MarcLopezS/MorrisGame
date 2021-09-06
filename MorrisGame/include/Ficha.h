#ifndef FICHA_H
#define FICHA_H

#include <string>

using namespace std;

class Ficha
{
public:
    Ficha();
    Ficha(int x, int y, string val);
    virtual ~Ficha();

    void setX(int x);
    void setY(int y);
    void setValor(string value);

    int getX();
    int getY();
    string getValor();

    void dead();

protected:
private:
    string valor;

    int posX;
    int posY;
};

#endif // FICHA_H
