#include "Animal.h"
#include "Terminal.h"

using namespace std;

Animal::Animal()   {
    //this->animalID = Reserva::getId();
}
Animal::~Animal() {
}
/*
Coelho::Coelho() {
    letra = 'C';
    SCoelho = 20;
    escolhePeso();
    checkSurroundings();
    move();
}

int Animal::setPeso() {
    srand(time(0));
    int peso = rand() % 4 + 1 ;
    return peso;
}*/

void Animal::move(int x, int y) {
    //srand(time(0));
    //int desl = rand() % 2 + 1;
    // falta decidir em que sentiddo o animal se move
    //this->posX += desl;       // this->x é o x privado de Animal, o x branco é o parametro cujo valor vai alterar o privat
    //this->posY += y;
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