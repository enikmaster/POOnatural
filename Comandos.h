#ifndef TRABALHOPRATICO_COMANDOS_H
#define TRABALHOPRATICO_COMANDOS_H
#include "Includes.h"
#include "Reserva.h"

using namespace std;
void getReservaDims(int& DimX, int& DimY);
int numArgs(stringstream& teste, string& temp);
vector<string> split(const string& line);
void getInput(Reserva& reserva);
vector<string> split(const string& line);
int numArgs(std::stringstream& teste, std::string&temp );
bool verificaCmd(const string &cmd);
bool verificaEspecie(string &esp);
bool verificaSintaxe(int nArgs, int nArgsExp);
bool verificaAlimento(string &tipo);
bool verificaDirecao(string &dir);
bool verificaXY(const int &lin, const int &col, const Reserva& reserva);
bool verificaId(const int &id, const Reserva& reserva);
void checkComandoUser(const string& nomeFicheiro);
void criaAnimal(char especie);
void criaAnimal(char especie, int lin, int col);
void killAnimal(int lin, int col);
void killAnimal(int id);
void placeAlimento(char tipo);
void placeAlimento(char tipo, int lin, int col);
void feedDirectly(int lin, int col, int nut, int tox);
void feedId(int id);
void removeAlimento(int lin, int col);
void removeAlimento(int id);
void deletePos(int lin, int col);
void checkPos(int lin, int col);
void checkId(int id);
void tick();
void tick(int pausa);
void listIdsReserva();
void listIdsWindow();
void restore(string nome);
void store(string nome);
void deslocaAreaViz(string dir, int tamanho);
void infoToUser();

//bool verificaAnimal(int nArgs, vector<string> &args, Reserva &reserva);

#endif //TRABALHOPRATICO_COMANDOS_H
