#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Simulador.h"

#include <map>
#include <cctype>
#include <algorithm>

Simulador::Simulador(){

    map<string, int*> mapping = {
            {"linhas", &dLinhas},
            {"colunas", &dColunas},
            {"moedas", &moedasInicias},
            {"instantes_entre_novos_itens", &timeEntreItens},
            {"duração_item", &duracaoItem},
            {"max_itens", &maxItens},
            {"preço_venda_mercadoria", &precoMercadoriaVenda},
            {"preço_compra_mercadoria", &precoMercadoriaComprar},
            {"preço_caravana", &precoCaravanas},
            {"instantes_entre_novos_barbaros", &timeEntreBarbaros},
            {"duração_barbaros", &duracaoBarbaros},
            {"numero_de_montanhas", &nMontanhas},
            {"numero_de_cidades", &nCidades},
            {"numero_de_mercadorias", &nMercadorias},
            {"numero_de_caravanas", &nCaravanas},
            {"numero_de_tripulantes", &nTripulantes}
    };
    //pedir isto no ficheiro

    string linha, palavra;

    int num;
    string nomeFicheiro,comando;
    std::cout << "Comando para executar (config mapa.txt):"<<endl;
    std::cin >> comando >> nomeFicheiro;

    if (comando != "config") {
        std::cerr << "Comando invalido." << std::endl;
        exit (-505);
    }
    ifstream f(nomeFicheiro);
    if(f){
        while(getline(f, linha)){
            istringstream is(linha);
            if (is >> palavra && is >> num) {
                if (mapping.find(palavra) != mapping.end()) {
                    *(mapping[palavra]) = num;
                } else {
                    cerr << "Chave invalida: " << palavra << endl;
                }
            }
        }
    }
    if ((nCaravanas+nCidades+nMontanhas)>(dLinhas*dColunas)) {
        cerr << "Erro ao alocar memoria!" << endl;
        exit(1);
    }
    int pC=0;//posConter
    posicoes=new int[dLinhas*dColunas];
    posicoes=gerarPosicoesMatriz(dColunas,dLinhas);
    /*for (int i = 0; i < dLinhas * dColunas; ++i) {
          std::cout <<posicoes[i * 2]<< posicoes[i * 2 + 1];
      }*/
    posicaoAutocaravanasInicial=new int [nCaravanas];
    cidades= new Cidade[nCidades];
    for (int i = 0; i < nCidades; ++i) {
        int randomX=posicoes[pC*2];
        posicoes[0]=-1;
        int randomY=posicoes[pC*2+1];
        posicoes[1]=-1;
        pC++;
        //std::cout << randomY;
        cidades[i].setNome('c');
        cidades[i].setX(randomX);
        cidades[i].setY(randomY);
        cidades[i].setTripulantes(nTripulantes);

    }

    caravanas=new Caravanas[nCaravanas];
    for (int i = 0; i < nCaravanas; ++i) {
        int randomX=posicoes[pC*2];
        posicoes[0]=-1;
        int randomY=posicoes[pC*2+1];
        posicoes[1]=-1;
        pC++;
        caravanas[i].setIdcar(('A'+i));
        caravanas[i].setX(randomX);
        caravanas[i].setY(randomY);
    }

    montanhas= new Montanhas[nMontanhas];
    for (int i = 0; i < nMontanhas; ++i) {
        int randomX=posicoes[pC*2];
        posicoes[0]=-1;
        int randomY=posicoes[pC*2+1];
        posicoes[1]=-1;
        pC++;
        montanhas[i].setX(randomX);
        montanhas[i].setY(randomY);
    }

    user=new User(1,moedasInicias,nCaravanas);
    user->setX(posicoes[pC*2]);
    user->setY(posicoes[pC*2+1]);
    buffer= new Buffer(dLinhas,dColunas);

    escreveData();
    escreveMapa();
    f.close();
}
int* Simulador::gerarPosicoesMatriz(int linhas, int colunas) {
    int dLinhas = linhas * colunas; // Número total de posições
    int* cordenadasCidade = new int[dLinhas * 2]; // Cada posição armazena um par (linha, coluna)

    // Gerar todas as posições da matriz
    int count = 0;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cordenadasCidade[count * 2] = i;   // Linha
            cordenadasCidade[count * 2 + 1] = j; // Coluna
            ++count;
        }
    }

    // Embaralhar as posições para torná-las aleatórias
    std::srand(std::time(0));
    for (int i = 0; i < dLinhas; ++i) {
        int swapIndex = std::rand() % dLinhas;

        // Trocar pares de coordenadas
        std::swap(cordenadasCidade[i * 2], cordenadasCidade[swapIndex * 2]);
        std::swap(cordenadasCidade[i * 2 + 1], cordenadasCidade[swapIndex * 2 + 1]);
    }

    return cordenadasCidade; // Retorna o array
}

