#ifndef POONATURAL_ANIMAL_H
#define POONATURAL_ANIMAL_H
#include <string>
#include <vector>
#include <iostream>
#include "Alimento.h"
using namespace std;

struct registoAlimentar{
    string nome;
    int toxic;
    int nutri;
};

class Animal {
private:
    int posX, posY;
    unsigned animalID;
    char letra;
    int fome;
    int saude; //SAnimal
    int vida; //VAnimal (ao fim de x ticks, o animaal vai morrer)
    int peso;
    bool agressividade;
    struct registoAlimentar;
public:

    // constructores:
    Animal();
    ~Animal();
    // getters
    string getAnimalName();
    void getPosXY();
    void getAnimalID();
    void getLetra();
    void getFome();
    void getSaude();
    void getVida();
    void getPeso();
    void getAgressividade();
    void getRegistoAlimentar();

    // setters
    string setAnimalName();
    void setPosXY();
    void snimalID();
    void setLetra();
    void setFome();
    void setSaude();
    void setVida();
    void setPeso();
    void setAgressividade();
    void setRegistoAlimentar();

    // actions
    void move(int posX, int posY);
    void checkSurroundings(int x, int y, int radius);
    int escolhePeso();
    void dies();
    void birth();
    void feed();
    void repro();

};

/*
class Coelho : public Animal {
public:
    Coelho();
    int SCoelho;

};
*/

#endif //POONATURAL_ANIMAL_H
