//
// Created by tomas on 11/11/2024.
//

#ifndef CIDADE_H
#define CIDADE_H
#include <map>

#include "Caravanas.h"
using namespace std;


class Cidade {
public:
    char getNome() const {
        return nome;
    }

    void setNome(char nome) {
        this->nome = nome;
    }

    int getTripulantes() const {
        return nTripulantes;
    }

    void setTripulantes(int n_tripulantes) {
        nTripulantes = n_tripulantes;
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

    int sellmercadoria(char value) {
        if (mercadoria-value>0) {
            mercadoria = mercadoria-value;
            return value;
        }
        return -1;
    }

    int compramercadoria(int nmercadoria,int preco) {
        mercadoria +=nmercadoria;
        return nmercadoria*preco;
    }

    int compraTripulantes(char value) {
        nTripulantes-=value;
        return -value;
    }

private:
    char nome;
    int nTripulantes;
    int x,y;
    int mercadoria=100;
    public:
    Cidade(char nome='c',int ntripulantes=10000,int ramX=0,int ramY=0);

    void vendeCaravanas(char carname);

};



#endif //CIDADE_H
