#include "Info.h"
#include "../Interfaces/Interface.h"

Info::Info(string& cmd, int arg1, Interface* inter) : Comando(cmd) {
    inter->infoAboutId(arg1);
};