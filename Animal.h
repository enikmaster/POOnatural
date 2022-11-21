#ifndef POONATURAL_ANIMAL_H
#define POONATURAL_ANIMAL_H
#include <string>
#include <vector>
#include <iostream>
#include "Alimento.h"
using namespace std;

class Animal {
private:
    int x, y;
    unsigned animalID;
    char letra;
    int fome;
    int hp;
    int peso;
public:
    // construtres destrutores
    Animal();
    ~Animal();
    // getters
    string getAnimalName();
    // setters
    void setAnimalName();
    void move(int x, int y);
    void checkSurroundings(int x, int y, int radius);
    int escolhePeso();
};
/*
class Coelho : public Animal {
public:
    Coelho();
    int SCoelho;
};
*/

#endif //POONATURAL_ANIMAL_H
