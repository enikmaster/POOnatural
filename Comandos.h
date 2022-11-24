#ifndef TRABALHOPRATICO_COMANDOS_H
#define TRABALHOPRATICO_COMANDOS_H
#include <string>
#include <vector>
#include <iostream>
#include "Alimento.h"
#include "Animal.h"
using namespace std;
void getInput();
void checkComandoUser(string &input);
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
void store(string nome);
void restore(string nome);



#endif //TRABALHOPRATICO_COMANDOS_H
