#include "Interface.h"
#include "Save.h"
#include "../Reserva/Local.h"
#include "../Alimentos/Alimento.h"
#include "../Animais/Animal.h"
//uniform_int_distribution<> dimR(16, 500);
//uniform_int_distribution<> movimento(1, 2);
//mt19937 gen;

Interface::Interface()
        : originX(0), originY(0), zoo(nullptr), on(true), wReserva(term::Window(0, 0, 18, 18)), wInfo(term::Window(19, 0, 99, 18)), wInputs(term::Window(0, 18, 118, 5)) {
    wReserva << move_to(0, 0);
    mvprintw(0,1," Reserva ");
    wInfo << set_color(0) << move_to(0, 0);
    wInputs << set_color(0) << move_to(0, 0);
    mvprintw(18,1," Input ");
};
Interface::~Interface() {
    clearSaves();
    delete zoo;
}
/*Interface::Interface(Reserva* reserva)
        : originX(0), originY(0), zoo(reserva), wReserva(term::Window(0, 0, 18, 18)), wInfo(term::Window(19, 0, 99, 18)), wInputs(term::Window(0, 18, 118, 5)) {
    this->zoo->incContadorIds();
    wReserva << set_color(0) << move_to(0, 0);
    mvprintw(0,1," Reserva ");
    wInfo << set_color(0) << move_to(0, 0);
    //mvwprintw((0,34,"Info");
    wInputs << set_color(0) << move_to(0, 0);
    mvprintw(18,1," Input ");
}*/
// externas
// divide o input em várias strings e devolve um vetor com tudo
vector<string> split(const string& input) {
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i{0};
    while (i != input.size()) {
        while (i != input.size() && isspace(input.at(i)))
            ++i;
        string_size j{i};
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
int countArgs(stringstream& input, string& temp) {
    int cnt{0};
    while(input >> temp)
        ++cnt;
    return cnt;
}
// verifica e devolve as dimensoes da reserva a ser criada
void Interface::getReservaDims() {
    string input{};
    bool flag {false};
    do {
        wInfo.clear();
        refresh();
        wInfo << move_to(0, 0) << "Bem-Vindo!";
        wInfo << move_to(0, 1) << "Reserva Natural POO";
        wInfo << move_to(0, 2) << "Para iniciar a Reserva deve indicar as dimensoes. O maximo admitido e' 500 e o minimo e' 16.";
        wInfo << move_to(0, 3) << "Se pretender uma Reserva criada com dimensoes aleatorias, coloque 0 0.";
        wInputs << move_to(0, 0) << "Insira a dimensao da reserva (altura comprimento) ou 0 0 para um tamanho aleatorio: ";
        wInputs << move_to(0, 1);
        wInputs >> input;
        stringstream iss (input);
        string temp{};
        int nArgs {countArgs(iss, temp)};
        if(nArgs > 2 || nArgs == 0) {
            wInfo << move_to(0, 6) << "Numero de argumentos invalido...";
            continue;
        }
        vector<string> args {split(input)};
        if((stoi(args.at(0)) == 0) && (stoi(args.at(1)) == 0)) {
            //DimX = dimR(gen);
            //DimY = dimR(gen);
            Reserva* pReserva{new Reserva(16 + (rand() % 485), 16 + (rand() % 485))};
            zoo = pReserva;
            flag = true;
        }
        if((stoi(args.at(0)) >= 16 && stoi(args.at(0)) <= 500) && (stoi(args.at(1)) >= 16 && stoi(args.at(1)) <= 500)) {
            Reserva* pReserva{new Reserva(stoi(args.at(0)), stoi(args.at(1)))};
            zoo = pReserva;
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
    if(writePos == 1)
        infoTamanhoReserva();
    for(auto& comando : comandos) {
        if(cmd == comando.getCmd()) {
            wInfo << move_to(0, writePos) << comando.getCmd() << " " << comando.getArgs();
            wInfo << move_to(0, ++writePos) << comando.getDescr();
            writePos += 2;
        }
    }
    return 0;
}
// devolve uma cópia do ponteiro da reserva atual
Reserva* Interface::getReserva() const {
    Reserva* pCopiaReserva {zoo};
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
// tamanho da reserva
void Interface::infoTamanhoReserva() {
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
}
// mensagem de sucesso
void Interface::infoSucesso() {
    wInfo << "Comando executado com sucesso!";
}
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
        infoTamanhoReserva();
        wInfo << move_to(0,1) << "Demasiados argumentos...";
        infoToUser();
    }
    if(num < 1) {
        infoTamanhoReserva();
        wInfo << move_to(0, 1) << "Sem instrucoes...";
        infoToUser();
    }
}
// envia para o user um erro de comando desconhecido
void Interface::infoErroCmdDesc() {
    infoTamanhoReserva();
    wInfo << move_to(0, 1) << "Comando desconhecido...";
    infoToUser();
}
// envia para o user um erro de comando com número de argumentos errado
void Interface::infoErroNumArgs(string& cmd) {
    infoTamanhoReserva();
    wInfo << move_to(0, 1) << "Comando "<< cmd <<" com numero de argumentos invalido...";
}
// envia para o user um erro parametros inválidos
void Interface::infoErroParam() {
    infoTamanhoReserva();
    wInfo << move_to(0, 1) << "Um dos parametros nao e' valido.";
}
// envia para o user um erro de local vazio
void Interface::infoErroLocalVazio() {
    infoTamanhoReserva();
    wInfo << move_to(0, 1) << "Este local encontra-se vazio...";
}
void Interface::infoErroNoEspecie() {
    infoTamanhoReserva();
    wInfo << move_to(0, 1) << "Animal desconhecido...";
}
void Interface::infoErroNoFood() {
    infoTamanhoReserva();
    wInfo << move_to(0, 1) << "Alimento desconhecido...";
}
void Interface::infoErroForaReserva() {
    infoTamanhoReserva();
    wInfo << move_to(0, 1) << "Esta a tentar criar algo fora da reserva...";
}
void Interface::infoErroFileOpen() {
    infoTamanhoReserva();
    wInfo << move_to(0, 1) << "Erro a abrir o ficheiro...";
}
// mostra a reserva na janela certa
void Interface::infoShowReserva() {
    wReserva.clear();
    refresh();
    for( int i {0}; i < 16; ++i) {
        for( int j {0}; j < 16; ++j) {
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
// comando Anim
int Interface::infoAnim() {
    infoTamanhoReserva();
    int linha {0};
    for(auto& animal : zoo->animais) {
        int index {0};
        for(auto& letra : letraEspecies) {
            if(letra == animal->getLetra()) {
                wInfo << move_to(0, ++linha) << "Id: "<< animal->getAnimalId() << " | Saude: " << animal->getSaude() << " | Especie: " << especie.at(index);
            }
            ++index;
        }
    }
    wInfo << move_to(0, linha + 2);
    infoSucesso();
    return 0;
}
// comando Visanim
int Interface::infoVisanim() {
    infoTamanhoReserva();
    int areaVisivelX {getOriginX() + 15};
    int areaVisivelY {getOriginY() + 15};
    int linha {0};
    for (auto& animal : zoo->animais) {
        if ((animal->getPosX() <= areaVisivelX && animal->getPosX() >= getOriginX()) && (animal->getPosY() <= areaVisivelY && animal->getPosY() >= getOriginY()) ) {
            int index {0};
            for(auto& letra : letraEspecies) {
                if(letra == animal->getLetra())
                    wInfo << move_to(0, ++linha) << "Id: "<< animal->getAnimalId() << " | Saude: " << animal->getSaude() << " | Especie: " << especie.at(index);
                ++index;
            }
        }
    }
    wInfo << move_to(0, linha + 2);
    infoSucesso();
    return 0;
}
// comando Alim
int Interface::infoAlim() {
    infoTamanhoReserva();
    int linha {0};
    for(auto& alim : zoo->alimentos) {
        int index {0};
        for(auto& letra : letraAlimentos) {
            if(letra == alim->getLetra())
                wInfo << move_to(0, ++linha) << "Id: "<< alim->getFoodId() << " | Nutri: " << alim->getNutri() << " | Tipo: " << tipoAlim.at(index);
            ++index;
        }
    }
    wInfo << move_to(0, linha + 2);
    infoSucesso();
    return 0;
}
// comando Visalim
int Interface::infoVisalim() {
    infoTamanhoReserva();
    int areaVisivelX {getOriginX() + 15};
    int areaVisivelY {getOriginY() + 15};
    int linha {0};
    for (auto& alim : zoo->alimentos) {
        if ((alim->getPosX() <= areaVisivelX && alim->getPosX() >= getOriginX()) && (alim->getPosY() <= areaVisivelY && alim->getPosY() >= getOriginY()) ) {
            int index {0};
            for(auto& letra : letraAlimentos) {
                if(letra == alim->getLetra())
                    wInfo << move_to(0, ++linha) << "Id: "<< alim->getFoodId() << " | Nutri: " << alim->getNutri() << " | Tipo: " << tipoAlim.at(index);
                ++index;
            }
        }
    }
    wInfo << move_to(0, linha + 2);
    infoSucesso();
    return 0;
}
// Comando info <id>
int Interface::infoAboutId(int eid) {
    infoTamanhoReserva();
    int linha {0};
    for(auto& alimento : zoo->alimentos) {
        if(alimento->getFoodId() == eid) {
            wInfo << move_to(0, ++linha) << "Nome: "<< alimento->getLetra() << alimento->getFoodId();
            wInfo << move_to(0, ++linha) << "Id: "<< alimento->getFoodId();
            wInfo << move_to(0, ++linha) << "Posicao X: "<< alimento->getPosX() << " Posicao Y: " << alimento->getPosY();
            wInfo << move_to(0, ++linha) << "Valor nutritivo: " << alimento->getNutri();
            wInfo << move_to(0, ++linha) << "Valor toxicidade: " << alimento->getToxic();
            wInfo << move_to(0, ++linha) << "Validade: " << alimento->getDuracao() << " turnos";
            wInfo << move_to(0, ++linha) << "Cheiros:";
            for(int i {0}; i < alimento->getQuantidadeCheiros(); ++i) {
                wInfo << move_to(0, ++linha) << "   " << alimento->getCheiro(i);
            }
            return 0;
        }
    }
    for(auto& animal : zoo->animais) {
        if(animal->getAnimalId() == eid) {
            wInfo << move_to(0, ++linha) << "Nome: "<< animal->getLetra() << animal->getAnimalId();
            wInfo << move_to(0, ++linha) << "Id: "<< animal->getAnimalId();
            wInfo << move_to(0, ++linha) << "Posicao X: "<< animal->getPosX() << " Posicao Y: " << animal->getPosY();
            wInfo << move_to(0, ++linha) << "Fome: " << animal->getFome();
            wInfo << move_to(0, ++linha) << "Saude: " << animal->getSaude();
            wInfo << move_to(0, ++linha) << "Idade: " << animal->getIdade() << " turnos";
            wInfo << move_to(0, ++linha) << "Peso: " << animal->getPeso();
            wInfo << move_to(0, ++linha) << "Velocidade maxima: " << animal->getdeslMax();
            // falta um ciclo para o registo alimentar ou indicar o tamanho do registo
            break;
        }
    }
    if(linha != 0) {
        wInfo << move_to(0, linha + 2);
        infoSucesso();
    } else {
        wInfo << move_to(0, linha + 1);
        infoErroNoEspecie();
    }
    return 0;
}
// comando See
int Interface::infoSee(int posX, int posY) {
    infoTamanhoReserva();
    int linha {2};
    int reLinha {2};
    if(!zoo->locaisOcupados.empty()) {
        int numOcupas {0};
        for(auto& alimento : zoo->alimentos) {
            if(alimento->getPosX() == posX && alimento->getPosY() == posY) {
                wInfo << move_to(numOcupas*25, ++linha) << "Nome: "<< alimento->getLetra() << alimento->getFoodId();
                wInfo << move_to(numOcupas*25, ++linha) << "Id: "<< alimento->getFoodId();
                wInfo << move_to(numOcupas*25, ++linha) << "Valor nutritivo: " << alimento->getNutri();
                wInfo << move_to(numOcupas*25, ++linha) << "Valor toxicidade: " << alimento->getToxic();
                wInfo << move_to(numOcupas*25, ++linha) << "Validade: " << alimento->getDuracao() << " turnos";
                wInfo << move_to(numOcupas*25, ++linha) << "Cheiros:";
                for(int i = 0; i < alimento->getQuantidadeCheiros();++i) {
                    wInfo << move_to(0, ++linha) << "   " << alimento->getCheiro(i);
                }
                ++numOcupas;
            }
        }
        for(auto& animal : zoo->animais) {
            reLinha = 2;
            if(animal->getPosX() == posX && animal->getPosY() == posY) {
                wInfo << move_to(numOcupas*25, ++reLinha) << "Nome: "<< animal->getLetra() << animal->getAnimalId();
                wInfo << move_to(numOcupas*25, ++reLinha) << "Id: "<< animal->getAnimalId();
                wInfo << move_to(numOcupas*25, ++reLinha) << "Fome: " << animal->getFome();
                wInfo << move_to(numOcupas*25, ++reLinha) << "Saude: " << animal->getSaude();
                wInfo << move_to(numOcupas*25, ++reLinha) << "Idade: " << animal->getIdade() << " turnos";
                wInfo << move_to(numOcupas*25, ++reLinha) << "Peso: " << animal->getPeso();
                wInfo << move_to(numOcupas*25, ++reLinha) << "Velocidade maxima: " << animal->getdeslMax();
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
    wInfo << move_to(0, (linha >= reLinha) ? linha + 2 : reLinha + 2);
    infoSucesso();
    return 0;
}
// actions
// verifica se a especie animal é válida
bool Interface::checkArgAnimais(string& arg) const {
    char temp{(char) toupper(arg.at(0))};
    for(auto& letra : letraEspecies){
        if(letra == temp)
            return true;
    }
    return false;
}
// verifica se o tipo de alimento é válido
bool Interface::checkArgAlimentos(string& arg) const {
    char temp {(char)tolower(arg.at(0))};
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
// verifica se a posição está ocupada com Animal
bool Interface::checkAnimAtPos(int posX, int posY) const{
    for(auto& animal : zoo->animais) {
        if(animal->getPosX() == posX && animal->getPosY() == posY)
            return true;
    }
    return false;
}
// verifica se a posição está ocupada com Animal
bool Interface::checkAlimAtPos(int posX, int posY) const{
    for(auto& alimento : zoo->alimentos) {
        if(alimento->getPosX() == posX && alimento->getPosY() == posY)
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
    int index {0};
    for(auto& comando : comandos) {
        ++index;
        if(comando.getCmd() == arg)
            return index;
    }
    return 0;
}
// comando slide
int Interface::modifyOriginVis(const string& direction, int value) {
    if(direction == "up" || direction == "KEY_UP")
        (getOriginY() - value < 0) ? setOriginY(0) : setOriginY(getOriginY() - value);
    if(direction == "down" || direction == "KEY_DOWN")
        (getOriginY() + value > zoo->getDimY() - 16) ? setOriginY(zoo->getDimY() - 16) : setOriginY(getOriginY() + value);
    if(direction == "left" || direction == "KEY_LEFT")
        (getOriginX() - value < 0) ? setOriginX(0) : setOriginX(getOriginX() - value);
    if(direction == "right" || direction == "KEY_RIGHT")
        (getOriginX() + value > zoo->getDimX() - 16) ? setOriginX(zoo->getDimX() - 16) : setOriginX(getOriginX() + value);
    wInfo << move_to(0, 2);
    infoSucesso();
    return 0;
}
// adiciona um novo save game
int Interface::addSave(string nome) {
    wInfo << move_to(0,1) << "Reserva '" << nome << "' guardada com sucesso";
    // duplica a reserva
    Reserva* pReserva {new Reserva(*zoo)};
    // passa a reserva nova para o Save
    Save* pSave {new Save(std::move(nome), pReserva)};
    // guarda o save num vector de Saves
    saves.push_back(pSave);
    wInfo << move_to(0,2);
    infoSucesso();
    wInfo << move_to(0,3);
    infoAboutId(pReserva->animais[0]->getAnimalId());
    return 0;
}
// reinicia uma reserva guardada
int Interface::restoreSave(const string& nome) {
    for(auto& save : saves) {
        if(save->getNome() == nome) {
            setSavedZoo(save->getReservaSave());
            break;
        }
    }
    return 0;
}
// elimina todos os save games
void Interface::clearSaves() {
    for(vector<Save*>::iterator save {saves.begin()}; save != saves.end(); ) {
        (*save)->clearReserva();
        delete *save;
        saves.erase(save);
    }
}
// start simulation
void Interface::start() {
    getReservaDims();
    wInfo.clear();
    refresh();
    wInfo << zoo->getAsString();
    bool on {true};
    infoShowReserva();
    vector<string> inputsFromFile;
    do {
        vector<string> args;
        int nArgs{0};
        if(!inputsFromFile.empty()) {
            stringstream iss(inputsFromFile.at(0));
            string temp{};
            nArgs = countArgs(iss, temp);
            // divide a string em palavras
            args = split(inputsFromFile.at(0));
            inputsFromFile.erase(inputsFromFile.begin());
        } else {
            // pede informação ao user
            infoToUser();
            string userInput{getInput()};
            wInputs.clear();
            refresh();
            stringstream iss(userInput);
            string temp{};
            nArgs = countArgs(iss, temp);
            // verifica se os argumentos introduzidos estão dentro dos limites válidos
            if (nArgs < 1 || nArgs > 5) {
                infoErroArgs(nArgs);
                continue;
            }
            // divide a string em palavras
            args = split(userInput);
        }
        // verifica se o comando existe
        int posCmd {findComando(args.at(0))};
        if(!posCmd) {
            infoErroCmdDesc();
            continue;
        } else {
            infoTamanhoReserva();
            int flag {0};
            if(nArgs == 1) {
                if (args.at(0) == "KEY_UP" || args.at(0) == "KEY_DOWN" || args.at(0) == "KEY_LEFT" || args.at(0) == "KEY_RIGHT" ){
                    // executa os comandos sem argumentos
                    flag = comandos.at(22).executa(args.at(0), getReserva(), this);
                } else {
                    // executa os comandos sem argumentos
                    flag = comandos.at(posCmd - 1).executa(args.at(0), getReserva(), this);
                }
            }
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
                if(args.at(0) == "load") {
                    flag = comandos.at(posCmd-1).executa(args.at(0), args.at(1), inputsFromFile, this);
                } else {
                    flag = comandos.at(posCmd-1).executa(args.at(0), args.at(1), getReserva(), this);
                }
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
                    for(int rep {1}; rep <= stoi(args.at(1)); ++rep) {
                        flag = comandos.at(posCmd-1).executa(args.at(0), getReserva(), this);
                        infoShowReserva();
                        sleep(stoi(args.at(2)));
                    }
                } else {
                    flag = comandos.at(posCmd-1).executa(args.at(0), args.at(1), args.at(2), getReserva(), this);
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
                flag = comandos.at(posCmd-1).executa(args.at(0), args.at(1), args.at(2), args.at(3), getReserva());
            }
            if(nArgs == 5) {
                // executa os comandos com 4 argumentos
                if(args.at(0) == "feed") {
                    if( !checkArgPosX(stoi(args.at(1))) ) {
                        infoErroForaReserva();
                        continue;
                    }
                    if( !checkArgPosY(stoi(args.at(2))) ) {
                        infoErroForaReserva();
                        continue;
                    }
                    if( !checkAnimAtPos(stoi(args.at(1)), stoi(args.at(2))) ) {
                        infoErroLocalVazio();
                    }
                }
                flag = comandos.at(posCmd-1).executa(args.at(0), args.at(1), args.at(2), args.at(3), args.at(4), getReserva());
            }
            if(flag == 1) { // flag tem o valor 1
                string cmd{comandos.at(posCmd-1).getCmd()};
                infoErroNumArgs(cmd);
                // executa o comando help pq deu erro num comando
                getHelp(cmd, 3);
            }
            if(flag == -1) {
                // executa o comando help
                flag = getHelp(args.at(1), 1);
            }
            if(flag == -2)
                // sai do while loop
                on = false;

            infoToUser();
            infoShowReserva();
        }
    } while(on);
}