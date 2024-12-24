#ifndef CARAVANAS_H
#define CARAVANAS_H
#include <string>

using namespace std;

class Caravanas {
    int idcar,preco,nagua,ntripulantes,maxtripulantes;
    int carvida,carataque,velocidade;
    char tipocar;
    string mercadoria[10];
    int x,y;

public:
    char getTipocar(){
        return tipocar;
    }
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

    Caravanas(char idcar=' ',char tipocar='C');
    char getidcar(){return idcar;};
    void setIdcar(char i){idcar=i;};
    int getpreco(){return preco;}
};
#endif //CARAVANAS_H
