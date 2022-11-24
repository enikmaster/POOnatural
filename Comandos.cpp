#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Alimento.h"
#include "Comandos.h"
#include "Animal.h"
using namespace std;

const vector<char> listEspecies {'c', 'o', 'l', 'g', 'm'};
const vector<string> listComandos {"animal", "kill", "killid", "food", "feed",
                            "feedid", "nofood", "empty", "see",
                            "info", "n", "anim", "visanim", "store",
                            "restore", "load", "slide", "exit"};

void verNrArg(int &len, string &input) {
    int cont=0;
    for (int i=0; i<len; i++) {
        if (input.at(i) == ' ') {
            cont++;
        }
    }
    if (cont > 5) {
        cout << "Erro! Argumentos a mais!\n";
        return;
    }
    if (cont < 1) {
        cout << "Erro! Argumentos a menos!\n";
        return;
    }
}

void verCmd(const string &cmd){
        bool xpto = find(listComandos.begin(), listComandos.end(), cmd) != listComandos.end();
        if (!xpto){
            cout << "Inseriu mal o primeiro comando!\n";
            return;
        }
}
void verEsp(const char &esp) {
        bool xpto = find(listEspecies.begin(), listEspecies.end(), esp) != listEspecies.end();
        if (!xpto){
            cout << "Inseriu mal o primeiro comando!\n";
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


void checkComandoUser(string &input) {

    int len = input.length();
    cout << "string: " << input << " " << "tamanho: " << len << endl;

    //Calcula e verifica o numero de argumentos passados
    verNrArg(len, input);


    // Get primeira palavra
    string cmd = input.substr(0, input.find(' '));
    cout << cmd << endl;
    // Verifica se a primeira palavra existe
    verCmd(cmd);


    // Get index da sigla
    int especie = (input.find(' ') + 1);
    cout << "index do char: " << especie << endl;
    // Get sigla
    char esp;
    esp = input.at(especie);
    cout << "char de especie: " << esp << endl;
    // Verifica se a esp existe
    verEsp(esp);

    // Animal de 4 parametros (INCOMPLETA)
    int flin = (input.find(' '  + 3));
    int fcol = (input.find(' ' + 5));
    int lin = input.at(flin);
    int col = input.at(fcol);
    cout << "lin col : " << lin << col << endl;
    //Verifica se x e y estao compreendidos entre os limites da Reserva
    verXY(lin, col);


    // para os comandos que nao precisam de overload, fazer um
    // vetor para direcionar diretamente as funcoes
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
