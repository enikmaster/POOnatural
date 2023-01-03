#include "Bife.h"
#include "../Reserva/Reserva.h"

Bife::Bife(string l, int posX, int posY, Reserva* reservaFood) : Alimento(std::move(l), posX, posY, reservaFood) {
    setNutri(10);
    setToxic(2);
    setDuracao(30);
    setCheiros("carne");
    setCheiros("ketchup");
};
void Bife::dimNutri() {
    if(this->getNutri() > 0)
        this->setNutri(this->getNutri() - 1);
}
void Bife::desaparece() {
    reservaAlimento->removeFood(this->getFoodId());
}
void Bife::cicloTurno() {
    // isto vai ser chamado a cada turno
    this->dimNutri();
    this->dimDuracao();
    if(this->getDuracao() <= 0)
        this->desaparece();
}