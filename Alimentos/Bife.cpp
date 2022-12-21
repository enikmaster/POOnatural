#include "Bife.h"

Bife::Bife() {
    Alimento::setLetra('b');
    Alimento::setNutri(10);
    Alimento::setToxic(2);
    Alimento::setCheiro1("carne");
    Alimento::setCheiro2("ketchup");
};

void Bife::podridao() {
    // isto vai ser chamado a cada tick global
    if (getNutri() > 0)
        setNutri(getNutri() - 1);
}

Bife::~Bife() {
    if (Alimento::getTick() == 30) {
        //delete
    }
};
