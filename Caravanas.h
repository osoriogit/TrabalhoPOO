#ifndef CARAVANAS_H
#define CARAVANAS_H
#include <string>

using namespace std;

class Caravanas {
    int idcar,preco,nagua,ntripulantes,maxtripulantes;
    int carvida,carataque,velocidade;
    char tipocar;
    string mercadoria[10];
    int mercadoriaCidade=0;
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

    int getnagua() {
        return nagua;
    }

    int getntripulantes() {
        return ntripulantes;
    }

    int getcarvida() {
        return carvida;
    }

    int getcarataque() {
        return carataque;
    }

    int getvelocidade() {
        return velocidade;
    }

    string getmercadoria(int ia) {
        return mercadoria[ia];
    }

    void novamercadoria(int quilos) {
        mercadoriaCidade +=quilos;
    }

    int getmercadoriaCidade() {
        return mercadoriaCidade;
    }

    int sellmercadoria(int i) {
        if(mercadoriaCidade==0) {
            int a=mercadoriaCidade;
            mercadoriaCidade=0;
            return a;
        }
        if(i<=mercadoriaCidade) {
            mercadoriaCidade-=i;
            return i;
        } else {return -1;}
    }

    Caravanas(char idcar=' ',char tipocar='C');
    char getidcar(){return idcar;};
    void setIdcar(char i){idcar=i;};
    int getpreco(){return preco;}
};
#endif //CARAVANAS_H