void Simulador::escreveMapa(){
    //escreve deserto
    for (int yi = 0; yi < dLinhas; ++yi) {
        for (int xi = 0; xi < dColunas; ++xi) {
            buffer->escreve(xi,yi,'.');
        }
    }
    //escreveCidades
    for (int i = 0; i < getNCidades(); ++i) {
        char tempc=cidades[i].getNome() ;
        int tempx=cidades[i].getX();
        int tempy=cidades[i].getY();
       buffer->escreve(tempx,tempy,tempc);
    }
    //escreveCaravanas
    for (int i = 0; i < getNCaravanas(); ++i) {
        char tempc=caravanas[i].getidcar() ;
        int tempx=caravanas[i].getX();
        int tempy=caravanas[i].getY();
        buffer->escreve(tempx,tempy,tempc);
    }
    //escreveMontanhas
    for (int i = 0; i < getNMontanhas(); ++i) {
        int tempx=montanhas[i].getX();
        int tempy=montanhas[i].getY();
        buffer->escreve(tempx,tempy,'m');
    }
    //write user
    int tmpx=caravanas->getX();
    int tmpy=caravanas->getY();
    buffer->escreve(tmpx,tmpy,'U');
    //imprimebuffer
    std::cout << buffer[0];
}

void Simulador::escreveData() const {
    cout << "Linhas: " << dLinhas << endl;
    cout << "Colunas: " << dColunas << endl;
    cout << "Moedas: " << moedasInicias << endl;
    cout << "Instantes entre novos itens: " << timeEntreItens << endl;
    cout << "Duracao do item: " << duracaoItem << endl;
    cout << "Maximo de itens: " << maxItens << endl;
    cout << "Preco de venda da mercadoria: " << precoMercadoriaVenda << endl;
    cout << "Preco de compra da mercadoria: " << precoMercadoriaComprar << endl;
    cout << "Preco da caravana: " << precoCaravanas << endl;
    cout << "Instantes entre novos barbaros: " << timeEntreBarbaros << endl;
    cout << "Duracao dos barbaros: " << duracaoBarbaros << endl;
    cout << "Numero de montanhas: " << nMontanhas << endl;
    cout << "Numero de cidades: " << nCidades << endl;
    cout << "Numero de mercadorias: " << nMercadorias << endl;
    cout << "Numero de caravanas: " << nCaravanas << endl;
    cout << "Numero de tripulantes: " << nTripulantes << endl;
}

int Simulador::getTimeEntreItens() const {
    return timeEntreItens;
}

void Simulador::setTimeEntreItens(int tEI){
    timeEntreItens = tEI;
}

int Simulador::getDuracaoItem() const {
    return duracaoItem;
}

void Simulador::setDuracaoItem(int dI) {
    duracaoItem = dI;
}

int Simulador::getMaxItens() const {
    return maxItens;
}

void Simulador::setMaxItens(int mI) {
    maxItens = mI;
}

int Simulador::getDColunas() const {
    return dColunas;
}

void Simulador::setDColunas(int dC) {
    dColunas = dC;
}

