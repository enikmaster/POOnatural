#ifndef POONATURAL_NEXT_H
#define POONATURAL_NEXT_H
#include "../Includes.h"
#include "Comando.h"

class Next : public Comando {
public:
    Next(string cmd, int arg1, Reserva* reserva);
    Next(string cmd, Reserva* reserva) : Next(std::move(cmd), 1, reserva) {};
};
#endif //POONATURAL_NEXT_H
