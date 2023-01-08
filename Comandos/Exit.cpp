#include "Exit.h"
#include "../Interfaces/Interface.h"

Exit::Exit(string& cmd, Reserva* reserva, Interface* inter) : Comando(cmd) {
    reserva->deleteAll();
    inter->clearSaves();
}