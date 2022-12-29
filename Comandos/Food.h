#ifndef POONATURAL_FOOD_H
#define POONATURAL_FOOD_H
#include "Comando.h"
#include "../Alimentos/Relva.h"
#include "../Reserva/Local.h"
class Local;
class Food : public Comando {
public:
    Food(string& cmd, string& arg1, int arg2, int arg3, Reserva* zoo);
    Food(string& cmd, string& arg1, Reserva* zoo);
};


#endif //POONATURAL_FOOD_H
