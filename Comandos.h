#ifndef TRABALHOPRATICO_COMANDOS_H
#define TRABALHOPRATICO_COMANDOS_H
#include "Includes.h"
#include "Reserva.h"
#include "Terminal.h"

using namespace std;
void getReservaDims(int& DimX, int& DimY, term::Window &janela);
int numArgs(stringstream& teste, string& temp);
vector<string> split(const string& line);
void getInput(Reserva& reserva, term::Window &janela1, term::Window &janela2, term::Window &janela3);
vector<string> split(const string& line);
int numArgs(std::stringstream& teste, std::string&temp );
bool verificaCmd(const string &cmd, term::Window &janela);
bool verificaEspecie(string &esp, term::Window &janela);
bool verificaSintaxe(int nArgs, int nArgsExp);
bool verificaAlimento(string &tipo, term::Window &janela);
bool verificaDirecao(string &dir, term::Window &janela);
bool verificaXY(const int &lin, const int &col, const Reserva& reserva, term::Window &janela);
bool verificaId(const int &id, const Reserva& reserva);
void criaAnimal(char especie, term::Window &janela, term::Window &janela2);
void criaAnimal(char especie, int lin, int col, term::Window &janela, term::Window &janela2);
void killAnimal(int lin, int col, term::Window &janela);
void killAnimal(int id, term::Window &janela);
void placeAlimento(char tipo, term::Window &janela);
void placeAlimento(char tipo, int lin, int col, term::Window &janela);
void feedDirectly(int lin, int col, int nut, int tox, term::Window &janela);
void feedId(int id, term::Window &janela);
void removeAlimento(int lin, int col, term::Window &janela);
void removeAlimento(int id, term::Window &janela);
void deletePos(int lin, int col, term::Window &janela);
void checkPos(int lin, int col, term::Window &janela);
void checkId(int id, term::Window &janela);
void tick(term::Window &janela);
void tick(int pausa, term::Window &janela);
void listIdsReserva(term::Window &janela);
void listIdsWindow(term::Window &janela);
void restore(string nome, term::Window &janela);
void store(string nome, term::Window &janela);
void deslocaAreaViz(string dir, int tamanho, term::Window &janela);
void infoToUser(term::Window &janela);
void reservaInfo(Reserva& reserva, term::Window& janelaInfo);
void checkComandoUser(const string& nomeFicheiro, term::Window &janela1, term::Window &janela2);

//bool verificaAnimal(int nArgs, vector<string> &args, Reserva &reserva);

#endif //TRABALHOPRATICO_COMANDOS_H
