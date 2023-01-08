#ifndef POONATURAL_VISALIM_H
#define POONATURAL_VISALIM_H
#include "../Includes.h"
#include "Comando.h"

class Visalim : public Comando{
public:
    Visalim(string& cmd, Reserva* reserva);
};


#endif //POONATURAL_VISALIM_H
