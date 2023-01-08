#ifndef POONATURAL_SEE_H
#define POONATURAL_SEE_H
#include "../Includes.h"
#include "Comando.h"

class See : public Comando {
public:
    See(string& cmd, int posX, int posY, Interface* inter);
};


#endif //POONATURAL_SEE_H
