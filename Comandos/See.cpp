#include "See.h"
#include "../Interfaces/Interface.h"

See::See(string& cmd, int posX, int posY, Interface* inter) : Comando(cmd) {
    inter->infoSee(posX, posY);
}