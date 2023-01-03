#include "Corpo.h"

Corpo::Corpo(int posX, int posY, int nutri, Reserva* reservaFood) : Alimento("p", posX, posY, reservaFood) {
    setNutri(nutri);
    setToxic(0);
    setDuracao(nutri * 2);
    setCheiros("carne");
};

void Corpo::incToxic() {
    // para de aumentar chegando a um nivel
    if (this->getToxic() < getDuracao())
        setToxic(getToxic() + 1);
}
void Corpo::dimNutri() {
    setNutri(this->getNutri() - 1);
}
void Corpo::cicloTurno() {
    // diminui valor nutritivo
    dimNutri();
    // aumenta toxicidade
    incToxic();
}