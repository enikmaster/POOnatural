#include "../Reserva.h"
#include "Alimento.h"


Alimento::Alimento() {};
Alimento::~Alimento() {};

void Alimento::podridao() {};
//setters e getters

int Alimento::getPosX() {return this->posX;}
int Alimento::getPosY() {return this->posY;}
void Alimento::setPosX(int a) { this->posX = a;}
void Alimento::setPosY(int a) { this->posY = a;}

int Alimento::getLetra() { return this->letra;}
void Alimento::setLetra(char a) { this->letra = a;}

int Alimento::getTick() { return this->tick;}

int Alimento::getNutri() { return this->nutri;}
void Alimento::setNutri(int a) { this->nutri = a;}

int Alimento::getToxic() { return this->toxic;}
void Alimento::setToxic(int a) { this->toxic = a;}

string Alimento::getCheiro1() { return this->cheiro1;}
string Alimento::getCheiro2() { return this->cheiro2;}
void Alimento::setCheiro1(string a) { this->cheiro1 = std::move(a);}
void Alimento::setCheiro2(string a) { this->cheiro2 = std::move(a);}