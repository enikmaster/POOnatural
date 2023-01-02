#ifndef POONATURAL_FEEDID_H
#define POONATURAL_FEEDID_H
#include "Comando.h"

class Feedid : public Comando {
public:
    Feedid(std::string& cmd, int arg1, int arg2, int arg3, Reserva* reservaFeedid);
};


#endif //POONATURAL_FEEDID_H