int Simulador::getDLinhas() const {
    return dLinhas;
}

void Simulador::setDLinhas(int dL) {
    dLinhas = dL;
}

int Simulador::getNMontanhas() const {
    return nMontanhas;
}

void Simulador::setNMontanhas(int nM) {
    nMontanhas = nM;
}

int Simulador::getNCidades() const {
    return nCidades;
}

void Simulador::setNCidades(int nC) {
    nCidades = nC;
}

int Simulador::getNMercadorias() const {
    return nMercadorias;
}

void Simulador::setNMercadorias(int nM) {
    nMercadorias = nM;
}

int Simulador::getPrecoMercadoriaVenda() const {
    return precoMercadoriaVenda;
}

void Simulador::setPrecoMercadoriaVenda(int pMV) {
    precoMercadoriaVenda = pMV;
}

int Simulador::getPrecoMercadoriaComprar() const {
    return precoMercadoriaComprar;
}

void Simulador::setPrecoMercadoriaComprar(int pMC) {
    precoMercadoriaComprar = pMC;
}

int Simulador::getNtripulantes() const {
    return nTripulantes;
}

void Simulador::setNtripulantes(int nT) {
    Simulador::nTripulantes = nT;
}

const string &Simulador::getNomeCidades() const {
    return nomeCidades;
}

void Simulador::setNomeCidades(const string &nC) {
    nomeCidades = nC;
}

Cidade *Simulador::getCidade() const {
    return cidades;
}

void Simulador::setCidade(Cidade *c) {
    cidades = c;
}
Buffer *Simulador::getBuffer() const {
    return buffer;
}

void Simulador::setBuffer(Buffer *b) {
    buffer = b;
}

int Simulador::getNCaravanas() const {
    return nCaravanas;
}

void Simulador::setNCaravanas(int nC) {
    nCaravanas = nC;
}

int Simulador::getPrecoCaravanas() const {
    return precoCaravanas;
}

void Simulador::setPrecoCaravanas(int pC) {
    precoCaravanas = pC;
}

Caravanas *Simulador::getCaravanas() const {
    return caravanas;
}

void Simulador::setCaravanas(Caravanas *car) {
    caravanas = car;
}

int Simulador::getTimeEntreBarbaros() const {
    return timeEntreBarbaros;
}

void Simulador::setTimeEntreBarbaros(int tEB) {
    timeEntreBarbaros = tEB;
}

int Simulador::getDuracaoBarbaros() const {
    return duracaoBarbaros;
}

void Simulador::setDuracaoBarbaros(int dB) {
    duracaoBarbaros = dB;
}

int Simulador::getMoedasInicias() const {
    return moedasInicias;
}

void Simulador::setMoedasInicias(int mI) {
    moedasInicias = mI;
}

int Simulador::corvertor(char a) {
    if (isdigit(a)) {
        int numero = a - '0';
        return numero;
    }else{
        return -1;
    }
}

Simulador::~Simulador() {
    delete[] cidades;
    delete[] posicoes;
    delete[] montanhas;
    delete[] caravanas;
    delete user;
    delete buffer;
}

