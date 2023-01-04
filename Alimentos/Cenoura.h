#ifndef TESTETP_CENOURA_H
#define TESTETP_CENOURA_H
#include "../Includes.h"
#include "Alimento.h"

class Cenoura : public Alimento{
public:
    Cenoura(char l, int posX, int posY, Reserva* reservaFood);
    ~Cenoura() override = default;
    // actions
    void incToxic();
    void incDuracao() {this->setDuracao(this->getDuracao() + 1);};
    void cicloTurno() override;
};

#endif //TESTETP_CENOURA_H