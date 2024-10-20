#ifndef POONATURAL_BANANA_H
#define POONATURAL_BANANA_H
#include "../Includes.h"
#include "Alimento.h"

class Banana : public Alimento {
public:
    Banana(char l, int posX, int posY, Reserva* reservaFood);
    Banana(const Banana& outro);
    Banana(char l, Reserva* reservaFood);
    ~Banana() override = default;
    // actions
    void dimNutri();
    void dimDuracao() { setDuracao(getDuracao() - 1);};
    void checkVitality();
    void cicloTurno() override;
    Banana* clone() override {return new Banana(*this);}
};


#endif //POONATURAL_BANANA_H
