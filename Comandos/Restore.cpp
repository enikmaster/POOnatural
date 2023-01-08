#include "Restore.h"
#include "../Interfaces/Interface.h"

Restore::Restore(string& cmd, string& filename, Interface* inter) : Comando(cmd) {
    inter->restoreSave(filename);
}