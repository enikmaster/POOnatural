#include "Empty.h"

Empty::Empty(std::string& cmd, int arg1, int arg2, Reserva* reservaEmpty) : Comando(cmd) {
    reservaEmpty->setToEmptyByPos(arg1, arg2);
    if(!reservaEmpty->removeAnimal(arg1, arg2))
        reservaEmpty->removeFood(arg1, arg2);
}