#include "Kill.h"
Kill::Kill(std::string& cmd, int arg1, int arg2, Reserva* reservaKill) : Comando(cmd) {
    reservaKill->removeAnimal(arg1, arg2);
    // criar um novo alimento neste local?
}