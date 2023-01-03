#ifndef POONATURAL_BANANA_H
#define POONATURAL_BANANA_H
#include "../Includes.h"
#include "Alimento.h"

class Banana : public Alimento {
public:
    Banana(string l, int posX, int posY, Reserva* reservaFood);
    ~Banana() override = default;
    // actions
    void dimNutri();
    void dimDuracao() {this->setDuracao(this->getDuracao() - 1);};
    void desaparece();
    void cicloTurno() override;
};


#endif //POONATURAL_BANANA_H
