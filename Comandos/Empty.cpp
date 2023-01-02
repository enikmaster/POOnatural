#include "Empty.h"

Empty::Empty(std::string& cmd, int arg1, int arg2, Reserva* reservaEmpty) : Comando(cmd) {
    // o .erase() chama o destrutor?
    if(!reservaEmpty->removeAnimal(arg1, arg2))
        reservaEmpty->removeFood(arg1, arg2);
}