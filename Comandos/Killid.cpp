#include "Killid.h"

Killid::Killid(string& cmd, int arg1, Reserva* reserva) : Comando(cmd) {
    reserva->removeAnimal(arg1);
}