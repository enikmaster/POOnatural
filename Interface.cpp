#include "Interface.h"
#include "Reserva/Local.h"
#include "Alimentos/Alimento.h"
#include "Animais/Animal.h"
uniform_int_distribution<> dimR(16, 500);
//uniform_int_distribution<> movimento(1, 2);
mt19937 gen;

Interface::Interface(Reserva* reserva)
        //: originX(0), originY(0), zoo(reserva), wReserva(term::Window(0, 0, 32, 16)), wInfo(term::Window(33, 0, 85, 16)), wInputs(term::Window(0, 16, 118, 5)) {
        : originX(0), originY(0), zoo(reserva), wReserva(term::Window(0, 0, 18, 18)), wInfo(term::Window(19, 0, 99, 18)), wInputs(term::Window(0, 18, 118, 5)) {
    this->zoo->incContadorIds();
    wReserva << set_color(0) << move_to(0, 0);
    mvprintw(0,1," Reserva ");
    wInfo << set_color(0) << move_to(0, 0);
    //mvwprintw((0,34,"Info");
    wInputs << set_color(0) << move_to(0, 0);
    mvprintw(18,1," Input ");
}

// externas
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

// getters

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
        wInfo << zoo->getAsString();
    }
    for(auto& comando : comandos) {
        if(cmd == comando.getCmd()){
            wInfo << move_to(0, writePos) << comando.getCmd() << " " << comando.getArgs();
            wInfo << move_to(0, ++writePos) << comando.getDescr();
            writePos += 2;
        }
    }
    return 0;
}

