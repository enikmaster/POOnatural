#include <random>
//#include <bits/stdc++.h>
#include "Interface.h"

uniform_int_distribution<> dimR(16, 500);
//uniform_int_distribution<> movimento(1, 2);
mt19937 gen;

Interface::Interface(Reserva& hub)
    : zoo(hub), wReserva(term::Window(0, 0, 32, 16)), wInfo(term::Window(33, 0, 85, 16)), wInputs(term::Window(0, 16, 118, 5)) {
    this->zoo.incContadorIds();
    wReserva << set_color(0) << move_to(0, 0);
    mvprintw(0,1," Reserva ");
    wInfo << set_color(0) << move_to(0, 0);
    //mvwprintw((0,34,"Info");
    wInputs << set_color(0) << move_to(0, 0);
    mvprintw(16,1," Input ");
}
// divide o input em várias strings e devolve um vetor com tudo
vector<string> split(const string& input) {
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != input.size()) {
        while (i != input.size() && isspace(input.at(i)))
            ++i;
        string_size j = i;
        while (j != input.size() && !isspace(input.at(j)))
            j++;
        if (i != j) {
            ret.push_back(input.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}
// conta o número de argumentos
int countArgs(stringstream &input, string& temp) {
    int cnt(0);
    while(input >> temp)
        ++cnt;
    return cnt;
}
// verifica e devolve as dimensoes da reserva a ser criada
void getReservaDims(int& DimX, int& DimY, term::Terminal& janela) {
    string input;
    bool flag = false;
    do {
        janela << term::move_to(0, 23) << "Insira a dimensao da reserva (altura comprimento) ou 0 0 para um tamanho aleatorio: ";
        janela >> input;
        stringstream iss (input);
        string temp{};
        int nArgs = countArgs(iss, temp);
        if(nArgs > 2 || nArgs == 0) {
            janela << term::move_to(4, 24) << "Numero de argumentos invalido...";
            continue;
        }
        vector<string> args = split(input);
        if((stoi(args.at(0)) == 0) && (stoi(args.at(1)) == 0)) {
            //DimX = dimR(gen);
            //DimY = dimR(gen);
            DimX = 16 + (rand() % 485);
            DimY = 16 + (rand() % 485);
            flag = true;
        }
        if((stoi(args.at(0)) >= 16 && stoi(args.at(0)) <= 500) && (stoi(args.at(1)) >= 16 && stoi(args.at(1)) <= 500)) {
            DimX = stoi(args.at(0));
            DimY = stoi(args.at(1));
            flag = true;
        }
    }while(!flag);
}
// recebe o input do utilizador
string Interface::getInput() {
    string input{};
    wInputs << move_to(0, 1);
    wInputs >> input;
    return input;
}
// devolve a informação sobre o comando pedido
int Interface::getHelp(string& cmd, int writePos) {
    if(writePos == 1) {
        wInfo.clear();
        refresh();
        wInfo << zoo.getAsString();
    }
    for(auto& it : comandos) {
        if(cmd == it.getCmd()){
            wInfo << move_to(0, writePos) << it.getCmd() << " " << it.getArgs();
            wInfo << move_to(0, ++writePos) << it.getDescr();
            writePos += 2;
        }
    }
    return 0;
}
// envia para o output uma mensagem
void Interface::infoToUser() {
    wInputs.clear();
    refresh();
    wInputs << term::move_to(0, 0) << "Insira um comando: ";
    wInputs << move_to(0, 1);
}
// envia um erro para o user
void Interface::infoErroArgs(int num) {
    if(num > 5) {
        wInfo.clear();
        refresh();
        wInfo << zoo.getAsString();
        wInfo << move_to(0,1) << "Demasiados argumentos...";
        infoToUser();
    }
    if(num < 1) {
        wInfo.clear();
        refresh();
        wInfo << zoo.getAsString();
        wInfo << move_to(0, 1) << "Sem instrucoes...";
        infoToUser();
    }
}
void Interface::infoErroCmdDesc() {
    wInfo.clear();
    refresh();
    wInfo << zoo.getAsString();
    wInfo << move_to(0, 1) << "Comando desconhecido...";
    infoToUser();
}
void Interface::infoErroNumArgs(string& cmd) {
    wInfo.clear();
    refresh();
    wInfo << zoo.getAsString();
    wInfo << move_to(0, 1) << "Comando "<< cmd <<" com numero de argumentos invalido...";
}
// procura o comando pedido numa listagem de comandos e devolve a posição ou 0 se não encontrar
int Interface::findComando(string& arg) {
    int pos = 0;
    for(auto& it : comandos) {
        ++pos;
        if(it.getCmd() == arg)
            return pos;
    }
    return 0;
}
// inicia o simulador
void Interface::start() {
    infoToUser();
    wInfo << zoo.getAsString();
    bool on = true;
    do {
        string userInput{getInput()};
        wInputs.clear();
        refresh();
        stringstream iss (userInput);
        string temp{};
        int nArgs = countArgs(iss, temp);
        if(nArgs < 1 || nArgs > 5) {
            infoErroArgs(nArgs);
            continue;
        }
        vector<string> args = split(userInput);
        int pos = findComando(args.at(0));
        if(!pos) {
            infoErroCmdDesc();
            continue;
        } else {
            wInfo.clear();
            refresh();
            wInfo << zoo.getAsString();
            int flag = 0;
            if(nArgs == 1)
                flag = comandos.at(pos-1).executa(args.at(0));
            if(nArgs == 2)
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1));
            if(nArgs == 3)
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2));
            if(nArgs == 4)
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2), args.at(3));
            if(nArgs == 5)
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2), args.at(3), args.at(4));
            if(flag == -1)
                flag = getHelp(args.at(1), 1); // executa o comando help
            if(flag) {
                string cmd{comandos.at(pos-1).getCmd()};
                infoErroNumArgs(cmd);
                getHelp(cmd, 3); // executa o comando help pq deu erro num comando
            }
            if(flag == -15)
                on = false; // exit
            infoToUser();
        }
    } while(on);
}

// verifica se a especie (letra) existe na lista
/*bool verificaEspecie(string &esp, term::Window &janela) {
    bool xpto = find(listEspecies.begin(), listEspecies.end(), esp) != listEspecies.end();
    if (!xpto){
        janela << term::move_to(0, 1) << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}*/
// verifica se o alimento (letra) existe na lista
/*bool verificaAlimento(string &tipo, term::Window &janela) {
    bool xpto = find(listAlimentos.begin(), listAlimentos.end(), tipo) != listAlimentos.end();
    if (!xpto){
        janela << term::move_to(0, 1) << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}*/
// verifica se a direcao existe na lista
/*bool verificaDirecao(string &dir, term::Window &janela) {
    bool xpto = find(listDirections.begin(), listDirections.end(), dir) != listDirections.end();
    if (!xpto){
        janela << term::move_to(0, 1) << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}*/
// verifica se a posição está dentro da reserva e posteriormente, se está associado a alguma coisa
/*bool verificaXY(const int &posX, const int &posY, const Reserva& reserva, term::Window &janela) {
    if (posX < 1 || posY < 1) {
        janela << term::move_to(0, 1) << "Inseriu valores invalidos de linhas e/ou colunas \n";
        return false;
    }
    if (posY > reserva.getDimY() || posX > reserva.getDimX() ){
        janela << term::move_to(0, 1) << "Inseriu valores invalidos de linhas e/ou colunas \n";
        return false;
    }
    return true;
}*/
// verifica se o id está na reserva
/*bool verificaId(const int &id, const Reserva &reserva) {
    return id == reserva.getId();
}*/

