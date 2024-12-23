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
Caravanas User::getusercars() {
    return *usercars;
}

void User::setncars(int n) {
    this->ncars=n;
}
void User::setusercars(Caravanas& carname) {
    usercars[getncars()]=carname;
    setncars(getncars()+1);

}
void User::setmoedas(int nmoedas) {
    this->moedas = nmoedas;
}
bool User::comprarusercar(Caravanas carname,Cidade cidadename) {
    if (getmoedas() >= carname.getpreco()) {
        cidadename.vendecaravanas(carname);
        setmoedas(getmoedas()-carname.getpreco());
        setusercars(carname);
        return true;
    }
    return false;
}
User::~User() {
        delete[] usercars;

}