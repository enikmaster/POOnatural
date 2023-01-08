#include "Store.h"
#include "../Interfaces/Interface.h"

Store::Store(string& cmd, string& filename, Interface* inter) : Comando(cmd) {
    inter->addSave(filename);
}