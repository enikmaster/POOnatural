#ifndef POONATURAL_FEED_H
#define POONATURAL_FEED_H
#include "Comando.h"

class Feed : public Comando {
public:
    Feed(std::string& cmd, int posX, int posY, int arg1, int arg2, Reserva* r);
};


#endif //POONATURAL_FEED_H
