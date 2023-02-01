#include "Banana.h"
#include "../Reserva/Reserva.h"

Banana::Banana(char l, int posX, int posY, Reserva *reservaFood) : Alimento(l, posX, posY, reservaFood) {
    reservaAlimento->incContadorIds();
    this->setFoodId(reservaAlimento->getContadorIds());
    if(posX == -1) {
        int tempX {0};
        int tempY {0};
        do {
            tempX = this->aleatorio(0, reservaAlimento->getDimX());
            tempY = this->aleatorio(0, reservaAlimento->getDimY());
        } while(reservaAlimento->checkPosOcupado(tempX, tempY));
        this->setPosX(tempX);
        this->setPosY(tempY);
    }
    this->setNutri(15);
    this->setToxic(1);
    this->setDuracao(60);
    this->setCheiros("fruta");
    this->setIsAlive(true);
}
Banana::Banana(const Banana& outro) : Alimento(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    this->setNutri(outro.getNutri());
    this->setToxic(outro.getToxic());
    this->setDuracao(outro.getDuracao());
    this->setCheiros("fruta");
    this->setIsAlive(outro.getIsAlive());
}
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