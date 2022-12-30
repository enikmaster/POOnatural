#ifndef POONATURAL_KILL_H
#define POONATURAL_KILL_H
#include "Comando.h"
#include "../Includes.h"

class Kill : public Comando {
public:
    Kill(std::string& cmd, int arg1, int arg2, Reserva* reservaKill);
};


#endif //POONATURAL_KILL_H
