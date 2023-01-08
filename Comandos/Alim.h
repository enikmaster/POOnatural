#ifndef POONATURAL_ALIM_H
#define POONATURAL_ALIM_H
#include "../Includes.h"
#include "Comando.h"


class Alim : public Comando{
public:
    Alim(string& cmd, Reserva* reserva);
};


#endif //POONATURAL_ALIM_H
