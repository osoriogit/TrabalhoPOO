#ifndef SIMULADOR_H
#define SIMULADOR_H
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "buffer.h"
#include "Cidade.h"
#include "Montanhas.h"
#include "User.h"
#include <fstream>
#include <string.h>
#include "item.h"

#include "item.h"
using namespace std;

class Simulador {
    //intens
    int timeEntreItens{}, duracaoItem{}, maxItens{};
    //deserto
    int dColunas{}, dLinhas{}, nMontanhas{};
    //cidades
    int nCidades{}, nMercadorias{};
    int precoMercadoriaVenda{}, precoMercadoriaComprar{}, nTripulantes{};//preco venda, preco compra
    string nomeCidades;
    Cidade *cidades;
    Montanhas *montanhas;
    Caravanas *caravanas;
    Buffer saves[10];
    int nsaves=0;
    int *posicaoAutocaravanasInicial;
    User *user;
    item *itens;
    int runvalid=0;
    int remake=0;
    Buffer *buffer;
    int* posicoes;

    //caravanas
    int nCaravanas{}, precoCaravanas{};//preco caravanas
    int nCaravanasVendidas=0;
    //user e barbaros
    int timeEntreBarbaros{}, duracaoBarbaros{}, moedasInicias{};

public:
    Simulador();

    int getTimeEntreItens() const;          void setTimeEntreItens(int timeEntreItens);
    int getDuracaoItem() const;             void setDuracaoItem(int duracaoItem);
    int getMaxItens() const;                void setMaxItens(int maxItens);
    int getDColunas() const;                void setDColunas(int dColunas);
    int getDLinhas() const;                 void setDLinhas(int dLinhas);
    int getNMontanhas() const;              void setNMontanhas(int nMontanhas);
    int getNCidades() const;                void setNCidades(int nCidades);
    int getNMercadorias() const;            void setNMercadorias(int nMercadorias);
    int getPrecoMercadoriaVenda() const;    void setPrecoMercadoriaVenda(int precoMercadoriaVenda);
    int getPrecoMercadoriaComprar() const;  void setPrecoMercadoriaComprar(int precoMercadoriaComprar);
    int getNtripulantes() const;            void setNtripulantes(int ntripulantes);
    const string &getNomeCidades() const;   void setNomeCidades(const string &nomeCidades);
    Cidade *getCidade() const;              void setCidade(Cidade *cidade);
    Buffer *getBuffer() const;              void setBuffer(Buffer *b);
    int getNCaravanas() const;              void setNCaravanas(int nCaravanas);
    int getPrecoCaravanas() const;          void setPrecoCaravanas(int precoCaravanas);
    Caravanas *getCaravanas() const;        void setCaravanas(Caravanas *caravanas);
    int getTimeEntreBarbaros() const;       void setTimeEntreBarbaros(int timeEntreBarbaros);
    int getDuracaoBarbaros() const;         void setDuracaoBarbaros(int duracaoBarbaros);
    int getMoedasInicias() const;           void setMoedasInicias(int moedasInicias);

    void escreveMapa();
    int* gerarPosicoesMatriz(int linhas, int colunas);

    void escreveBuffer();

    void removerParesNegativos(int* arr, int tamanho);

    int corvertor(char a);
    void escreveData() const;

    ~Simulador();

    int getremake() {
        return remake;
    }

    void setremake(int i) {
        remake = i;
    }

    bool isLetraMinusculaChar(char getpos) {
        return ((getpos >= 'a' && getpos <= 'z')&&(getpos!='m'));
    }

    void executaComando(const string& linha);
    bool isNumeroPositivo(const string& str);
    bool isLetraMinuscula(const string& letra);
    bool isNumero0_9(int num);
    bool verificaComando(const string &linha);

    void combate();

    void run();

};
#endif //SIMULADOR_H
