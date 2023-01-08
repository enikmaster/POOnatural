#ifndef POONATURAL_RESTORE_H
#define POONATURAL_RESTORE_H
#include "Comando.h"

class Restore : public Comando {
public:
    Restore(string& cmd, string& filename, Interface* inter);
};

#endif //POONATURAL_RESTORE_H