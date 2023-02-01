#ifndef TESTETP_BIFE_H
#define TESTETP_BIFE_H
#include "../Includes.h"
#include "Alimento.h"

class Bife : public Alimento {
public:
    Bife(char l, int posX, int posY, Reserva* reservaFood);
    Bife(char l, Reserva* reservaFood);
    Bife(const Bife& outro);
    ~Bife() override = default;
    // actions
    void dimNutri() { setNutri(getNutri() - 1); };
    void dimDuracao() { setDuracao(getDuracao() - 1); };
    void checkVitality();
    void cicloTurno() override;
    Bife* clone() override { return new Bife(*this); }
};


#endif //TESTETP_BIFE_H
