#ifndef POONATURAL_ANIMAL_H
#define POONATURAL_ANIMAL_H
#include <string>
#include <vector>
#include <iostream>
#include "Alimento.h"
using namespace std;

class Animal {
public:
    // construtres destrutores
    Animal();
    ~Animal();
    // getters
    string getAnimalName();
    // setters
    void setAnimalName();
    // actions
    void checkSurroundings();
private:
    int lin, col;
    void move(int x, int y);
    const unsigned animalID;
    const int letra;
    int fome;
    int hp;
    int peso;
};

class Coelho : public Animal {
public:
    Coelho();
    int escolhePeso();
    void move();
private:
    char letra;
    int SCoelho;
};

#endif //POONATURAL_ANIMAL_H
