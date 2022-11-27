#include "Includes.h"
#include "Reserva.h"

using namespace std;

const vector<string> listDirections {"up", "down", "left", "right"};
const vector<string> listEspecies {"c", "o", "l", "g", "m"};
const vector<string> listAlimentos {"r", "t", "b", "a"};
const vector<string> listComandos {"animal", "kill", "killid", "food", "feed",
                            "feedid", "nofood", "empty", "see",
                            "info", "n", "anim", "visanim", "store",
                            "restore", "load", "slide", "exit", "help"};
// conta o numero de argumentos inseridos no terminal
int numArgs(stringstream& teste, string& temp ) {
    int cnt{0};
    while(teste >> temp)
        ++cnt;
    return cnt;
}
// divide a linha inserida em strings e guarda num vetor de strings
vector<string> split(const string& line) {
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    // invariant: we have processed characters [original value of i, i)
    while (i != line.size()) {
        // ignore leading blanks
        // invariant: characters in range [original i, current i) are all spaces
        while (i != line.size() && isspace(line.at(i)))
            ++i;

        // find end of next word
        string_size j = i;
        // invariant: none of the characters in range [original j, current j)is a space
        while (j != line.size() && !isspace(line.at(j)))
            j++;

        // if we found some nonwhitespace characters
        if (i != j) {
            // copy from s starting at i and taking j - i chars
            ret.push_back(line.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}
// verifica e devolve as dimensoes da reserva a ser criada
void getReservaDims(int& DimX, int& DimY) {
    string input;
    bool flag = false;
    do {
        cout << "Insira a dimensao da reserva (altura comprimento) ou 0 0 para um tamanho aleatorio: "<< endl;
        getline(cin, input);
        stringstream iss (input);
        string temp{};
        int nArgs = numArgs(iss, temp);
        if(nArgs > 2 || nArgs == 0) {
            cout << "informacao invalida..." << endl;
            continue;
        }
        vector<string> args = split(input);
        if((stoi(args.at(0)) == 0) && (stoi(args.at(1)) == 0)) {
            DimX = 0;
            DimY = 0;
            flag = true;
        }
        if((stoi(args.at(0)) >= 16 && stoi(args.at(0)) <= 500) && (stoi(args.at(1)) >= 16 && stoi(args.at(1)) <= 500)) {
            DimX = stoi(args.at(0));
            DimY = stoi(args.at(1));
            flag = true;
        }
    }while(!flag);
}
// verifica se o comando existe na lista de comandos do programa
bool verificaCmd(const string &cmd){
        bool xpto = find(listComandos.begin(), listComandos.end(), cmd) != listComandos.end();
        if (!xpto)
            cout << "Inseriu mal o primeiro comando!\n";
        return xpto;
}
// verifica se a especie (letra) existe na lista
bool verificaEspecie(string &esp) {
    bool xpto = find(listEspecies.begin(), listEspecies.end(), esp) != listEspecies.end();
    if (!xpto){
        cout << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}
// verifica se o alimento (letra) existe na lista
bool verificaAlimento(string &tipo) {
    bool xpto = find(listAlimentos.begin(), listAlimentos.end(), tipo) != listAlimentos.end();
    if (!xpto){
        cout << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}
// verifica se a direcao existe na lista
bool verificaDirecao(string &dir) {
    bool xpto = find(listDirections.begin(), listDirections.end(), dir) != listDirections.end();
    if (!xpto){
        cout << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}
// verifica se a posição está dentro da reserva e posteriormente, se está associado a alguma coisa
bool verificaXY(const int &posX, const int &posY, const Reserva& reserva) {
    if (posX < 1 || posY < 1) {
        cout << "Inseriu valores invalidos de linhas e/ou colunas \n";
        return false;
    }
    if (posY > reserva.getDimY() || posX > reserva.getDimX() ){
        cout << "Inseriu valores invalidos de linhas e/ou colunas \n";
        return false;
    }
    return true;
}
// verifica se o id está na reserva
bool verificaId(const int &id, const Reserva &reserva) {
    return id == reserva.getId();
}
// verifica se a sintaxe do comando está correta
bool verificaSintaxe(const int nArgs, const int nArgsExp) {
    return nArgs == nArgsExp;
}
// envia para o output uma mensagem
void infoToUser() {
    cout << "O que pretende validar: " << endl;
}
/*bool verificaAnimal(int nArgs, vector<string> &args, Reserva &reserva) {
    if (nArgs == 2) {
        if (!verificaEspecie(args.at(1))) {
            return false;
        }
        // Adicionar coords random
        criaAnimal(args.at(1)[0]);
        cout << "O que pretende validar: " << endl;
        return true;
    }
    if (nArgs == 4) {
        if ( !verificaEspecie(args.at(1)) ) {
            return false;
        }
        if ( !verificaXY(stoi(args.at(2)), stoi(args.at(3)), reserva)) {
            return false;
        }
        criaAnimal(args.at(1)[0], stoi(args.at(2)), stoi(args.at(3)));
        return true;
    }
    cout << "Erro! Numero errado de parametros\n";
    return false;
}*/
// abre o ficheiro
void checkComandoUser(const string& nomeFicheiro) {
    string line;
    fstream myfile;
    myfile.open(nomeFicheiro, ios::in); // in = read mode, on = write mode
    if (myfile.is_open()) {
        cout << "Ficheiro aberto com sucesso!\n";
        while (getline(myfile, line)) {
            // não é necessário escrever no terminal
            cout << line << endl;
        }
        myfile.close();
    }
    else {
        cout << "Erro a abrir o ficheiro!\n";
        return;
    }
}
// comandos
void criaAnimal(char especie, int lin, int col){cout << "A verificar na 2 fase\n";};
void criaAnimal(char especie) {cout << "A verificar na 2 fase\n";}
void killAnimal(int lin, int col){cout << "A verificar na 2 fase\n";};
void killAnimal(int id){cout << "A verificar na 2 fase\n";};
void placeAlimento(char tipo, int lin, int col){cout << "A verificar na 2 fase\n";};
void feedDirectly(int lin, int col, int nut, int tox){cout << "A verificar na 2 fase\n";};
void feedId(int id){cout << "A verificar na 2 fase\n";};
void placeAlimento(char tipo) {cout << "A verificar na 2 fase\n";}
void removeAlimento(int lin, int col){cout << "A verificar na 2 fase\n";};
void removeAlimento(int id){cout << "A verificar na 2 fase\n";};
void deletePos(int lin, int col){cout << "A verificar na 2 fase\n";};
void checkPos(int lin, int col){cout << "A verificar na 2 fase\n";};
void checkId(int id){cout << "A verificar na 2 fase\n";};
void tick(){cout << "A verificar na 2 fase\n";};
void tick(int pausa){cout << "A verificar na 2 fase\n";};
void listIdsReserva(){cout << "A verificar na 2 fase\n";};
void listIdsWindow(){cout << "A verificar na 2 fase\n";};
void store(string nome){cout << "A verificar na 2 fase\n";};
void restore(string nome){cout << "A verificar na 2 fase\n";};
void deslocaAreaViz(string dir, int tamanho){cout << "A verificar na 2 fase\n";};
// recebe os comandos
void getInput(Reserva& reserva) {
    string input{};
    infoToUser();
    getline(cin, input);
    do {
        stringstream iss (input);
        string temp{};
        int nArgs = numArgs(iss, temp);
        if(nArgs > 5) {
            cout << "demasiada informacao..." << endl;
            infoToUser();
            continue;
        }
        if(nArgs < 1) {
            cout << "sem instrucoes..." << endl;
            infoToUser();
            continue;
        }
        vector<string> args = split(input);
        // ################################  VERIFICAÇÕES  ########################################
        if ( !verificaCmd(args.at(0)) ) {
            infoToUser();
            continue;
        }
        // CRIAR ANIMAL
        if ( args.at(0) == "animal") {
           if (!verificaEspecie(args.at(1))) {
               infoToUser();
               continue;
           }
           if(verificaSintaxe(nArgs, 2)) {
               // animal <letra>
               criaAnimal(args.at(1)[0]);
               infoToUser();
               continue;
           }
           if(verificaSintaxe(nArgs, 4)) {
               if (!verificaXY(stoi(args.at(2)), stoi(args.at(3)), reserva)) {
                   infoToUser();
                   continue;
               }
               // animal <letra> <posX> <posY>
               criaAnimal(args.at(1)[0], stoi(args.at(2)), stoi(args.at(3)));
               infoToUser();
               continue;
           }
           if(nArgs != 2 && nArgs != 4){
               cout << "numero de argumentos invalido" << endl;
               infoToUser();
               continue;
           }
        }
        // MATAR ANIMAL POSIÇÃO
        if ( args.at(0) == "kill") {
            if (verificaSintaxe(nArgs, 3)) {
                if ( !verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva) ) {
                    infoToUser();
                    continue;
                }
                // kill <posX> <posY>
                killAnimal(int (stoi(args.at(1))), int (stoi(args.at(2))));
                infoToUser();
                continue;
            } else {
                cout << "numero de argumentos invalido" << endl;
                infoToUser();
                continue;
            }
        }
        // MATAR ANIMAL ID
        if ( args.at(0) == "killid") {
            if (verificaSintaxe(nArgs, 2)) {
                if ( !verificaId(stoi(args.at(1)), reserva) ) {
                    cout << "Erro! ID invalido!" << endl << "O que pretende validar: " << endl;
                    continue;
                }
                // killid <id>
                killAnimal(stoi(args.at(1)));
                infoToUser();
                continue;
            } else {
                cout << "numero de argumentos invalido"<< endl;
                infoToUser();
                continue;
            }
        }
        // COLOCAR ALIMENTO
        if ( args.at(0) == "food") {
            if (!verificaAlimento(args.at(1)) ) {
                infoToUser();
                continue;
            }
            if (verificaSintaxe(nArgs, 2)) {
                // food <letra>
                placeAlimento(args.at(1)[0]);
                infoToUser();
                continue;
            }
            if (verificaSintaxe(nArgs, 4)) {
                if ( !verificaXY(stoi(args.at(2)), stoi(args.at(3)), reserva)) {
                    infoToUser();
                    continue;
                }
                // food <letra> <posX> <posY>
                placeAlimento(args.at(1)[0], stoi(args.at(2)), stoi(args.at(3)));
                infoToUser();
                continue;
            }
            if(nArgs != 2 && nArgs != 4) {
                cout << "numero de argumentos invalido" << endl;
                infoToUser();
                continue;
            }
        }
        //  ALIMENTAR DIRETAMENTE ANIMAIS
        if ( args.at(0) == "feed") {
            if (verificaSintaxe(nArgs, 5)) {
                if ( !verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva) ) {
                    infoToUser();
                    continue;
                }
                // feed <posX> <posY> <nutri> <toxic>
                feedDirectly(stoi(args.at(1)),stoi(args.at(2)), stoi(args.at(3)), stoi(args.at(4)));
                infoToUser();
                continue;
            } else {
                cout << "numero de argumentos invalido" << endl;
                infoToUser();
                continue;
            }
        }
        if ( args.at(0) == "feedid") {
            if (verificaSintaxe(nArgs, 2)) {
                if (!verificaId(stoi(args.at(1)), reserva)) {
                    infoToUser();
                    continue;
                }
                // feedid <id>
                feedId(stoi(args.at(1)));
                infoToUser();
                continue;
            } else {
                cout << "numero de argumentos invalido" << endl;
                infoToUser();
                continue;
            }
        }
        //  REMOVER ALIMENTO
        if ( args.at(0) == "nofood") {
            if (verificaSintaxe(nArgs, 3)) {
                if ( !verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva) ) {
                    infoToUser();
                    continue;
                }
                // nofood <posX> <posY>
                removeAlimento( stoi(args.at(1)), stoi(args.at(2)));
                infoToUser();
                continue;
            }
            if (verificaSintaxe(nArgs, 2)) {
                if ( !verificaId(stoi(args.at(1)), reserva)) {
                    cout << "Erro! ID invalido!" << endl;
                    infoToUser();
                    continue;
                }
                // nofood <id>
                removeAlimento(reserva.getId());
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // ELIMINAR O QUE QUER QUE ESTEJA NUMA POSIÇÃO
        if ( args.at(0) == "empty") {
            if (verificaSintaxe(nArgs, 3)) {
                if (!verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva)) {
                    infoToUser();
                    continue;
                }
                // empty <posX> <posY>
                deletePos(stoi(args.at(1)), stoi(args.at(2)));
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // VER O QUE SE ENCONTRA NUMA POSIÇÃO
        if ( args.at(0) == "see") {
            if (verificaSintaxe(nArgs, 3)) {
                if (!verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva)) {
                    infoToUser();
                    continue;
                }
                // see <posX> <posY>
                checkPos(int(stoi(args.at(1))), int(stoi(args.at(2))));
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // VER INFORMAÇÃO ACERCA DE UM ELEMENTO DO SIMULADOR (ANIMAL OU ALIMENTO)
        if ( args.at(0) == "info") {
            if (verificaSintaxe(nArgs, 2)) {
                if (!verificaId(stoi(args.at(1)), reserva) ) {
                    infoToUser();
                    continue;
                }
                // info <id>
                checkId(int(stoi(args.at(1))) );
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // PASSAR PARA O INSTANTE SEGUINTE DA SIMULAÇÃO
        if ( args.at(0) == "n") {
            if (verificaSintaxe(nArgs, 1)) {
                // n
                tick();
                infoToUser();
                continue;
            }
            if (verificaSintaxe(nArgs, 2)) {
                // n <N>
                for(int i = 1; i < stoi(args.at(1)); ++i )
                    tick();
                infoToUser();
                continue;
            }
            if (verificaSintaxe(nArgs, 3)) {
                // n <N> <P>
                for(int i = 1; i < stoi(args.at(1)); ++i )
                    tick(5);
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // LISTAR ID DOS ANIMAIS NA RESERVA
        if (args.at(0) == "anim") {
            if (verificaSintaxe(nArgs, 1)) {
                // anim
                listIdsReserva();
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // LISTAR O ID DOS ANIMAIS NA AREA VISIVEL DA RESERVA
        if (args.at(0) == "visanim") {
            if (verificaSintaxe(nArgs, 1)) {
                // visanim
                listIdsWindow();
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // ARMAZENAR O ESTADO DA RESERVA EM MEMORIA
        if (args.at(0) == "store") {
            if (verificaSintaxe(nArgs, 2)) {
                // store <file>
                store(args.at(1));
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // REATIVAR UM ESTADO DA RESERVA PREVIAMENTE ARMAZENADO EM MEMORIA
        if (args.at(0) == "restore") {
            if (verificaSintaxe(nArgs, 2)) {
                // restore <file>
                restore(args.at(1));
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // CARREGAR E EXECUTAR COMANDOS A PARTIR DE UM FICHEIRO DE TEXTO
        if (args.at(0) == "load") {
            if (verificaSintaxe(nArgs, 2)) {
                // load <file>
                checkComandoUser(args.at(1));
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // DESLOCAR A AREA DE VISUALIZAÇÃO
        if (args.at(0) == "slide") {
            if (verificaSintaxe(nArgs, 3)) {
                if ( !verificaDirecao(args.at(1)) ) {
                    infoToUser();
                    continue;
                }
                // slide <direction> <linhas/colunas>
                deslocaAreaViz(args.at(1), stoi(args.at(2)));
                infoToUser();
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                infoToUser();
                continue;
            }
        }
        // ENCERAR O SIMULADOR
        if (args.at(0) == "exit") {
            if (verificaSintaxe(nArgs, 1)){
                // exit
                return;
            } else {
                cout << "Erro! Numero errado de parametros"<<endl;
                infoToUser();
                continue;
            }
        }
        // LISTAR OS COMANDOS POSSIVEIS
        if(args.at(0) == "help") {
            if(verificaSintaxe(nArgs, 1)){
                // help
                cout << "work in progress!" << endl;
            } else {
                cout << "erro! numero de argumentos invalido" << endl;
                infoToUser();
                continue;
            }
        }
//        escreve os argumentos no terminal
//        for (std::vector<std::string>::size_type i = 0; i != args.size(); ++i) {
//            std::cout << args.at(i) << std::endl;
//        }
    } while(getline(cin, input));
}



/*
 // LER DO FICHEIRO
void checkComando() {
    fstream myfile;
    myfile.open("comandos.txt", ios::in); // read mode
    if (myfile.is_open()) {
        cout << "aberto\n";
        while (getline(myfile, line)) {
            cout << line << endl;
            break;
        }
        myfile.close();
    }
}
*/
