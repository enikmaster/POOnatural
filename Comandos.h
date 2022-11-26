#ifndef TRABALHOPRATICO_COMANDOS_H
#define TRABALHOPRATICO_COMANDOS_H
#include <string>
#include <vector>
#include <iostream>
#include "Alimento.h"
#include "Animal.h"
using namespace std;
void getInput();
vector<string> split(const string& line);
int numArgs(std::stringstream& teste, std::string&temp );
bool verCmd(const string &cmd);
bool verEsp(string &esp);
bool verAli(string &tipo);
bool verDir(string &dir);
bool verXY(const int &lin, const int &col);
bool verId(const int &id);
void checkComandoUser(string nomeFicheiro);
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
void tick(int instante);
void tick(int instante, int pausa);
void listIdsReserva();
void listIdsWindow();
void restore(string nome);
void store(string nome);
void deslocaAreaViz(string dir, int lin, int col);



#endif //TRABALHOPRATICO_COMANDOS_H
