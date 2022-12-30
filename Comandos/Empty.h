#ifndef POONATURAL_EMPTY_H
#define POONATURAL_EMPTY_H
#include "Comando.h"

class Empty : public Comando {
public:
    Empty(std::string& cmd, int arg1, int arg2, Reserva* reservaEmpty);
};

#endif //POONATURAL_EMPTY_H