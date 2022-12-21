#ifndef POONATURAL_CRIAANIMAL_H
#define POONATURAL_CRIAANIMAL_H


#include "Comando.h"

class CriaAnimal : public Comando {
    CriaAnimal(string c, string d, string a) : Comando("animal", d, a) {
        cout << c;
    }
};


#endif