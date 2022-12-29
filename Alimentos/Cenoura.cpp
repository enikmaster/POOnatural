#include "Cenoura.h"
#include "../Reserva/Reserva.h"


Cenoura::Cenoura() {
    Cenoura::podridao();
    Alimento::setLetra('t');
    Alimento::setNutri(4);
    Alimento::setToxic(0);
    Alimento::setCheiro1("verdura");

}

void Cenoura::podridao() {
    if (Alimento::getTick() == 10) Alimento::setToxic(1);
    if (Alimento::getTick() == 20) Alimento::setToxic(2);
    if (Alimento::getTick() == 30) Alimento::setToxic(3);
}

Cenoura::~Cenoura() {
    cout << "Cenoura consumida!\n";
}