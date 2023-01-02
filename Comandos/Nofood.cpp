#include "Nofood.h"

Nofood::Nofood(string& cmd, int arg1, int arg2, Reserva* reserva) : Comando(cmd) {
    reserva->removeFood(arg1, arg2);
}
Nofood::Nofood(string &cmd, int arg1, Reserva *reserva) : Comando(cmd) {
    reserva->removeFood(arg1);
}