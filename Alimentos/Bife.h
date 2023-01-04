#ifndef TESTETP_BIFE_H
#define TESTETP_BIFE_H
#include "../Includes.h"
#include "Alimento.h"

class Bife : public Alimento {
public:
    Bife(char l, int posX, int posY, Reserva* reservaFood);
    ~Bife() override = default;
    // actions
    void dimNutri();
    void dimDuracao() {this->setDuracao(this->getDuracao() - 1);};
    void desaparece();
    void cicloTurno() override;
};


#endif //TESTETP_BIFE_H
