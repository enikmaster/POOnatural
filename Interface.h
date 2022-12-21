#ifndef INC_03_LEARN_INTERFACE_H
#define INC_03_LEARN_INTERFACE_H
#include <iostream>
#include <algorithm>
#include "Terminal.h"
#include "Comandos/Comando.h"
#include "Reserva.h"


using namespace term;
class Interface {
    Window wReserva;
    Window wInfo;
    Window wInputs;
    Reserva zoo;
    vector<Comando> comandos ={{"animal","Cria um novo animal na reserva. O utilizador indica a especie e a posicao X e Y dentro da reserva.","<especie> <posicao_X> <posicao_Y>"},
                               {"animal","Cria um novo animal na reserva. O utilizador indica a especie. A posicao dentro da reserva e' atribuida aleatoraiamente.","<especie>"},
                               {"kill","Mata um animal da reserva. O utilizador indica a posicao X e Y dentro da reserva.","<posicao_X> <posicao_Y>"},
                               {"killid","Mata um animal da reserva. O utilizador indica o id do animal.","<id>"},
                               {"food","Cria um novo alimento na reserva. O utilizador indica o tipo e a posicao X e Y dentro da reserva.","<tipo> <posicao_X> <posicao_Y>"},
                               {"food","Cria um novo alimento na reserva. O utilizador indica o tipo. A posicao dentro da reserva e' atribuida aleatoraiamente.","<tipo>"},
                               {"feed","Alimenta um animal da reserva. O utilizador indica a posicao X e Y dentro da reserva, os nutrientes e a toxicidade.","<posicao_X> <posicao_Y> <nutrientes> <toxicidade>"},
                               {"feedid","Alimenta um animal da reserva. O utilizador indica o id, os nutrientes e a toxicidade.","<id> <nutrientes> <toxicidade>"},
                               {"nofood","*****","<posicao_X> <posicao_Y>"},
                               {"nofood","*****","<id>"},
                               {"empty","*****","<posicao_X> <posicao_Y>"},
                               {"see","*****","<posicao_X> <posicao_Y>"},
                               {"info","*****","<id>"},
                               {"n","Avanca um turno."},
                               {"n","Avanca N turnos imediatamente.","<N_turnos>"},
                               {"n","Avanca N turnos com um intervalo de tempo entre eles.","<n_turnos> <tempo>"},
                               {"anim","Lista todos os animais da reserva."},
                               {"visanim","Lista todos os animais da area visivel da reserva."},
                               {"store","*****","<nome>"},
                               {"restore","*****","<nome>"},
                               {"load","*****","<nome_ficheiro>"},
                               {"slide","Desloca a area visivel da reserva na direcao indicada, com o tamanho de deslocacao especificado.","<direcao> <tamanho>"},
                               {"exit","Termina o programa."},
                               {"help","Apresenta o comando, a sintaxe e uma descricao do que faz.","<comando>"}};
public:
    Interface(Reserva& hub);
    ~Interface() {}
    // getters
    string getTamanhoLoja() {return this->zoo.getAsString();}
    int getCntIds() {return zoo.getContadorIds();}
    string getInput();
    int getHelp(string& cmd, int writePos);
    // information to user
    void infoToUser();
    void infoErroArgs(int num);
    void infoErroCmdDesc();
    void infoErroNumArgs(string& cmd);
    // actions
    int findComando(string& arg);
    void start();
};
vector<string> split(const string& input);
int countArgs(stringstream& input, string& temp);
void getReservaDims(int& DimX, int& DimY, term::Terminal& janela);
#endif //INC_03_LEARN_INTERFACE_H
