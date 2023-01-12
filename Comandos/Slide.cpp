#include "Slide.h"
#include "../Interfaces/Interface.h"

Slide::Slide(string& cmd, string &arg1, int arg2, Interface* inter) : Comando(cmd) {
    inter->modifyOriginVis(arg1, arg2);
}