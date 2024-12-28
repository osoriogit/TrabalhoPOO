#ifndef BUFFER_H
#define BUFFER_H



#include <iostream>
using namespace std;

class Buffer {
public:
    char * getMatriz() const {
        return matriz;
    }

    int getLinhas() const {
        return linhas;
    }

   int getColunas() const {
        return colunas;
    }

    char getpos(int x, int y) {
        char c = matriz[x + y * colunas];
        return c;
    }

private:
    char *matriz;
    int linhas;
    int colunas;

public:
    Buffer(int linhas=0, int colunas=0);

    char & devolveMatriz(int x, int y) const;

    void escreve(int x, int y, char cr);

    ~Buffer();
};
ostream& operator<<(ostream& os, const Buffer& b);




#endif //BUFFER_H
