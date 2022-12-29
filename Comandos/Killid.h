#ifndef POONATURAL_KILLID_H
#define POONATURAL_KILLID_H
#include "Comando.h"

class Killid : public Comando {
public:
    Killid(string& cmd, int arg1, Reserva* reserva);
};


#endif //POONATURAL_KILLID_H
