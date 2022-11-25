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

const vector<string> listEspecies {"c", "o", "l", "g", "m"};
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

void verCmd(const string &cmd){
        bool xpto = find(listComandos.begin(), listComandos.end(), cmd) != listComandos.end();
        if (!xpto){
            cout << "Inseriu mal o primeiro comando!\n";
            return;
        }
}
void verEsp(string &esp) {
        bool xpto = find(listEspecies.begin(), listEspecies.end(), esp) != listEspecies.end();
        if (!xpto){
            cout << "Inseriu mal o segundo comando!\n";
            return;
        }
}

void verXY(const int &lin, const int &col) {
    if ( ( lin < 16 || lin > 500) || (col < 16 || col > 500 ) ) {
        cout << "Inseriu valores invalidos de linhas e/ou colunas \n";
        return;
    }
}

void verId(const int &id) {
    if (id < 0) {
        cout << "Inseriu um ID invalido!\n";
        return;
    }
}


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

        // chamar a função de validar cenas
    // CRIAR FUNCAO checkComando()
        verCmd(args.at(0));

        if ( args.at(0) == "animal") {
            if (nArgs == 2) {
                verEsp(args.at(1));
                //adicionar coords random
                //criaAnimal(char especie);
            }
            else {
                verEsp(args.at(1));
                verXY(stoi(args.at(2)), stoi(args.at(3)));
                criaAnimal(char (args.at(2)[0]), int (stoi(args.at(3))), int (stoi(args.at(4))));
            }
        }
        if ( args.at(0) == "kill") {
            if (nArgs == 3) {
                verXY(stoi(args.at(2)), stoi(args.at(3)));
                killAnimal(int (stoi(args.at(2))), int (stoi(args.at(3))));
            }
        }
        if ( args.at(0) == "killid") {
            if (nArgs == 2) {
                // killAnimal(int id);
                //killAnimal(int id);
            }
        }

        // NEXT: COLOCAR ALIMENTO etc...


//        escreve os argumentos no terminal
//        for (std::vector<std::string>::size_type i = 0; i != args.size(); ++i) {
//            std::cout << args.at(i) << std::endl;
//        }

        cout << "O que pretende validar: " << endl;
    }while(getline(cin, input));
}



/*
    1. contar nr de palavras;
    2. verificar se maior q zero ou menor q 6
    3. se nao
    4. se sim, checkFirstName e nr de argumentos
    5. com nr de arg, comparar o animal com os outros animais
    6. se igual, comparar o nr de argumentos
    7. se dentro dos valores certos (overload)
 */



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
