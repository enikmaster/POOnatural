#ifndef POONATURAL_HUMANO_H
#define POONATURAL_HUMANO_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Humano : public Animal {
private:
    string direction;

public:
    Humano(char l, int posX, int posY, Reserva *reserva);
    ~Humano();

    void setDirection(string dir) { direction = dir;}
    int getVelocidade();
    void checkVitality();
    void checkSurrounding();
    void checkDirection();
    void nasce();
    void cicloTurno() override;
    Humano* clone() override {return new Humano(*this);};
};


#endif //POONATURAL_HUMANO_H
