#ifndef TESTETP_CENOURA_H
#define TESTETP_CENOURA_H
#include "../Includes.h"
#include "Alimento.h"

class Cenoura : public Alimento{
public:
    Cenoura(char l, int posX, int posY, Reserva* reservaFood);
    Cenoura(char l, Reserva* reservaFood);
    Cenoura(const Cenoura& outra);
    ~Cenoura() override = default;
    // actions
    void nasce();
    void incToxic(){ setToxic(getToxic() + 1); };
    void incDuracao() { setDuracao(getDuracao() + 1); };
    void cicloTurno() override;
    Cenoura* clone() override { return new Cenoura(*this); }
};

#endif //TESTETP_CENOURA_H