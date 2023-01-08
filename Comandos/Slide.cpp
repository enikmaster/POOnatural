#include "Slide.h"
#include "../Interfaces/Interface.h"

Slide::Slide(string& cmd, string &arg1, int arg2, Interface* inter) : Comando(cmd) {
    inter->modifyOriginVis(arg1, arg2);
//    if(arg1 == "up") {
//        reserva->setOrigemVisY(reserva->getOrigemVisY() - arg2);
//    }
//    if(arg1 == "down") {
//        reserva->setOrigemVisY(reserva->getOrigemVisY() + arg2);
//    }
//    if(arg1 == "left") {
//        reserva->setOrigemVisX(reserva->getOrigemVisX() - arg2);
//    }
//    if(arg1 == "right") {
//        reserva->setOrigemVisX(reserva->getOrigemVisX() + arg2);
//    }
}