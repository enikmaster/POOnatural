#include "Includes.h"

using namespace std;

const vector<char> listEspecies {'c', 'o', 'l', 'g', 'm'};
const vector<string> listComandos {"animal", "kill", "killid", "food", "feed",
                            "feedid", "nofood", "empty", "see",
                            "info", "n", "anim", "visanim", "store",
                            "restore", "load", "slide", "exit"};
int numArgs(std::stringstream& teste, std::string& temp ) {
    int cnt{0};
    while(teste >> temp)
        ++cnt;
    return cnt;
}
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
        // verCmd(args.at(0));

//        escreve os argumentos no terminal
//        for (std::vector<std::string>::size_type i = 0; i != args.size(); ++i) {
//            std::cout << args.at(i) << std::endl;
//        }

        cout << "O que pretende validar: " << endl;
    }while(getline(cin, input));
}

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
