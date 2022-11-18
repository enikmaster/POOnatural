#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include "Alimento.h"


using namespace std;

Animal::Animal() {

}
Coelho::Coelho() {
    letra = 'C';
    SCoelho = 20;
    escolhePeso();
    checkSurroundings();
    move();
}

int Coelho::escolhePeso() {
    srand(time(0));
    int random = rand() % 4 + 1 ;
    return random;
}

void Animal::move(int x=0, int y=0) {
    srand(time(0));
    int desl = rand() % 2;
    if (desl = 1) {
        lin += x;
        col += y;
        cout << "mexi 1!\n";
    } else {
        lin = x + 2;
        col = y +2;
        cout << "mexi 2!\n";
    }
}

void Animal::checkSurroundings() {
    int radius = 4;
    int area = M_PI * pow(radius,2);

    // se algo estiver dentro do circulo -> detetado n sei como
}
