#include "User.h"

User::User(int iduser,int moedas,int nmaxcars) {
    this->iduser = iduser;
    this->moedas = moedas;
    usercars=new Caravanas[nmaxcars];
}
int User::getiduser() {
    return this->iduser;
}
int User::getmoedas() {
    return this->moedas;
}
int User::getncars() {
    return this->ncars;
}
Caravanas User::getusercars(int i) {
    return usercars[i];
}

void User::setncars(int n) {
    this->ncars=n;
}
void User::setusercars(Caravanas& car) {
    usercars[getncars()]=car;
    setncars(getncars()+1);

}
void User::setmoedas(int nmoedas) {
    this->moedas = nmoedas;
}
bool User::comprarusercar(Caravanas car) {
    if (getmoedas() >= car.getpreco()) {
        setmoedas(getmoedas()-car.getpreco());
        setusercars(car);
        return true;
    }
    return false;
}
User::~User() {
        delete[] usercars;

}