#ifndef USER_H
#define USER_H
#include <iostream>
#include <ostream>
#include <string>
#include "Caravanas.h"
#include "Cidade.h"

using namespace std;

class User {
    int iduser;
    int moedas;
    int ncars=0;
    int x,y;
    Caravanas *usercars;
public:
    User(int iduser,int moedas,int nmaxcars);
    int getiduser();
    int getmoedas();
    int getncars();
    Caravanas getusercars(int i);
    void setncars(int n);
    void setusercars(Caravanas& carname);
    void setmoedas(int nmoedas);
    bool comprarusercar(Caravanas car);
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
    ~User();

    void setusercar(const Caravanas & caravanas, int ic_ncaravana) {
        usercars[ic_ncaravana] = caravanas;
    }

    void addmoedas(int moedas) {
        this->moedas += moedas;
    }

    void destructc(int i,int max) {
        Caravanas CaravanaTemp(-1,'T');
        CaravanaTemp=usercars[max-1];
        usercars[max-1]=usercars[i];
        usercars[i]=CaravanaTemp;
    }
};



#endif //USER_H
