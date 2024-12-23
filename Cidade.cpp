#include "Cidade.h"

#include <iostream>
#include <ostream>

Cidade::Cidade(char nome,int nTripulantes,int ramX,int ramY) {
    this->nome=nome;
    this->nTripulantes=nTripulantes;
    x=ramX;
    y=ramY;

}
void Cidade::vendecaravanas(Caravanas carname) {
    std::cout << "Vendecaravanas com id :" <<carname.getidcar()<<std::endl;

}