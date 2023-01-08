#ifndef INC_03_LEARN_INTERFACE_H
#define INC_03_LEARN_INTERFACE_H
#include "../Includes.h"
#include "../Terminal.h"
#include "../Comandos/Comando.h"

class Animal;
class Alimento;
class Local;
class Save;
using namespace term;
class Interface {
    int originX;
    int originY;
    Window wReserva;
    Window wInfo;
    Window wInputs;
    Reserva* zoo;
    vector<Save*> saves;
    const vector<string> directions {"up", "down", "left", "right"};
    const vector<char> letraEspecies {'C','O', 'L', 'G', 'M', 'H'};
    const vector<char> letraAlimentos {'r', 't', 'p', 'b', 'a'};
    const vector<string> especie {"Coelho", "Ovelha", "Lobo", "Canguru", "Macaco", "Humano"};
    const vector<string> tipoAlim {"Relva", "Cenoura", "Corpo", "Bife", "Banana"};
    const vector<Comando> comandos {{"animal","Cria um novo animal na reserva. O utilizador indica a especie e a posicao X e Y dentro da reserva.","<especie> <posicao_X> <posicao_Y>"},
                               {"animal","Cria um novo animal na reserva. O utilizador indica a especie. A posicao dentro da reserva e' atribuida aleatoraiamente.","<especie>"},
                               {"kill","Mata um animal da reserva. O utilizador indica a posicao X e Y dentro da reserva.","<posicao_X> <posicao_Y>"},
                               {"killid","Mata um animal da reserva. O utilizador indica o id do animal.","<id>"},
                               {"food","Cria um novo alimento na reserva. O utilizador indica o tipo e a posicao X e Y dentro da reserva.","<tipo> <posicao_X> <posicao_Y>"},
                               {"food","Cria um novo alimento na reserva. O utilizador indica o tipo. A posicao dentro da reserva e' atribuida aleatoraiamente.","<tipo>"},
                               {"feed","Alimenta um animal da reserva. O utilizador indica a posicao X e Y dentro da reserva, os nutrientes e a toxicidade.","<posicao_X> <posicao_Y> <nutrientes> <toxicidade>"},
                               {"feedid","Alimenta um animal da reserva. O utilizador indica o id, os nutrientes e a toxicidade.","<id> <nutrientes> <toxicidade>"},
                               {"nofood","Remove um alimento da reserva. O utilizador indica a posicao X e Y dentro da reserva.","<posicao_X> <posicao_Y>"},
                               {"nofood","Remove um alimento da reserva. O utilizador indica o id do alimento.","<id>"},
                               {"empty","Elimina um elemento do que quer que esteja na reserva. O utilizador indica a posicao X e Y dentro da reserva.","<posicao_X> <posicao_Y>"},
                               {"see","Ver o que se encontra numa posicao, indicando toda a informacao da posicao e das suas coisas. O utilizador indica a posicao X e Y.","<posicao_X> <posicao_Y>"},
                               {"info","Ver a informacao acerca de um elemento da reserva (alimento ou animal). O utilizador indica o id do elemento.","<id>"},
                               {"n","Avanca um turno."},
                               {"n","Avanca N turnos imediatamente.","<N_turnos>"},
                               {"n","Avanca N turnos com um intervalo de tempo entre eles.","<n_turnos> <tempo>"},
                               {"anim","Lista todos os animais da reserva."},
                               {"visanim","Lista todos os animais da area visivel da reserva."},
                               {"alim","Lista todos os animais da reserva."},
                               {"visalim","Lista todos os animais da area visivel da reserva."},
                               {"store","Armazena o estado da reserva em memoria, associando-lhe um nome. O utilizador indica um nome.","<nome>"},
                               {"restore","Reativa um estado da reserva previamente armazenado em memoria. O utilizador indica o nome.","<nome>"},
                               {"load","Carrega e executa comandos a partir de um ficheiro de texto. O utilizador indica o nome do ficheiro.","<nome_ficheiro>"},
                               {"slide","Desloca a area visivel da reserva na direcao indicada, com o tamanho de deslocacao especificado.","<direcao> <tamanho>"},
                               {"exit","Termina o programa."},
                               {"help","Apresenta o comando, a sintaxe e uma descricao do que faz.","<comando>"}};

public:
    Interface(Reserva* reserva);

    // getters
    int getOriginX() const {return originX;}
    int getOriginY() const {return originY;}
    string getInput();
    int getHelp(string& cmd, int writePos);
    Reserva* getReserva() const;
    // setters
    void setOriginX(int newOriginX) {this->originX = newOriginX;}
    void setOriginY(int newOriginY) {this->originY = newOriginY;}
    void setSavedZoo(Reserva* reservaSaved);
    // informations
    void infoTamanhoReserva();
    void infoSucesso();
    void infoToUser();
    void infoErroArgs(int num);
    void infoErroCmdDesc();
    void infoErroNumArgs(string& cmd);
    void infoErroParam();
    void infoErroLocalVazio();
    void infoErroNoEspecie();
    void infoErroNoFood();
    void infoErroForaReserva();
    void infoErroFileOpen();
    void infoShowReserva();
    int infoAboutId(int eid);
    int infoAnim();
    int infoVisanim();
    int infoAlim();
    int infoVisalim();
    int infoSee(int posX, int posY);
    // actions
    bool checkArgAnimais(string& arg) const;
    bool checkArgAlimentos(string& arg) const;
    bool checkArgSaves(string& arg) const;
    bool checkArgDirection(string& arg) const;
    bool checkArgIds(int arg) const;
    bool checkArgPosX(int arg) const {return (arg < zoo->getDimX());};
    bool checkArgPosY(int arg) const {return (arg < zoo->getDimY());};
    bool checkAnimAtPos(int posX, int posY) const;
    bool checkAlimAtPos(int posX, int posY) const;
    bool checkVisibility(int posX, int posY) const;
    int findComando(string& arg);
    int modifyOriginVis(const string& direction, int value);
    int addSave(string nome);
    int restoreSave(const string& nome);
    void clearSaves();

    // start simulation
    void start();

    friend class Comando;
};
vector<string> split(const string& input);
int countArgs(stringstream& input, string& temp);
void getReservaDims(int& DimX, int& DimY, term::Terminal& janela);
#endif //INC_03_LEARN_INTERFACE_H