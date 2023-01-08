#include "CriaAnimal.h"
#include "../Animais/Ovelha.h"
#include "../Animais/Coelho.h"
#include "../Animais/Lobo.h"
#include "../Animais/Canguru.h"
#include "../Animais/Macaco.h"

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
    if(arg1 == 'L') {
        Animal* pLobo = new Lobo(arg1, arg2, arg3, reserva);
        reserva->addAnimal(pLobo);
        Local* pLocal = new Local(pLobo->getAnimalId(), pLobo->getPosX(), pLobo->getPosY(), pLobo->getLetra(), reserva);
        reserva->addLocal(pLocal);
    }
    if(arg1 == 'G') {
        Animal* pCanguru = new Canguru(arg1, arg2, arg3, reserva);
        reserva->addAnimal(pCanguru);
        Local* pLocal = new Local(pCanguru->getAnimalId(), pCanguru->getPosX(), pCanguru->getPosY(), pCanguru->getLetra(), reserva);
        reserva->addLocal(pLocal);
    }
    if(arg1 == 'M') {
        Animal* pMacaco = new Macaco(arg1, arg2, arg3, reserva);
        reserva->addAnimal(pMacaco);
        Local* pLocal = new Local(pMacaco->getAnimalId(), pMacaco->getPosX(), pMacaco->getPosY(), pMacaco->getLetra(), reserva);
        reserva->addLocal(pLocal);
    }
}