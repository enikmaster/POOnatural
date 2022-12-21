#ifndef POONATURAL_ANIMAL_H
#define POONATURAL_ANIMAL_H
#include "../Includes.h"
using namespace std;

// int s = cin >> getline(contantes.txt);

 struct registoAlimentar {
    string nome;
    int toxic;
    int nutri;
};

class Animal {
private:
    int posX, posY;
    int animalID;
    char letra;
    int fome;
    int saude; //SAnimal
    int vida; //VAnimal (ao fim de x ticks, o animal vai morrer)
    int peso;
    bool agressividade;
    struct registoAlimentar;
public:

    // constructores:
    Animal();
    ~Animal();
    // getters
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
    void setPosXY();
    void setAnimalID();
    void setLetra();
    void setFome();
    void setSaude();
    void setVida();
    int setPeso();
    void setAgressividade();
    void setRegistoAlimentar();

    // actions
    void move(int posX, int posY);
    void checkSurroundings(int x, int y, int radius);
    void dies();
    void birth();
    void feed();
    void repro();

};

/*
class Coelho : public Animal {
public:
    Coelho() : letra('C'), saude(s);
    int SCoelho;

};
*/

#endif //POONATURAL_ANIMAL_H
