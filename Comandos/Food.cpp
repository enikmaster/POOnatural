#include "Food.h"

Food::Food(string& cmd, string& arg1, int arg2, int arg3, Reserva* zoo) : Comando(cmd) {
    // verificar os argumentos 2 e 3 aleatorios;
    Alimento* pNovoAlimento;
    if(arg1 == "r") {
        pNovoAlimento = new Relva(arg1, arg2, arg3, zoo);
        zoo->addFood(pNovoAlimento);
    }
    if(arg1 == "t") {
        pNovoAlimento = new Cenoura(arg1, arg2, arg3, zoo);
        zoo->addFood(pNovoAlimento);
    }
    if(arg1 == "b") {
        pNovoAlimento = new Bife(arg1, arg2, arg3, zoo);
        zoo->addFood(pNovoAlimento);
    }
    if(arg1 == "a") {
        pNovoAlimento = new Banana(arg1, arg2, arg3, zoo);
        zoo->addFood(pNovoAlimento);
    }
    Local* pLocal = new Local(pNovoAlimento->getFoodId(), pNovoAlimento->getPosX(), pNovoAlimento->getPosY(), pNovoAlimento->getLetra(), zoo);
    zoo->addLocal(pLocal);
}
Food::Food(string& cmd, string& arg1, Reserva* zoo) : Food(cmd, arg1, -1, -1, zoo) {}