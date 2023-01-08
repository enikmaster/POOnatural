#ifndef POONATURAL_EXIT_H
#define POONATURAL_EXIT_H
#include "../Includes.h"
#include "Comando.h"

class Exit : public Comando {
public:
    Exit(string& cmd, Reserva* reserva, Interface* inter);
};

#endif //POONATURAL_EXIT_H