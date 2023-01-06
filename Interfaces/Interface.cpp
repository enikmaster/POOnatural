#include "Interface.h"
#include "Save.h"
#include "../Reserva/Local.h"
#include "../Alimentos/Alimento.h"
#include "../Animais/Animal.h"
//uniform_int_distribution<> dimR(16, 500);
//uniform_int_distribution<> movimento(1, 2);
//mt19937 gen;

Interface::Interface(Reserva* reserva)
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
// devolve uma cópia do ponteiro da reserva atual
Reserva* Interface::getReserva() const {
    Reserva* pCopiaReserva = zoo;
    return pCopiaReserva;
}
// setters
// substitui a reserva atual por uma reserva guardada anteriormente
void Interface::setSavedZoo(Reserva *reservaSaved) {
    zoo->deleteAll();
    delete zoo;
    zoo = reservaSaved;
}
// informations
// envia para o output uma mensagem
void Interface::infoToUser() {
    wInputs.clear();
    refresh();
    wInputs << term::move_to(0, 0) << "Insira um comando: ";
    wInputs << move_to(0, 1);
}
// envia um erro de número de argumentos fora dos limites para o user
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
// envia para o user um erro de comando desconhecido
void Interface::infoErroCmdDesc() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Comando desconhecido...";
    infoToUser();
}
// envia para o user um erro de comando com número de argumentos errado
void Interface::infoErroNumArgs(string& cmd) {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Comando "<< cmd <<" com numero de argumentos invalido...";
}
// envia para o user um erro parametros inválidos
void Interface::infoErroParam() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Um dos parametros nao e' valido.";
}
void Interface::infoErroNoEspecie() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Animal desconhecido...";
}
void Interface::infoErroNoFood() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Alimento desconhecido...";
}
void Interface::infoErroForaReserva() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    wInfo << move_to(0, 1) << "Esta a tentar criar algo fora da reserva...";
}
// mostra a reserva na janela certa
void Interface::infoShowReserva() {
    wReserva.clear();
    refresh();
    for( int i = 0; i < 16; ++i) {
        for( int j = 0; j < 16; ++j) {
            wReserva << move_to(j, i) << ".";
        }
    }
    if(!zoo->locaisOcupados.empty()) {
        for(auto& localOcupado : zoo->locaisOcupados) {
            if(checkVisibility(localOcupado->getLocalX(), localOcupado->getLocalY()) ) {
                wReserva << move_to(localOcupado->getLocalX() - getOriginX(), localOcupado->getLocalY() - getOriginY()) << localOcupado->getTipoOcupante();
            }
        }
    }
}


int Interface::infoAnim() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    string especie;
    int w = 1;
    vector<char>letras1{'C', 'O', 'L', 'G'};
    vector<string>letras2{"Coelho", "Ovelha", "Lobo", "Canguru"};

    for(auto& animal : zoo->animais) {
        for (int i = 0; i<letras1.size(); ++i){
            if (letras1[i] == animal->getLetra()) {
                especie = letras2[i];
                continue;
            }
        }
        wInfo << move_to(0, w) << "Id: "<< animal->getAnimalId() << " | Saude: " << animal->getSaude() << " | Especie: " << especie;
        ++w;
    }
    return 0;
}

int Interface::infoVisanim() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    int areaVisivelX = originX + 16;
    int areaVisivelY = originY + 16;
    int w = 1, newLine = 0;
    string especie;
    vector<char>letras1{'C', 'O', 'L', 'G'};
    vector<string>letras2{"Coelho", "Ovelha", "Lobo", "Canguru"};

    for (auto& animal : zoo->animais) {
        if (animal->getPosX() < areaVisivelX && animal->getPosX() >= originX) {
            if (animal->getPosY() < areaVisivelY && animal->getPosY() >= originY) {
                for (int i = 0; i<letras1.size(); ++i){
                    if (letras1[i] == animal->getLetra()) {
                        especie = letras2[i];
                        continue;
                    }
                }
                wInfo << move_to(0, w) << "Id: "<< animal->getAnimalId() << " | Saude: " << animal->getSaude() << " | Especie: " << especie;
                ++w;
                if (w % 3 == 0)
                    ++newLine;
            }
        }
    }
    return 0;
}

