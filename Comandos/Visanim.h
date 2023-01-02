#ifndef POONATURAL_VISANIM_H
#define POONATURAL_VISANIM_H
#include "../Includes.h"
#include "Comando.h"

class Visanim : public Comando {
public:
    Visanim(string& cmd, Reserva* reserva);
};

#endif //POONATURAL_VISANIM_H