#include "Anim.h"
#include "../Interfaces/Interface.h"

Anim::Anim(string& cmd, Interface* hub) : Comando(cmd) {
    hub->infoAnim();
};