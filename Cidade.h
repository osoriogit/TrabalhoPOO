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

private:
    char nome;
    int nTripulantes;
    int x,y;
    public:
    Cidade(char nome='c',int ntripulantes=10,int ramX=0,int ramY=0);

    void vendeCaravanas(char carname);

};



#endif //CIDADE_H