void Simulador::executaComando(const string& linha) {
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
            cout << "\nComando 'config, mas ja foi executado no inicio do programa.'" << endl;
            break;
        case 2:
            // void termina();
            cout << "\nComando 'sair'" << endl;
            break;
        case 3:
            // exec <nomeFicheiro> - Lê comandos do ficheiro de texto designado por nomeFicheiro, um por linha, e
            //executa-os. Este comando é muito útil para executar um conjunto de comandos predefinido, previamente
            //gravados num ficheiro. Permite, assim, poupar imenso tempo durante os testes, carregando uma
            //determinada sequência de comandos reproduzível. Cada linha do ficheiro tem um comando com a
            //mesma estrutura e texto dos comandos que se digitam através do teclado, portanto com a mesma
            //interpretação e processamento, partilhando o código associado a estas tarefas e diferindo apenas de
            //onde vêm os caracteres que o compõem (do teclado vs. de um ficheiro).
            // void executaExec();
            cout << "\nComando 'exec'" << endl;
            break;
        case 4:
            // prox <n> – Termina a fase de indicação dos comandos e vai ter início a fase de execução de comandos
            //pendentes e comportamentos automáticos. n é opcional, e maior que 0, e indica o número de instantes a
            //avançar. Se avançar mais do que um instante, deverá ser apresentado o mapa e outras informações em
            //cada um dos instantes.
            // void executaProx(stoi(partes[1]));
            cout << "\nComando 'prox'" << endl;
            break;
        case 5:
            // comprac <C> <T> - Compra, na cidade C uma caravana do tipo T. T indica o tipo da caravana: C –
            //Comércio, M – Militar, S – Secreta.
            // void executaComprac(partes[1], partes[2]);
            cout << "\nComando 'comprac'" << endl;
            break;
        case 6:
            // precos – Lista os preços das mercadorias (igual em todas as cidades).
            // void listaPrecos();
            cout << "\nComando 'precos'" << endl;
            break;
        case 7:
            // cidade <C> - Lista conteúdo da cidade C (caravanas existentes)
            // void listaCidadeInfo(partes[1]);
            cout << "\nComando 'cidade'" << endl;
            break;
        case 8:
            // caravana <C> - mostra a descrição da caravana C (todos os detalhes)
            // void executaCaravana(stoi(partes[1]));
            cout << "\nComando 'caravana'" << endl;
            break;
        case 9:
            // compra <N> <M> - Compra M toneladas de mercadorias para a caravana N, o qual deverá estar numa
            //cidade nessa altura
            // void executaCompra(stoi(partes[1]), stoi(partes[2]));
            cout << "\nComando 'compra'" << endl;
            break;
        case 10:
            // vende <N> - Vende toda a mercadoria da caravana N, o qual deverá estar numa cidade
            // void executaVende(stoi(partes[1]));
            cout << "\nComando 'vende'" << endl;
            break;
        case 11:
            // move <N> <X> - Move a caravana com o número N uma posição na direção X: D (direita), E (esquerda),
            //C (cima), B (baixo) e as diagonais, na mesma lógica: CE (cima-esquerda), CD (cima-direita), BE (baixo-
            //esquerda), BD (baixo-direita)
            // void executaMove(stoi(partes[1]), partes[2]);
            cout << "\nComando 'move'" << endl;
            break;
        case 12:
            // auto <N> - Coloca a caravana N em “auto-gestão”, ou seja, a caravana passa a ter o seu comportamento
            //automático, seja ele qual for, mesmo que seja “ficar parado”
            // void executaAuto(stoi(partes[1]));
            cout << "\nComando 'auto'" << endl;
            break;
        case 13:
            // stop <N> - A caravana com o número N pára o comportamento automático
            // void executaStop(stoi(partes[1]));
            cout << "\nComando 'stop'" << endl;
            break;
        case 14:
            // barbaro <l> <c> - Cria uma caravana barbara nas coordenadas (l, c)
            // void criaCaravanaBarbaro(stoi(partes[1]), stoi(partes[2]));
            cout << "\nComando 'barbaro'" << endl;
            break;
        case 15:
            // areia <l> <c> <r> - Cria uma tempestade de areia na posição l, c com raio r posições (é um quadrado de
            //posições)
            // void executaAreia(stoi(partes[1]), stoi(partes[2]), stoi(partes[3]));
            cout << "\nComando 'areia'" << endl;
            break;
        case 16:
            // moedas <N> - Acrescenta N moedas ao jogador (pode ser um valor negativo). Isto serve para testes
            // void executaMoedas(stoi(partes[1]));
            cout << "\nComando 'moedas'" << endl;
            break;
        case 17:
            // tripul <N> <T> - Compra T tripulantes para a caravana N desde que essa caravana esteja numa cidade
            // void executaTripul(stoi(partes[1]), stoi(partes[2]));
            cout << "\nComando 'tripul'" << endl;
            break;
        case 18:
            // saves <nome> - Faz uma cópia do estado do buffer (aspeto visual apenas – não os dados do
            //simulador) usado para apresentar a informação apresentada no turno atual. A cópia é armazenada em
            //memória associando-o ao nome indicado
            // void executaSaves(partes[1]);
            cout << "\nComando 'saves'" << endl;
            break;
        case 19:
            // loads <nome> - Recupera a cópia do buffer previamente armazenado em memória com o nome indicado,
            //permitindo assim ver um determinado instante anterior (para comparação ou que for). Esta operação não
            //altera o estado da simulação atual
            // void executaLoads(partes[1]);
            cout << "\nComando 'loads'" << endl;
            break;
        case 20:
            // lists - Lista os nomes das cópias do buffer existentes
            // void listaNomesCopias();
            cout << "\nComando 'lists'" << endl;
            break;
        case 21:
            // dels <nome> - Apaga a cópia do buffer em memória associada ao nome indicado
            // void executaDels(partes[1]);
            cout << "\nComando 'dels'" << endl;
            break;
        case 22:
            // terminar – Termina a simulação, sendo apresentada a pontuação. O simulador regressa à fase 1, onde
            //o utilizador pode iniciar nova simulação, ou sair do programa
            // void executaTerminar();
            cout << "\nComando 'terminar'" << endl;
            break;
        default:
            cout << "\nComando nao existe!" << endl;
            break;
    }
}

