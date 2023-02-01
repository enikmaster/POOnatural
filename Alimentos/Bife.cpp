#include "Bife.h"
#include "../Reserva/Reserva.h"

Bife::Bife(char l, int posX, int posY, Reserva* reservaFood) : Alimento(l, posX, posY, reservaFood) {
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
    this->setNutri(10);
    this->setToxic(2);
    this->setDuracao(30);
    this->setCheiros("carne");
    this->setCheiros("ketchup");
    this->setIsAlive(true);
};
Bife::Bife(char l, Reserva* reservaFood) : Bife(l, -1, -1, reservaFood) {};
Bife::Bife(const Bife& outro) : Alimento (outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    this->setFoodId(outro.getFoodId());
    this->setPosX(outro.getPosX());
    this->setPosY(outro.getPosY());
    this->setNutri(outro.getNutri());
    this->setToxic(outro.getToxic());
    this->setDuracao(outro.getDuracao());
    this->setCheiros("carne");
    this->setCheiros("ketchup");
    this->setIsAlive(outro.getIsAlive());
}
void Bife::checkVitality() {
    if(getDuracao() <= 0)
        setIsAlive(false);
}
void Bife::cicloTurno() {
    // isto vai ser chamado a cada turno
    if(getNutri() > 0) {
        dimNutri();
    }
    dimDuracao();
    checkVitality();
}