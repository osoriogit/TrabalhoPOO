#ifndef CARAVANAS_H
#define CARAVANAS_H
#include <string>

using namespace std;

class Caravanas {
    int idcar,preco,nagua,ntripulantes,maxtripulantes;
    int carvida,carataque,velocidade,naguaMax=100,cargaMax=5;
    char tipocar;
    string mercadoria[10];
    int mercadoriaCidade=1;
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
    void setTipocar(char tipocar) {
        if (tipocar == 'C') {
            preco=10;
            nagua=50;
            naguaMax=200;
            mercadoriaCidade=5;
            cargaMax=40;
            ntripulantes=20;
            maxtripulantes=50;
            carvida=100;
            carataque=100;
            velocidade=1;
            this->tipocar=tipocar;
            mercadoria[9]={"mina"};
        } else if (tipocar == 'M') {
            preco=10;
            nagua=20;
            naguaMax=400;
            mercadoriaCidade=1;
            cargaMax=5;
            ntripulantes=20;
            maxtripulantes=40;
            carvida=100;
            carataque=100;
            velocidade=1;
            this->tipocar=tipocar;
            mercadoria[9]={"cpandora"};
        }else if (tipocar == 'S') {
            preco=10;
            nagua=50;
            naguaMax=200;
            mercadoriaCidade=25;
            cargaMax=100;
            ntripulantes=50;
            maxtripulantes=200;
            carvida=300;
            carataque=150;
            velocidade=2;
            this->tipocar=tipocar;
            mercadoria[9]={"tesouro"};
        } else if (tipocar == 'B'){
            preco=999999;
            nagua=0;
            naguaMax=400;
            mercadoriaCidade=1;
            cargaMax=5;
            ntripulantes=40;
            maxtripulantes=40;
            carvida=100;
            carataque=100;
            velocidade=1;
            this->tipocar=tipocar;
            mercadoria[9]={"mina"};
        }
    }

    int getmaxntripulantes() {
        return maxtripulantes;
    }

    void addtripulantes(char value) {
        ntripulantes+=value;
    }

    void perderTripulantes(int perda) {
        ntripulantes-=perda;
    }

    void adicionarTripulantes(int i) {
        ntripulantes+=i;
    }

    Caravanas(char idcar=' ',char tipocar='C');
    char getidcar(){return idcar;};
    void setIdcar(char i){idcar=i;};
    int getpreco(){return preco;}
};
#endif //CARAVANAS_H
