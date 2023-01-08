#ifndef POONATURAL_SLIDE_H
#define POONATURAL_SLIDE_H
#include "Comando.h"

class Slide : public Comando {
public:
    Slide(string& cmd, string& arg1, int arg2, Interface* inter);
};


#endif //POONATURAL_SLIDE_H
