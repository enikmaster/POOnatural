#include "Alim.h"
#include "../Interfaces/Interface.h"

Alim::Alim(string& cmd, Interface* inter) : Comando(cmd) {
    inter->infoAlim();
};