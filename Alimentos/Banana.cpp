#include "Banana.h"
#include "../Reserva/Reserva.h"

Banana::Banana(char l, int posX, int posY, Reserva *reservaFood) : Alimento(l, posX, posY, reservaFood) {
    this->setNutri(15);
    this->setToxic(1);
    this->setDuracao(60);
    this->setCheiros("fruta");
    setIsAlive(true);
}
Banana::Banana(const Banana& outro) {}
// actions
void Banana::dimNutri() {
    (getDuracao() > 50) ? setNutri(getNutri() + 1) : setNutri(getNutri() - 1);
}
void Banana::checkVitality() {
    if(getDuracao() <= 0)
        setIsAlive(false);
}
void Banana::cicloTurno() {
    if(getDuracao() > 0)
        dimDuracao();
    if(getNutri() > 0)
        dimNutri();
    checkVitality();
}