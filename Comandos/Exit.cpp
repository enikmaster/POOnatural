#include "Exit.h"

Exit::Exit(string& cmd, Reserva* reserva) : Comando(cmd) {
    reserva->deleteAll();
}