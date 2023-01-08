#include "Visalim.h"
#include "../Interfaces/Interface.h"

Visalim::Visalim(string& cmd, Interface* inter) : Comando(cmd) {
    inter->infoVisalim();
};