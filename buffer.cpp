#include "buffer.h"

Buffer::Buffer(int linhas, int colunas) {
    this->linhas = linhas;
    this->colunas = colunas;

    matriz = new char[linhas*colunas];
}
char & Buffer::devolveMatriz(int x,int y) const{
    return this->matriz[x+y*colunas];
}

void Buffer::escreve(int x, int y, char cr){
    this->matriz[x+y*colunas] = cr;
}
ostream& operator<<(ostream& os, const Buffer& b) {
    os<< endl;;
    for (int yi = 0; yi < b.getLinhas(); ++yi) {
        for (int xi = 0; xi < b.getColunas(); ++xi) {
            os<<b.devolveMatriz(xi,yi);
        }
        os<<endl;
    }
    return os;
}

Buffer::~Buffer(){
    delete[] matriz;
}
