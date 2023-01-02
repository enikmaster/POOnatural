#ifndef POONATURAL_CRIAANIMAL_H
#define POONATURAL_CRIAANIMAL_H
#include "Comando.h"
#include "../Animais/Ovelha.h"
#include "../Reserva/Local.h"
class Local;
class CriaAnimal : public Comando {
public:
    CriaAnimal(string& cmd, string& arg1, int arg2, int arg3, Reserva* reserva);
    CriaAnimal(string& cmd, string& arg1, Reserva* reserva) : CriaAnimal(cmd, arg1, -1, -1, reserva) {};
};


#endif