// Função para verificar se uma string representa um número inteiro positivo
bool Simulador::isNumeroPositivo(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return !str.empty();
}

bool Simulador::isLetraMinuscula(const string& letra) {
    return (letra[0] >= 'a' && letra[0] <= 'z');
}

bool Simulador::isNumero0_9(int num) {
    return (num >= 0 && num <= nCaravanas);
}

bool Simulador::verificaComando(const string& linha) {
    // Mapeamento dos comandos válidos e número de parâmetros esperados (-1 para parâmetros variáveis)
    map<string, int> comandos = {
            {"config",   1},
            {"sair",     0},
            {"exec",     1},
            {"prox",     -1},
            {"comprac",  2},
            {"precos",   0},
            {"cidade",   1},
            {"caravana", 1},
            {"compra",   2},
            {"vende",    1},
            {"move",     2},
            {"auto",     1},
            {"stop",     1},
            {"barbaro",  2},
            {"areia",    3},
            {"moedas",   1},
            {"tripul",   2},
            {"saves",    1},
            {"loads",    1},
            {"lists",    0},
            {"dels",     1},
            {"terminar", 0}
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
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/
    if (comando == "config" && parametrosRecebidos == 1) {
        string nome = partes[1];
        if (nome.empty()) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if( comando == "sair" && parametrosRecebidos == 0) {
        cout << "\n\nComando invalido!" << endl;
        return false;
    } else if (comando == "exec" && parametrosRecebidos == 1) {
        string nome = partes[1];
        if (nome.empty()) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/
    else if (comando == "prox" && parametrosRecebidos == 1) {
        if (!isNumeroPositivo(partes[1])) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "comprac" && parametrosRecebidos == 2) {
        string tipo1 = partes[1];
        string tipo2 = partes[2];
        if(!isLetraMinuscula(tipo1)){
            if (tipo2 != "C" && tipo2 != "M" && tipo2 != "S") {
                cout << "\n\nComando invalido!" << endl;
                return false;
            }
        }
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/
    } else if (comando == "precos" && parametrosRecebidos == 0) {
        cout << "\n\nComando invalido!" << endl;
        return false;
    } else if (comando == "cidade" && parametrosRecebidos == 1) {
        string tipo = partes[1];
        if (!isLetraMinuscula(tipo)) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "caravana" && parametrosRecebidos == 1) {
        string tipo = partes[1];
        if (!isNumeroPositivo(tipo) || !isNumero0_9(stoi(tipo))) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "compra" && parametrosRecebidos == 2) {
        string tipo1 = partes[1];
        string tipo2 = partes[2];
        if (!isNumeroPositivo(tipo2) && (!isNumeroPositivo(tipo1) || !isNumero0_9(stoi(tipo1)))) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "vende" && parametrosRecebidos == 1) {
        string tipo = partes[1];
        if (!isNumeroPositivo(tipo) || !isNumero0_9(stoi(tipo))) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/
    } else if (comando == "move" && parametrosRecebidos == 2) {
        string direcao = partes[2];
        vector<string> direcoesValidas = {"D", "E", "C", "B", "CE", "CD", "BE", "BD"};
        if (find(direcoesValidas.begin(), direcoesValidas.end(), direcao) == direcoesValidas.end()) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/
    }else if (comando == "auto" && parametrosRecebidos == 1) {
        string tipo = partes[1];
        if (!isNumeroPositivo(tipo) || !isNumero0_9(stoi(tipo))) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "stop" && parametrosRecebidos == 1) {
        string tipo = partes[1];
        if (!isNumeroPositivo(tipo) || !isNumero0_9(stoi(tipo))) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "barbaro" && parametrosRecebidos == 2) {
        string tipo1 = partes[1];
        string tipo2 = partes[2];
        // [IMPORTANTE]: Also verificar se o conteudo da coordenada é um ponto
        if(!isNumeroPositivo(tipo1) || !isNumeroPositivo(tipo2)) {
            if ((stoi(tipo1) > dLinhas) || (stoi(tipo2) > dColunas)) {
                cout << "\n\nComando invalido!" << endl;
                return false;
            }
        }
    } else if (comando == "areia" && parametrosRecebidos == 3) {
        string tipo1 = partes[1];
        string tipo2 = partes[2];
        string tipo3 = partes[3];
        if(!isNumeroPositivo(tipo1) || !isNumeroPositivo(tipo2) || !isNumeroPositivo(tipo3)) {
            // numero 3 é um exemplo para a area nao ser muito grande
            if ((stoi(tipo1) > dLinhas) || (stoi(tipo2) > dColunas) || (stoi(tipo3) > 3)) {
                cout << "\n\nComando invalido!" << endl;
                return false;
            }
        }
    } else if (comando == "moedas" && parametrosRecebidos == 1) {
        string tipo = partes[1];
        if (!isdigit(stoi(tipo))) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    }else if (comando == "tripul" && parametrosRecebidos == 2) {
        string tipo1 = partes[1];
        string tipo2 = partes[2];
        if (!isNumeroPositivo(tipo1)  || !isNumero0_9(stoi(tipo1)) || !isNumeroPositivo(tipo2)) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }

    } else if (comando == "saves" && parametrosRecebidos == 1) {
        string nome = partes[1];
        if (nome.empty()) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "loads" && parametrosRecebidos == 1) {
        string nome = partes[1];
        if (nome.empty()) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    }else if (comando == "lists" && parametrosRecebidos == 0) {
        cout << "\n\nComando invalido!" << endl;
        return false;
    } else if (comando == "dels" && parametrosRecebidos == 1) {
        string nome = partes[1];
        if (nome.empty()) {
            cout << "\n\nComando invalido!" << endl;
            return false;
        }
    } else if (comando == "terminar" && parametrosRecebidos == 0) {
        cout << "\n\nComando invalido!" << endl;
        return false;
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/
    cout << "\n\nComando valido!" << endl;
    return true;
}

void Simulador::run() {
    string comando;
    int iteracoes = 0;
    while (true) {
        cout << " Comando: ";
        getline(cin, comando);

        if (comando == "sair") {
            cout << "Programa terminou." << endl;
            break;
        }

        if (Simulador::verificaComando(comando)) {
            Simulador::executaComando(comando);
            iteracoes++;
        }
        cout << iteracoes << endl;
    }
}
