#include "Simulador.h"
#include "User.h"
#include "buffer.h"
using namespace std;
//Final commit sure
int main() {
    int operacao=0;
    while (operacao==0){
        Simulador simulador;
        cin.ignore();
        simulador.run();
        operacao=simulador.getremake();
    }
    return 0;
}
//git test