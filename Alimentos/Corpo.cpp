#include "Corpo.h"

Corpo::Corpo(int posX, int posY, int nutri, Reserva* reservaFood) : Alimento("p", posX, posY, reservaFood) {
    setNutri(nutri);
    setToxic(0);
    setDuracao(nutri * 2);
    setCheiros("carne");
};

void Corpo::incToxic() {
    this->setToxic(this->getToxic() + 1);
}
void Corpo::dimNutri() {
    this->setNutri(this->getNutri() - 1);
}
void Corpo::cicloTurno() {
    // diminui valor nutritivo
    if(this->getNutri() > 0)
        dimNutri();
    // aumenta toxicidade
    if(this->getToxic() < getDuracao())
        incToxic();
}