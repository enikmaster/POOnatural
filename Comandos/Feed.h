#ifndef POONATURAL_FEED_H
#define POONATURAL_FEED_H
#include "Comando.h"

class Feed : public Comando {
    Feed(std::string& cmd, int posX, int posY, int arg1, int arg2, Reserva* reservaKill);
};


#endif //POONATURAL_FEED_H
