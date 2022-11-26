#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "Alimento.h"
#include "Comandos.h"
#include "Animal.h"
using namespace std;

const vector<string> listDirections {"up", "down", "left", "right"};
const vector<string> listEspecies {"c", "o", "l", "g", "m"};
const vector<string> listAlimentos {"r", "t", "b", "a"};
const vector<string> listComandos {"animal", "kill", "killid", "food", "feed",
                            "feedid", "nofood", "empty", "see",
                            "info", "n", "anim", "visanim", "store",
                            "restore", "load", "slide", "exit"};


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
int numArgs(std::stringstream& teste, std::string&temp ) {
    int cnt{0};
    while(teste >> temp)
        ++cnt;
    return cnt;
}

bool verCmd(const string &cmd){
        bool xpto = find(listComandos.begin(), listComandos.end(), cmd) != listComandos.end();
        if (!xpto)
            cout << "Inseriu mal o primeiro comando!\n";
        return xpto;
}
bool verEsp(string &esp) {
        bool xpto = find(listEspecies.begin(), listEspecies.end(), esp) != listEspecies.end();
        if (!xpto){
            cout << "Inseriu mal o segundo comando!\n";
        }
        return xpto;
}
bool verAli(string &tipo) {
    bool xpto = find(listAlimentos.begin(), listAlimentos.end(), tipo) != listAlimentos.end();
    if (!xpto){
        cout << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}
bool verDir(string &dir) {
    bool xpto = find(listDirections.begin(), listDirections.end(), dir) != listDirections.end();
    if (!xpto){
        cout << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}

bool verXY(const int &lin, const int &col) {
    if ( ( lin < 16 || lin > 500) || (col < 16 || col > 500 ) ) {
        cout << "Inseriu valores invalidos de linhas e/ou colunas \n";
        return false;
    } else return true;
}

bool verId(const int &id) {
    if (id < 0) {
        cout << "Inseriu um valor invalido!\n";
        return false;
    } else return true;
}
bool verificaAnimal(int nArgs, vector<string> &args) {
    if (nArgs == 2) {
        if (!verEsp(args.at(1))) {
            return false;
        }
        // Adicionar coords random
        criaAnimal(args.at(1)[0]);
        cout << "O que pretende validar: " << endl;
        return true;
    }
    if (nArgs == 4) {
        if ( !verEsp(args.at(1)) ) {
            return false;
        }
        if ( !verXY(stoi(args.at(2)), stoi(args.at(3))) ) {
            return false;
        }
        criaAnimal(char (args.at(1)[0]), int (stoi(args.at(2))), int (stoi(args.at(3))));
        return true;
    }
        cout << "Erro! Numero errado de parametros\n";
        return false;
}

void checkComandoUser(const string& nomeFicheiro) {
    string line;
    fstream myfile;
    myfile.open(nomeFicheiro, ios::in); // in = read mode, on = write mode
    if (myfile.is_open()) {
        cout << "Ficheiro aberto com sucesso!\n";
        while (getline(myfile, line)) {
            cout << line << endl;
            //break;

        }
        myfile.close();
    }
    else {
        cout << "Erro a abrir o ficheiro!\n";
        return;
    }
}

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
void tick(int instante){cout << "A verificar na 2 fase\n";};
void tick(int instante, int pausa){cout << "A verificar na 2 fase\n";};
void listIdsReserva(){cout << "A verificar na 2 fase\n";};
void listIdsWindow(){cout << "A verificar na 2 fase\n";};
void store(string nome){cout << "A verificar na 2 fase\n";};
void restore(string nome){cout << "A verificar na 2 fase\n";};
void deslocaAreaViz(string dir, int lin, int col){cout << "A verificar na 2 fase\n";};

void getInput() {
    string input{};
    cout << "O que pretende validar: " << endl;
    getline(cin, input);
    do {
        stringstream iss (input);
        string temp{};
        int nArgs = numArgs(iss, temp);
        if(nArgs > 5) {
            cout << "demasiada informacao..." << endl;
            cout << "O que pretende validar: " << endl;
            continue;
        }
        if(nArgs < 1) {
            cout << "sem instrucoes..." << endl;
            cout << "O que pretende validar: " << endl;
            continue;
        }
        vector<string> args = split(input);

        // ################################  VERIFICAÇÕES  ########################################

        if ( !verCmd(args.at(0)) ) {
            cout << "O que pretende validar: " << endl;
            continue;
        }

        // CRIAR ANIMAL

        if ( args.at(0) == "animal") {
           bool flag;
           flag = verificaAnimal(nArgs, args);
           if (!flag) {
               cout << "O que pretende validar: " << endl;
               continue;
           }
        }



        // MATAR ANIMAL

        if ( args.at(0) == "kill") {
            if (nArgs == 3) {
                 if ( !verXY(stoi(args.at(1)), stoi(args.at(2))) ) {
                     cout << "O que pretende validar: " << endl;
                     continue;
                 }
                killAnimal(int (stoi(args.at(1))), int (stoi(args.at(2))));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }

        if ( args.at(0) == "killid") {
            if (nArgs == 2) {
                if ( !verId(stoi(args.at(1))) ) {
                    cout << "Erro! ID invalido!\n";
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                killAnimal(stoi(args.at(1)));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }


        // COLOCAR ALIMENTO

        if ( args.at(0) == "food") {
            if (nArgs == 2) {
                if ( !verAli(args.at(1)) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                // Adicionar coords random
                placeAlimento(args.at(1)[0]);
                cout << "O que pretende validar: " << endl;
                continue;
            }
            if (nArgs == 4) {
                if ( !verAli(args.at(1)) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                if ( !verXY(stoi(args.at(2)), stoi(args.at(3))) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                placeAlimento(char (args.at(1)[0]), int (stoi(args.at(2))), int (stoi(args.at(3))));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;}
        }


        //  ALIMENTAR DIRETAMENTE ANIMAIS

        if ( args.at(0) == "feed") {
            if (nArgs == 5) {
                if ( !verXY(stoi(args.at(1)), stoi(args.at(2))) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                if ( (!verId(stoi(args.at(3)))) && (!verId(stoi(args.at(4)))) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                feedDirectly(stoi(args.at(1)),stoi(args.at(2)), stoi(args.at(3)), stoi(args.at(4)));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;}
        }

        if ( args.at(0) == "feedid") {
            if (nArgs == 2) {
                if (!verId(stoi(args.at(1)))) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                feedId(stoi(args.at(1)));
                cout << "ola";
                cout << "O que pretende validar: " << endl;
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }

        //  REMOVER ALIMENTO

        if ( args.at(0) == "nofood") {
            if (nArgs == 3) {
                if ( !verXY(stoi(args.at(1)), stoi(args.at(2))) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                removeAlimento(int (stoi(args.at(1))), int (stoi(args.at(2))));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            if (nArgs == 2) {
                if ( !verId(stoi(args.at(1))) ) {
                    cout << "Erro! ID invalido!\n";
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                removeAlimento(1);
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }


        // ELIMINAR O QUE QUER QUE ESTEJA NUMA POSIÇÃO

        if ( args.at(0) == "empty") {
            if (nArgs == 3) {
                if (!verXY(stoi(args.at(1)), stoi(args.at(2)))) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                deletePos(int(stoi(args.at(1))), int(stoi(args.at(2))));
                cout << "O que pretende validar: " << endl;
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }


        // VER O QUE SE ENCONTRA NUMA POSIÇÃO

        if ( args.at(0) == "see") {
            if (nArgs == 3) {
                if (!verXY(stoi(args.at(1)), stoi(args.at(2)))) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                checkPos(int(stoi(args.at(1))), int(stoi(args.at(2))));
                cout << "O que pretende validar: " << endl;
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }


        // VER INFORMAÇÃO ACERCA DE UM ELEMENTO DO SIMULADOR (ANIMAL OU ALIMENTO)

        if ( args.at(0) == "info") {
            if (nArgs == 2) {
                if (!verId(stoi(args.at(1))) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                checkId(int(stoi(args.at(1))) );
                cout << "O que pretende validar: " << endl;
                continue;
            } else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }


        // PASSAR PARA O ISNTANTE SEGUINTE DA SIMULAÇÃO

        if ( args.at(0) == "n") {
            if (nArgs == 1) {
                //int n++;
                tick();
                cout << "O que pretende validar: " << endl;
                continue;
            }
            if (nArgs == 2) {
                if (!verId(stoi(args.at(1))) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                tick(stoi(args.at(1)) );
                cout << "O que pretende validar: " << endl;
                continue;
            }
            if (nArgs == 3) {
                if ( (!verId(stoi(args.at(1)))) && (!verId(stoi(args.at(2)))) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                tick(stoi(args.at(1)),stoi(args.at(2)));
                cout << "O que pretende validar: " << endl;
                continue;
            }

            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }


        // LISTAR ID DOS ANIMAIS NA RESERVA

        if (args.at(0) == "anim") {
            if (nArgs == 1) {
                listIdsReserva();
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }

        // LISTAR O ID DOS ANIMAIS NA AREA VISIVEL DA RESERVA

        if (args.at(0) == "visanim") {
            if (nArgs == 1) {
                listIdsWindow();
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }

        // ARMAZENAR O ESTADO DA RESERVA EM MEMORIA

        if (args.at(0) == "store") {
            if (nArgs == 2) {
                store(args.at(1));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }

        // REATIVAR UM ESTADO DA RESERVA PREVIAMENTE ARMAZENADO EM MEMORIA

        if (args.at(0) == "restore") {
            if (nArgs == 2) {
                restore(args.at(1));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }

        // CARREGAR E EXECUTAR COMANDOS A PARTIR DE UM FICHEIRO DE TEXTO

        if (args.at(0) == "load") {
            if (nArgs == 2) {
                checkComandoUser(args.at(1));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }


        // DESLOCAR A AREA DE VISUALIZAÇÃO

        if (args.at(0) == "slide") {
            if (nArgs == 4) {
                if ( !verDir(args.at(1)) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                if ( (!verId(stoi(args.at(2)))) && (!verId(stoi(args.at(3)))) ) {
                    cout << "O que pretende validar: " << endl;
                    continue;
                }
                deslocaAreaViz(args.at(1), stoi(args.at(2)), stoi(args.at(3)));
                cout << "O que pretende validar: " << endl;
                continue;
            }
            else {
                cout << "Erro! Numero errado de parametros\n";
                cout << "O que pretende validar: " << endl;
                continue;
            }
        }

        // ENCERAR O SIMULADOR

        if (args.at(0) == "exit") {
            if (nArgs == 1){
                return;
            } else {
            cout << "Erro! Numero errado de parametros\n";
            cout << "O que pretende validar: " << endl;
            continue;
        }
        }


//        escreve os argumentos no terminal
//        for (std::vector<std::string>::size_type i = 0; i != args.size(); ++i) {
//            std::cout << args.at(i) << std::endl;
//        }


    }while(getline(cin, input));

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
