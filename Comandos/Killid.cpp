#include "Killid.h"

Killid::Killid(string& cmd, int arg1, Reserva* reserva) : Comando(cmd) {
    if(reserva->removeLocal(arg1)) {
        reserva->removeAnimal(arg1);
        reserva->removeFood(arg1);
    }
}