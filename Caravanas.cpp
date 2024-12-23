#include "Caravanas.h"
Caravanas::Caravanas(int idcar,const string& tipocar) {
            this->idcar=idcar;
            preco=10;
            nagua=100;
            ntripulantes=10;
            maxtripulantes=10;
            carvida=100;
            carataque=100;
            velocidade=1;
            this->tipocar=tipocar;
            mercadoria[9]={"bomba"};
}