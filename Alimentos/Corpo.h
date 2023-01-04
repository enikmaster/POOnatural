#ifndef TESTETP_CORPO_H
#define TESTETP_CORPO_H
#include "../Includes.h"
#include "Alimento.h"
#include "../Animais/Animal.h"

class Corpo : public Alimento{
public:
    Corpo(int x, int y, int nutri, Reserva* reservaFood);
    ~Corpo() {};
    // actions
    void incToxic();
    void dimNutri();
    void cicloTurno() override;
};


#endif //TESTETP_CORPO_H
