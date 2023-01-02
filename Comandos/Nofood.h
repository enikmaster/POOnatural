#ifndef POONATURAL_NOFOOD_H
#define POONATURAL_NOFOOD_H
#include "../Includes.h"
#include "Comando.h"

class Nofood : public Comando {
public:
    Nofood(string& cmd, int arg1, int arg2, Reserva* reserva);
    Nofood(string& cmd, int arg1, Reserva* reserva);
};

#endif //POONATURAL_NOFOOD_H