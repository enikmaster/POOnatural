#ifndef POONATURAL_ANIMAL_H
#define POONATURAL_ANIMAL_H
#include <string>
#include <vector>
#include <iostream>
#include "Alimento.h"
using namespace std;

class Animal {
public:

    //Animal(char especie, int linha, int coluna);
    Animal();
    ~Animal();
    // getters
    string getAnimalName();
    // setters
    void setAnimalName();
    int lin, col;
    void move(int x, int y);
    const unsigned animalID;
    const int letra;
    int fome;
    int hp;
    int peso;
    void checkSurroundings();

private:

};

class Coelho : public Animal {
public:
    Coelho();
    char letra;
    int SCoelho;
    int escolhePeso();
    void move();
};


#endif //POONATURAL_ANIMAL_H
