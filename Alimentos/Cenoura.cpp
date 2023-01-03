#include "Cenoura.h"

Cenoura::Cenoura(string l, int posX, int posY, Reserva* reservaFood) : Alimento(std::move(l), posX, posY, reservaFood) {
    setNutri(4);
    setToxic(0);
    setDuracao(1);
    setCheiros("verdura");
}
void Cenoura::incToxic() {
    if(this->getToxic() < 3) {
        if(this->getDuracao() % 10 == 0)
            this->setToxic(this->getToxic() + 1);
    }
}
void Cenoura::cicloTurno() {
    this->incDuracao();
    this->incToxic();
}