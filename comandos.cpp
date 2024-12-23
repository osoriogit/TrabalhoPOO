#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>

using namespace std;

void executaComando(const string& linha) {
    // Mapeamento de comandos para identificadores únicos
    map<string, int> comandos = {
            {"config", 1}, {"sair", 2}, {"exec", 3}, {"prox", 4},
            {"comprac", 5}, {"precos", 6}, {"cidade", 7}, {"caravana", 8},
            {"compra", 9}, {"vende", 10}, {"move", 11}, {"auto", 12},
            {"stop", 13}, {"barbaro", 14}, {"areia", 15}, {"moedas", 16},
            {"tripul", 17}, {"saves", 18}, {"loads", 19}, {"lists", 20},
            {"dels", 21}, {"terminar", 22}
    };

    // Separar o comando e os parâmetros
    istringstream iss(linha);
    vector<string> partes;
    string token;
    while (iss >> token) {
        partes.push_back(token);
    }

    if (partes.empty()) {
        cout << "Erro: comando vazio!" << endl;
        return;
    }

    string comando = partes[0];

    // Obter identificador único do comando
    int identificadorComando = comandos[comando];

    // Switch para tratar os comandos
    switch (identificadorComando) {
        case 1:
            // void executaConfig();
            cout << "\nComando 'config'" << endl;
            break;
        case 2:
            // void executaSair();
            cout << "\nComando 'sair'" << endl;
            break;
        case 3:
            // void executaExec();
            cout << "\nComando 'exec'" << endl;
            break;
        case 4:
            // void executaProx();
            cout << "\nComando 'prox'" << endl;
            break;
        case 5:
            // void executaComprac();
            cout << "\nComando 'comprac'" << endl;
            break;
        case 6:
            // void executaPrecos();
            cout << "\nComando 'precos'" << endl;
            break;
        case 7:
            // void executaCidade();
            cout << "\nComando 'cidade'" << endl;
            break;
        case 8:
            // void executaCaravana();
            cout << "\nComando 'caravana'" << endl;
            break;
        case 9:
            // void executaCompra();
            cout << "\nComando 'compra'" << endl;
            break;
        case 10:
            // void executaVende();
            cout << "\nComando 'vende'" << endl;
            break;
        case 11:
            // void executaMove();
            cout << "\nComando 'move'" << endl;
            break;
        case 12:
            // void executaAuto();
            cout << "\nComando 'auto'" << endl;
            break;
        case 13:
            // void executaStop();
            cout << "\nComando 'stop'" << endl;
            break;
        case 14:
            // void executaBarbaro();
            cout << "\nComando 'barbaro'" << endl;
            break;
        case 15:
            // void executaAreia();
            cout << "\nComando 'areia'" << endl;
            break;
        case 16:
            // void executaMoedas();
            cout << "\nComando 'moedas'" << endl;
            break;
        case 17:
            // void executaTripul();
            cout << "\nComando 'tripul'" << endl;
            break;
        case 18:
            // void executaSaves();
            cout << "\nComando 'saves'" << endl;
            break;
        case 19:
            // void executaLoads();
            cout << "\nComando 'loads'" << endl;
            break;
        case 20:
            // void executaLists();
            cout << "\nComando 'lists'" << endl;
            break;
        case 21:
            // void executaDels();
            cout << "\nComando 'dels'" << endl;
            break;
        case 22:
            // void executaTerminar();
            cout << "\nComando 'terminar'" << endl;
            break;
        default:
            cout << "\nComando nao existe!" << endl;
            break;
    }
}

// Função para verificar se uma string representa um número inteiro positivo
bool isNumeroPositivo(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return !str.empty();
}

bool verificaComando(const string& linha) {
    // Mapeamento dos comandos válidos e número de parâmetros esperados (-1 para parâmetros variáveis)
    map<string, int> comandos = {
            {"config", 1}, {"sair", 0}, {"exec", 1}, {"prox", -1},
            {"comprac", 2}, {"precos", 0}, {"cidade", 1}, {"caravana", 1},
            {"compra", 2}, {"vende", 1}, {"move", 2}, {"auto", 1},
            {"stop", 1}, {"barbaro", 2}, {"areia", 3}, {"moedas", 1},
            {"tripul", 2}, {"saves", 1}, {"loads", 1}, {"lists", 0},
            {"dels", 1}, {"terminar", 0}
    };

    // Separar o comando e os parâmetros
    istringstream iss(linha);
    vector<string> partes;
    string token;
    while (iss >> token) {
        partes.push_back(token);
    }

    if (partes.empty()) {
        cout << "\n\nComando invalido!" << endl;
        return false;
    }

    string comando = partes[0];

    // Verifica se o comando existe
    if (comandos.find(comando) == comandos.end()) {
        cout << "\n\nComando invalido!" << endl;
        return false;
    }

    int numParametros = comandos[comando];
    int parametrosRecebidos = partes.size() - 1;

    // Verificar se o número de parâmetros está correto
    if (numParametros != -1 && parametrosRecebidos != numParametros) {
        cout << "\n\nComando invalido!" << endl;
        return false;
    }

    // Validações específicas
    if (comando == "prox" && parametrosRecebidos == 1) {
        if (!isNumeroPositivo(partes[1])) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "comprac" && parametrosRecebidos == 2) {
        string tipo = partes[2];
        if (tipo != "C" && tipo != "M" && tipo != "S") {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "move" && parametrosRecebidos == 2) {
        string direcao = partes[2];
        vector<string> direcoesValidas = {"D", "E", "C", "B", "CE", "CD", "BE", "BD"};
        if (find(direcoesValidas.begin(), direcoesValidas.end(), direcao) == direcoesValidas.end()) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    }

    cout << "\n\nComando valido!" << endl;
    return true;
}

int main() {
    string input;

    // Loop para testar comandos
    while (true) {
        cout << " Comando: ";
        getline(cin, input);

        if (input == "sair") {
            break;
        }

        if(verificaComando(input)) {
            executaComando(input);
        }
    }

    return 0;
}
