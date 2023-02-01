#include "Relva.h"
#include "../Reserva/Local.h"

Relva::Relva(char l, const int x, const int y, Reserva* zoo) : Alimento(l, x, y, zoo) {
    zoo->incContadorIds();
    this->setFoodId(zoo->getContadorIds());
    if(x == -1) {
        int tempX {0};
        int tempY {0};
        do {
            tempX = this->aleatorio(0, zoo->getDimX());
            tempY = this->aleatorio(0, zoo->getDimY());
        } while(zoo->checkPosOcupado(tempX, tempY));
        this->setPosX(tempX);
        this->setPosY(tempY);
    }
    this->nasce();
};
Relva::Relva(char l, Reserva* zoo) : Relva(l, -1, -1, zoo) {}
Relva::Relva(const Relva& outro, bool clone) : Alimento(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    if(clone) {
        this->setFoodId(outro.getFoodId());
        this->setPosX(outro.getPosX());
        this->setPosY(outro.getPosY());
        this->setNutri(outro.getNutri());
        this->setDuracao(outro.getDuracao());
        this->setSpawnTime(outro.getSpawnTime());
        this->setToxic(outro.getToxic());
        this->setCheiros("erva");
        this->setCheiros("verdura");
    } else {
        outro.reservaAlimento->incContadorIds();
        this->setFoodId(outro.reservaAlimento->getContadorIds());
        this->setPosX(outro.getPosX());
        this->setPosY(outro.getPosY());
        this->nasce();
    }
}
void Relva::nasce() {
    this->setNutri(3);
    this->setDuracao(20);
    this->setSpawnTime(5);
    this->setToxic(0);
    this->setCheiros("erva");
    this->setCheiros("verdura");
}
void Relva::dimDuracao() {
    this->setDuracao(this->getDuracao() - 1);
}
Alimento* Relva::fazOutro() {
    if(getDuracao() <= getSpawnTime()) {
        int tempX {this->aleatorio(4, 8)};
        int tempY {this->aleatorio(4, 8)};
        if(!reservaAlimento->checkPosOcupado(tempX, tempY)) {
            setSpawnTime(-1);
            Alimento* pA {new Relva(*this, false)};
            pA->setPosX(tempX);
            pA->setPosY(tempY);
            reservaAlimento->addFood(pA);
            Local* pL {new Local(pA->getFoodId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva())};
            reservaAlimento->addLocal(pL);
            return pA;
        }
    }
    return nullptr;
}
// verifica se está a hora de "falecer"
void Relva::checkVitality() {
    if(this->getDuracao() <= 0)
        this->setIsAlive(false);
}
void Relva::cicloTurno() {
    if(getIsAlive())
        dimDuracao();
    checkVitality();
    if(getIsAlive()) {
        if(getDuracao() <= getSpawnTime())
            this->fazOutro();
    }
}