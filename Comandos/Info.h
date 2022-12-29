#ifndef POONATURAL_INFO_H
#define POONATURAL_INFO_H
#include "Comando.h"

class Info : public Comando {
public:
    Info(string& cmd, int arg1, Reserva* reserva);
};

#endif //POONATURAL_INFO_H