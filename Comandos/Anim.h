#ifndef POONATURAL_ANIM_H
#define POONATURAL_ANIM_H
#include "../Includes.h"
#include "Comando.h"

class Anim : public Comando {
public:
    Anim(string& cmd, Reserva* reserva);
};

#endif //POONATURAL_ANIM_H