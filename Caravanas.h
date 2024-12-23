#ifndef CARAVANAS_H
#define CARAVANAS_H
#include <string>

using namespace std;

class Caravanas {
    int idcar,preco,nagua,ntripulantes,maxtripulantes;
    int carvida,carataque,velocidade;
    string tipocar;
    string mercadoria[10];
    int x,y;

public:
    int getX() const {
        return x;
    }

    void setX(int x) {
        this->x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        this->y = y;
    }

    Caravanas(int idcar=0,const string& tipocar="combate");
    int getidcar(){return idcar;};
    void setIdcar(int i){idcar=i;};
    int getpreco(){return preco;}
};
#endif //CARAVANAS_H