// Comando info <id>
int Interface::infoAboutId(int eid) {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
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
            return 0;
        }
    }
    for(auto& animal : zoo->animais) {
        if(animal->getAnimalId() == eid) {
            wInfo << move_to(0, 1) << "Nome: "<< animal->getLetra() << animal->getAnimalId();
            wInfo << move_to(0, 2) << "Id: "<< animal->getAnimalId();
            wInfo << move_to(0, 3) << "Posicao X: "<< animal->getPosX() << " Posicao Y: " << animal->getPosY();
            wInfo << move_to(0, 4) << "Fome: " << animal->getFome();
            wInfo << move_to(0, 5) << "Saude: " << animal->getSaude();
            wInfo << move_to(0, 6) << "Idade: " << animal->getIdade() << " turnos";
            wInfo << move_to(0, 7) << "Peso: " << animal->getPeso();
            wInfo << move_to(0, 8) << "Movimento maximo: " << animal->getdeslMax();
            wInfo << move_to(0, 9) << "Vivo: " << ((animal->getIsAlive()) ? "true" : "false" );
            //wInfo << move_to(0, 10) << "Alimentos perto: " << animal->getQuantidadeAlimentosPerto();
            // falta um ciclo para o registo alimentar ou indicar o tamanho do registo
            break;
        }
    }
    return 0;
}
int Interface::infoSee(int posX, int posY) {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    if(!zoo->locaisOcupados.empty()) {
        int numOcupas {0};
        for(auto& alimento : zoo->alimentos) {
            if(alimento->getPosX() == posX && alimento->getPosY() == posY) {
                wInfo << move_to(numOcupas*25, 3) << "Nome: "<< alimento->getLetra() << alimento->getFoodId();
                wInfo << move_to(numOcupas*25, 4) << "Id: "<< alimento->getFoodId();
                wInfo << move_to(numOcupas*25, 5) << "Valor nutritivo: " << alimento->getNutri();
                wInfo << move_to(numOcupas*25, 6) << "Valor toxicidade: " << alimento->getToxic();
                wInfo << move_to(numOcupas*25, 7) << "Validade: " << alimento->getDuracao() << " turnos";
                wInfo << move_to(numOcupas*25, 8) << "Cheiros:";
                for(int i = 0; i < alimento->getQuantidadeCheiros();++i) {
                    wInfo << move_to(0, 9+i) << "   " << alimento->getCheiro(i);
                }
                ++numOcupas;
            }
        }
        for(auto& animal : zoo->animais) {
            if(animal->getPosX() == posX && animal->getPosY() == posY) {
                wInfo << move_to(numOcupas*25, 4) << "Nome: "<< animal->getLetra() << animal->getAnimalId();
                wInfo << move_to(numOcupas*25, 5) << "Id: "<< animal->getAnimalId();
                wInfo << move_to(numOcupas*25, 6) << "Fome: " << animal->getFome();
                wInfo << move_to(numOcupas*25, 7) << "Saude: " << animal->getSaude();
                wInfo << move_to(numOcupas*25, 8) << "Idade: " << animal->getIdade() << " turnos";
                wInfo << move_to(numOcupas*25, 9) << "Peso: " << animal->getPeso();
                wInfo << move_to(numOcupas*25, 10) << "Velocidade maximo: " << animal->getdeslMax();
                ++numOcupas;
            }
        }
        if(numOcupas == 0) {
            wInfo << move_to(0, 1) << "Posicao "<< posX << " x " << posY << " vazia";
        } else {
            wInfo << move_to(0, 1) << "Posicao "<< posX << " x " << posY << " com "<< numOcupas<< " elementos.";
        }
    } else {
        wInfo << move_to(0, 1) << "Posicao "<< posX << " x " << posY << " vazia";
    }
    return 0;
}
//void Interface::infoTeste() {
//    wInfo.clear();
//    refresh();
//    wInfo << move_to(0,1) << "origem X: " << getOriginX();
//    wInfo << move_to(0,2) << "origem Y: " << getOriginY();
//}
// actions
// verifica se a especie animal é válida
bool Interface::checkArgAnimais(string& arg) const {
    char temp = (char)toupper(arg.at(0));
    for(auto& letra : letraEspecies){
        if(letra == temp)
            return true;
    }
    return false;
}
// verifica se o tipo de alimento é válido
bool Interface::checkArgAlimentos(string& arg) const {
    char temp = (char)tolower(arg.at(0));
    for(auto& letra : letraAlimentos){
        if(letra == temp)
            return true;
    }
    return false;
}
// verifica se o ficheiro Save existe
bool Interface::checkArgSaves(string& arg) const {
    for(auto& save : saves) {
        if(save->getNome() == arg)
            return true;
    }
    return false;
}
// verifica se a direção é válida
bool Interface::checkArgDirection(string& arg) const{
    for(auto& direction : directions){
        if(direction == arg)
            return true;
    }
    return false;
}
// verifica se o Id existe na reserva
bool Interface::checkArgIds(int arg) const{
    for(auto& local : zoo->locaisOcupados) {
        if(local->getOcupaId() == arg)
            return true;
    }
    return false;
}
// verifica se o elemento está visível
bool Interface::checkVisibility(int posX, int posY) const {
    return (posX >= getOriginX() && posX <= getOriginX() + 15 && posY >= getOriginY() && posY <= getOriginY() + 15);
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
// comando slide
int Interface::modifyOriginVis(const string& direction, int value) {
    if(direction == "up") {
        (getOriginY() - value < 0) ? setOriginY(0) : setOriginY(getOriginY() - value);
    }
    if(direction == "down") {
        (getOriginY() + value > zoo->getDimY() - 16) ? setOriginY(zoo->getDimY() - 16) : setOriginY(getOriginY() + value);
    }
    if(direction == "left") {
        (getOriginX() - value < 0) ? setOriginX(0) : setOriginX(getOriginX() - value);
    }
    if(direction == "right") {
        (getOriginX() + value > zoo->getDimX() - 16) ? setOriginX(zoo->getDimX() - 16) : setOriginX(getOriginX() + value);
    }
    return 0;
}
// adiciona um novo save game
int Interface::addSave(string nome) {
    // duplica a reserva
    Reserva* pReserva = new Reserva(*zoo);
    // passa a reserva nova para o Save
    Save* pSave = new Save(std::move(nome), pReserva);
    saves.push_back(pSave);
    return 0;
}
// reinicia uma reserva guardada
int Interface::restoreSave(const string& nome) {
    for(auto& save : saves) {
        if(save->getNome() == nome)
            setSavedZoo(save->getReservaSave());
    }
    return 0;
}
// elimina todos os save games
void Interface::clearSaves() {
    for(vector<Save*>::iterator save = saves.begin(); save != saves.end(); ) {
        (*save)->clearReserva();
        delete *save;
        saves.erase(save);
    }
}
// start simulation
void Interface::start() {
    wInfo << zoo->getAsString();
    bool on = true;
    infoShowReserva();
    do {
        // pede informação ao user
        infoToUser();
        string userInput{getInput()};
        wInputs.clear();
        refresh();
        stringstream iss (userInput);
        string temp{};
        int nArgs = countArgs(iss, temp);
        // verifica se os argumentos introduzidos estão dentro dos limites válidos
        if(nArgs < 1 || nArgs > 5) {
            infoErroArgs(nArgs);
            continue;
        }
        // divide a string em palavras
        vector<string> args = split(userInput);
        // verifica se o comando existe
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
                // executa os comandos sem argumentos
                flag = comandos.at(pos-1).executa( args.at(0), getReserva() );
            if(nArgs == 2) {
                // executa os comandos com 1 argumento
                if(args.at(0) == "animal" && !checkArgAnimais(args.at(1))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "killid" && !checkArgIds(stoi(args.at(1)))) {
                    infoErroParam();
                    continue;
                }
                if(args.at(0) == "food" && !checkArgAlimentos(args.at(1))) {
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
                // executa os comandos com 2 argumentos
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
                if(args.at(0) == "n") {
                    for(int rep = 1; rep <= stoi(args.at(1)); ++rep) {
                        flag = comandos.at(pos-1).executa(args.at(0), getReserva());
                        infoShowReserva();
                        sleep(stoi(args.at(2)));
                    }
                } else {
                    flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2), getReserva());
                }
            }
            if(nArgs == 4) {
                // executa os comandos com 3 argumentos
                if(args.at(0) == "animal") {
                    if( !checkArgAnimais(args.at(1)) ) {
                        infoErroNoEspecie();
                        continue;
                    }
                    if( !checkArgPosX(stoi(args.at(2))) ) {
                        infoErroForaReserva();
                        continue;
                    }
                    if( !checkArgPosY(stoi(args.at(3))) ) {
                        infoErroForaReserva();
                        continue;
                    }
                }
                if(args.at(0) == "food") {
                    if( !checkArgAlimentos(args.at(1)) ) {
                        infoErroNoFood();
                        continue;
                    }
                    if( !checkArgPosX(stoi(args.at(2))) ) {
                        infoErroForaReserva();
                        continue;
                    }
                    if( !checkArgPosY(stoi(args.at(3))) ) {
                        infoErroForaReserva();
                        continue;
                    }
                }
                if(args.at(0) == "feed" && !checkArgIds(stoi(args.at(1)))) {
                    infoErroParam();
                    continue;
                }
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2), args.at(3), getReserva());
            }
            if(nArgs == 5) {
                // executa os comandos com 4 argumentos
                if(args.at(0) == "feed" && !checkArgPosX(stoi(args.at(1))) && !checkArgPosY(stoi(args.at(2)))) {
                    infoErroParam();
                    continue;
                }
                flag = comandos.at(pos-1).executa(args.at(0), args.at(1), args.at(2), args.at(3), args.at(4), getReserva());
            }
            if(flag == 1) { // flag tem o valor 1
                string cmd{comandos.at(pos-1).getCmd()};
                infoErroNumArgs(cmd);
                getHelp(cmd, 3); // executa o comando help pq deu erro num comando
            }
            if(flag == -1) {
                // executa o comando help
                flag = getHelp(args.at(1), 1);
            }
            if(flag == -2) {
                // executa o comando exit
                clearSaves();
                on = false;
            }
            if(flag == -3)
                // executa o comando info <id>
                flag = infoAboutId(stoi(args.at(1)));
            if(flag == -4)
                // executa o comando save <nome-do-ficheiro>
                flag = addSave(args.at(1));
            if(flag == -5)
                // executa o comando restore <nome-do-ficheiro>
                flag = restoreSave(args.at(1));
            if(flag == -6)
                // executa o comando anim
                flag = infoAnim();
            if(flag == -7)
                // executa o comando visanim
                flag = infoVisanim();
            if(flag == -8)
                // executa o comando slide <direction> <tamanho>
                flag = modifyOriginVis(args.at(1), stoi(args.at(2)));
            if(flag == -9)
                // executa o comando see <posX> <posY>
                flag = infoSee(stoi(args.at(1)), stoi(args.at(2)));

            infoToUser();
            infoShowReserva();
        }
    } while(on);
}
