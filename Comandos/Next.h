#ifndef POONATURAL_NEXT_H
#define POONATURAL_NEXT_H
#include "../Includes.h"
#include "Comando.h"

class Next : public Comando {
public:
    Next(string& cmd, int arg1, int arg2, Reserva* reserva);
    Next(string& cmd, int arg1, Reserva* reserva) : Next(cmd, arg1, 0, reserva) {};
    Next(string& cmd, Reserva* reserva) : Next(cmd, 1, 0, reserva) {};
};


#endif //POONATURAL_NEXT_H
