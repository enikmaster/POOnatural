#include "Visanim.h"
#include "../Interfaces/Interface.h"

Visanim::Visanim(string& cmd, Interface* inter) : Comando(cmd) {
    inter->infoVisanim();
};