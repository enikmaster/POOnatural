#include "Banana.h"
#include "../Reserva/Reserva.h"

Banana::Banana(std::string l, int posX, int posY, Reserva *reservaFood) : Alimento(std::move(l), posX, posY, reservaFood) {
    this->setNutri(15);
    this->setToxic(1);
    this->setDuracao(60);
    this->setCheiros("fruta");
}
// actions
void Banana::dimNutri() {
    (this->getDuracao() > 50) ? this->setNutri(this->getNutri() + 1) : this->setNutri(this->getNutri() - 1);
}
void Banana::desaparece() {
    this->reservaAlimento->removeFood(this->getFoodId());
}
void Banana::cicloTurno() {
    if(this->getDuracao() <= 0)
        this->desaparece();
    if(this->getNutri() > 0)
        this->dimNutri();
}