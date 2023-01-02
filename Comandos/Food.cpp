#include "Food.h"

Food::Food(string& cmd, string& arg1, int arg2, int arg3, Reserva* zoo) : Comando(cmd) {
    // verificar os argumentos 2 e 3 aleatorios;

    if(arg1 == "r") {
        Alimento* pRelva = new Relva(arg1, arg2, arg3, zoo);
        zoo->addFood(pRelva);
        Local* pLocal = new Local(pRelva->getFoodId(), pRelva->getPosX(), pRelva->getPosY(), pRelva->getLetra(), zoo);
        zoo->addLocal(pLocal);
    }
    if(arg1 == "t") {
        // repetir o de cima
    }
    if(arg1 == "b") {

    }
    if(arg1 == "a") {

    }
    if(arg1 == "z") {

    }
};
Food::Food(string& cmd, string& arg1, Reserva* zoo) : Food(cmd, arg1, -1, -1, zoo) {};