#ifndef POONATURAL_LOAD_H
#define POONATURAL_LOAD_H
#include "../Includes.h"
#include "Comando.h"

class Load : public Comando {
public:
    Load(string& cmd, string& filename, vector<string>& guardaFrases, Interface* inter);
};

#endif //POONATURAL_LOAD_H