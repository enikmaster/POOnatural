#include "Relva.h"
#include "../Reserva/Local.h"

Relva::Relva(char l, const int x, const int y, Reserva* zoo) : Alimento(l, x, y, zoo) {
    this->nasce();
};
Relva::Relva(char l, Reserva* zoo) : Relva(l, -1, -1, zoo) {}
Relva::Relva(const Relva& outro) : Alimento(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    this->nasce();
}
Relva::~Relva() = default;
void Relva::nasce() {
    this->setNutri(3);
    this->setDuracao(20);
    this->setSpawnTime(this->getDuracao() - (this->getDuracao() / 4));
    this->setToxic(0);
    this->setCheiros("erva");
    this->setCheiros("verdura");
}
void Relva::dimDuracao() {
    this->setDuracao(this->getDuracao() - 1);
}
Alimento* Relva::fazOutro() {
    if(this->getDuracao() < this->getSpawnTime()) {
        int tempX = this->aleatorio(4, 8);
        int tempY = this->aleatorio(4, 8);
        if(!reservaAlimento->checkPosOcupado(tempX, tempY)) {
            Alimento* pA = new Relva(*this);
            pA->setPosX(tempX);
            pA->setPosY(tempY);
            reservaAlimento->addFood(pA);
            Local* pL = new Local(pA->getFoodId(), pA->getPosX(), pA->getPosY(),pA->getLetra() ,pA->getReserva());
            reservaAlimento->addLocal(pL);
            return pA;
        }
    }
    return nullptr;
}
void Relva::checkVitality() {
    if(this->getDuracao() <= 0)
        this->setIsAlive(false);
}
void Relva::cicloTurno() {
    if(this->getDuracao() > 0)
        this->dimDuracao();
    this->checkVitality();
    if(this->getIsAlive()) {
        if (this->getDuracao() <= this->getSpawnTime())
            this->fazOutro();
    }
}