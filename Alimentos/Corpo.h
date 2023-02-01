#ifndef TESTETP_CORPO_H
#define TESTETP_CORPO_H
#include "../Includes.h"
#include "Alimento.h"
#include "../Animais/Animal.h"

class Corpo : public Alimento{
public:
    Corpo(int x, int y, int nutri, Reserva* reservaFood);
    Corpo(const Corpo& outro);
    ~Corpo() override = default;
    // actions
    void incToxic() { setToxic(getToxic() + 1); };
    void dimNutri() { setNutri(getNutri() - 1); };
    void cicloTurno() override;
    Corpo* clone() override { return new Corpo(*this); }
};


#endif //TESTETP_CORPO_H
