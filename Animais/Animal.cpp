#include "Animal.h"
#include "../Reserva.h"

Animal::Animal()   {
    //this->animalID = Reserva::getId();
}
Animal::~Animal() {
}

void Animal::fomeca() {};
void Animal::repro() {};

//setters e getters
int Animal::getPosX() {return this->posX;}
int Animal::getPosY() {return this->posY;}
void Animal::setPosX(int valorDeslocamento) { this->posX += valorDeslocamento;}
void Animal::setPosY(int valorDeslocamento) { this->posY += valorDeslocamento;}

int Animal::getdeslMin() { return this->deslMin;}
int Animal::getdeslMax() { return this->deslMax;}
void Animal::setdeslMin(int min) { this->deslMin = min;}
void Animal::setdeslMax(int max) { this->deslMax = max;}

char Animal::getLetra() { return this->letra;}
void Animal::setLetra(char a) { this->letra = a;}

int Animal::getPeso() { return this->peso;}
void Animal::setPeso(int a) { this->peso = a;}

int Animal::getPercepcao() { return this->percepcao;}
void Animal::setPercepcao(int a) { this->percepcao = a;}

int Animal::getFome() { return this->fome;}
void Animal::setFome(int a) { this->fome = a;}

int Animal::getTick() { return this->tick;}


void Animal::escolhePeso(int min, int max){
    int z = aleatorio(min, max);
    Animal::setPeso(z);
}

void Animal::move(int min, int max) {
    int desl = aleatorio(min, max);

    // Se random:
    int valX = aleatorio(-1,3);
    int valY = aleatorio(-1,3);
    Animal::setPosX((Animal::getPosX() + valX) * desl);
    Animal::setPosY((Animal::getPosY() + valY) * desl);
}

void Animal::checkSurroundings(int x, int y, int radius) {
    // x e y = posicao actual do animal
    // radius = quantas posiçoes ele consegue ver
    int lenTotal = ((radius * 2) + 1) * 2;

    for (int i = y+radius; i > y-radius; i--) {
        for (int j = x-radius; j < x+radius; j++) {
            if ( i == y && j == x ) {
                //cout << "Nao verifica a posicao onde esta" << endl;
                continue;
            }
            // se algo estiver dentro do circulo -> detetado n sei como
        }
    }
}