// information to user
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
        wInfo << zoo->getAsString();
        wInfo << move_to(0,1) << "Demasiados argumentos...";
        infoToUser();
    }
    if(num < 1) {
        wInfo.clear();
        refresh();
        wInfo << zoo->getAsString();
        wInfo << move_to(0, 1) << "Sem instrucoes...";
        infoToUser();
    }
}
void Interface::infoErroCmdDesc() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Comando desconhecido...";
    infoToUser();
}
void Interface::infoErroNumArgs(string& cmd) {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Comando "<< cmd <<" com numero de argumentos invalido...";
}
void Interface::infoErroParam() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Um dos parametros nao e' valido.";
}
void Interface::infoShowReserva() {
    wReserva.clear();
    refresh();
    for( int i = 0; i < 16; ++i) {
        for( int j = 0; j < 16; ++j) {
            wReserva << move_to(j, i) << ".";
        }
    }
    if(zoo->locaisOcupados.size() != 0) {
        for(auto& localOcupado : zoo->locaisOcupados) {
            if(checkVisibilityX(localOcupado->getLocalX()) && checkVisibilityY(localOcupado->getLocalY()) ) {
                wReserva << move_to(localOcupado->getLocalX() - zoo->getOrigemVisX(), localOcupado->getLocalY() - zoo->getOrigemVisY()) << localOcupado->getTipoOcupante();
                // faz cenas
                /*if(it->getTipoOcupante() == "alimento") {
                    for(auto& itr : zoo->alimentos) {
                        if(itr->getFoodId() == it->getOcupaId()) {
                            wReserva << move_to(it->getLocalX() - zoo->getOrigemVisX(), it->getLocalY() - zoo->getOrigemVisY()) << itr->getLetra();
                        }
                    }
                }*/
                // fazer o ciclo para os animais
            }

        }
    }
}
void Interface::infoAboutId(int eid) {
    for(auto& alimento : zoo->alimentos) {
        if(alimento->getFoodId() == eid) {
            wInfo << move_to(0, 1) << "Nome: "<< alimento->getLetra() << alimento->getFoodId();
            wInfo << move_to(0, 2) << "Id: "<< alimento->getFoodId();
            wInfo << move_to(0, 3) << "Posicao X: "<< alimento->getPosX() << " Posicao Y: " << alimento->getPosY();
            wInfo << move_to(0, 4) << "Valor nutritivo: " << alimento->getNutri();
            wInfo << move_to(0, 5) << "Valor toxicidade: " << alimento->getToxic();
            wInfo << move_to(0, 6) << "Validade: " << alimento->getDuracao() << " turnos";
            wInfo << move_to(0, 7) << "Cheiros:";
            for(int i = 0; i < alimento->getQuantidadeCheiros();++i) {
                wInfo << move_to(0, 8+i) << "   " << alimento->getCheiro(i);
            }
            return;
        }
    }
    for(auto& animal : zoo->animais) {
        if(animal->getAnimalId() == eid) {
            wInfo << move_to(0, 1) << "Nome: "<< animal->getLetra() << animal->getAnimalId();
            wInfo << move_to(0, 2) << "Id: "<< animal->getAnimalId();
            wInfo << move_to(0, 3) << "Posicao X: "<< animal->getPosX() << " Posicao Y: " << animal->getPosY();
            wInfo << move_to(0, 4) << "Fome: " << animal->getFome();
            wInfo << move_to(0, 5) << "Saude: " << animal->getSaude();
            wInfo << move_to(0, 6) << "Vida: " << animal->getVida() << " turnos";
            wInfo << move_to(0, 7) << "Peso: " << animal->getPeso();
            wInfo << move_to(0, 8) << "Movimento maximo: " << animal->getdeslMax();
            // falta um ciclo para o registo alimentar ou indicar o tamanho do registo
            return;
        }
    }
}
// actions
bool Interface::checkArgAnimais(string& arg) const {
    for(auto& letra : letraEspecies){
        if(letra == arg)
            return true;
    }
    return false;
}
bool Interface::checkArgAlimentos(string& arg) const {
    for(auto& letra : letraAlimentos){
        if(letra == arg)
            return true;
    }
    return false;
}
bool Interface::checkArgSaves(string& arg) const {
    // to do
    return false;
}
bool Interface::checkArgDirection(string& arg) const{
    for(auto& direction : directions){
        if(direction == arg)
            return true;
    }
    return false;
}
bool Interface::checkArgIds(int arg) const{
    // to do

    return false;
}
bool Interface::checkArgPosX(int arg) const{
    return (arg <= zoo->getDimX());
}
bool Interface::checkArgPosY(int arg) const{
    return (arg <= zoo->getDimY());
}
bool Interface::checkVisibilityX(int pos) const {
    if(pos >= zoo->getOrigemVisX() && pos <= zoo->getOrigemVisX() + 16)
        return true;
    return false;
}
bool Interface::checkVisibilityY(int pos) const {
    if(pos >= zoo->getOrigemVisY() && pos <= zoo->getOrigemVisY() + 16)
        return true;
    return false;
}
// procura o comando pedido numa listagem de comandos e devolve a posição ou 0 se não encontrar
int Interface::findComando(string& arg) {
    int pos = 0;
    for(auto& comando : comandos) {
        ++pos;
        if(comando.getCmd() == arg)
            return pos;
    }
    return 0;
}
// inicia o simulador
void Interface::start() {
    infoToUser();
    wInfo << zoo->getAsString();
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
            wInfo << zoo->getAsString();
            int flag = 0;
            if(nArgs == 1)
                flag = comandos.at(pos-1).executa( args.at(0), getReserva() );
            if(nArgs == 2) {
                if(args.at(0) == "animal" && !checkArgAnimais(args.at(1))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "killid" && !checkArgIds(stoi(args.at(1)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "food" && checkArgAlimentos(args.at(1))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "nofood" && !checkArgIds(stoi(args.at(1)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "info" && !checkArgIds(stoi(args.at(1)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "restore" && !checkArgSaves(args.at(1))) {
                    infoErroParam();
                    continue;
                }
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), getReserva());
            }
            if(nArgs == 3) {
                if(args.at(0) == "kill" && !checkArgPosX(stoi(args.at(1))) && !checkArgPosY(stoi(args.at(2)))){
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "nofood" && !checkArgPosX(stoi(args.at(1))) && !checkArgPosY(stoi(args.at(2)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "empty" && !checkArgPosX(stoi(args.at(1))) && !checkArgPosY(stoi(args.at(2)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "see" && !checkArgPosX(stoi(args.at(1))) && !checkArgPosY(stoi(args.at(2)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "slide" && !checkArgDirection(args.at(1))) {
                    infoErroParam();
                    continue;
                }
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2), getReserva());
            }
            if(nArgs == 4) {
                if(args.at(0) == "animal" && !checkArgAnimais(args.at(1)) && !checkArgPosX(stoi(args.at(2))) && !checkArgPosY(stoi(args.at(3)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "food" && !checkArgAnimais(args.at(1)) && !checkArgPosX(stoi(args.at(2))) && !checkArgPosY(stoi(args.at(3)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "feed" && !checkArgIds(stoi(args.at(1)))) {
                    infoErroParam();
                    continue;
                }
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2), args.at(3), getReserva());
            }
            if(nArgs == 5) {
                if(args.at(0) == "feed" && !checkArgPosX(stoi(args.at(1))) && !checkArgPosY(stoi(args.at(2)))) {
                    infoErroParam();
                    continue;
                }
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2), args.at(3), args.at(4), getReserva());
            }
            if(flag) {
                string cmd{comandos.at(pos-1).getCmd()};
                infoErroNumArgs(cmd);
                getHelp(cmd, 3); // executa o comando help pq deu erro num comando
            }
            if(flag == -1) {
                flag = getHelp(args.at(1), 1);
            } // executa o comando help
            if(flag == -2)
                on = false; // exit
            if(flag == -3) {
                infoAboutId(stoi(args.at(1)));
            }

            infoToUser();
            infoShowReserva();
        }
    } while(on);
}
