#ifndef POONATURAL_STORE_H
#define POONATURAL_STORE_H
#include "Comando.h"

class Store : public Comando {
public:
    Store(string& cmd, string& filename, Interface* inter);
};


#endif //POONATURAL_STORE_H
