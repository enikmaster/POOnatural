#include "Animal.h"
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include "Animal.h"


using namespace std;

Animal::Animal() {
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
*/
int Animal::escolhePeso() {
    srand(time(0));
    int random = rand() % 4 + 1 ;
    return random;
}

void Animal::move(int x, int y) {
    srand(time(0));
    int desl = rand() % 2 + 1;
    if (desl == 1) {
        this->posX += x;       // this->x é o x privado de Animal, o x branco é o parametro cujo valor vai alterar o private
        this->posY += y;
        cout << "mexi 1!\n";
    } else {
        this->posX += x;
        this->posY += y;
        cout << "mexi 2!\n";
    }
}

void Animal::checkSurroundings(int x, int y, int radius) {
    // x e y = posicao actual do animal
    // radius = quantas posiçoes ele consegue ver
    int lenTotal = ((radius * 2) + 1) * 2;

    for (int i = y+radius; i > y-radius; i--) {
        for (int j = x-radius; j < x+radius; j++) {
            if ( i == y && j == x ) {
                cout << "Nao verifica a posicao onde esta" << endl;
                continue;
            }
            // se algo estiver dentro do circulo -> detetado n sei como
        }
    }
}