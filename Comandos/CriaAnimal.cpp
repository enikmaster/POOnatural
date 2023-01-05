#include "CriaAnimal.h"
#include "../Animais/Ovelha.h"
#include "../Animais/Coelho.h"

CriaAnimal::CriaAnimal(string& cmd, char arg1, int arg2, int arg3, Reserva* reserva) : Comando(cmd) {
    if(arg1 == 'O') {
        Animal* pOvelha = new Ovelha(arg1, arg2, arg3, reserva);
        reserva->addAnimal(pOvelha);
        Local* pLocal = new Local(pOvelha->getAnimalId(), pOvelha->getPosX(), pOvelha->getPosY(), pOvelha->getLetra(), reserva);
        reserva->addLocal(pLocal);
    }
    if(arg1 == 'C') {
        Animal* pCoelho = new Coelho(arg1, arg2, arg3, reserva);
        reserva->addAnimal(pCoelho);
        Local* pLocal = new Local(pCoelho->getAnimalId(), pCoelho->getPosX(), pCoelho->getPosY(), pCoelho->getLetra(), reserva);
        reserva->addLocal(pLocal);
    }
}