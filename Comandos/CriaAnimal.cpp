#include "CriaAnimal.h"

CriaAnimal::CriaAnimal(string& cmd, string& arg1, int arg2, int arg3, Reserva* reserva) : Comando(cmd) {
    if(arg1 == "o") {
        Animal* pOvelha = new Ovelha(arg1, arg2, arg3, reserva);
        reserva->addAnimal(pOvelha);
        Local* pLocal = new Local(pOvelha->getAnimalId(), pOvelha->getPosX(), pOvelha->getPosY(), pOvelha->getLetra(), reserva);
        reserva->addLocal(pLocal);
    }
}