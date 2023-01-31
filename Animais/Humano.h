#ifndef POONATURAL_HUMANO_H
#define POONATURAL_HUMANO_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Humano : public Animal {
private:
    std::string direction;

public:
    Humano(char l, int posX, int posY, Reserva *reserva);
    Humano(char l, Reserva* reserva);
    Humano(const Humano& outro, bool value = false);
    ~Humano() override;

    void setDirection(std::string dir) { direction = std::move(dir);}
    int getVelocidade();
    void checkVitality();
    void checkSurrounding();
    void checkDirection();
    void nasce();
    void cicloTurno() override;
    Humano* clone() override {return new Humano(*this);};
};


#endif //POONATURAL_HUMANO_H
