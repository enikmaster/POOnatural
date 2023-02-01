#include "Corpo.h"
#include "../reserva/reserva.h"

Corpo::Corpo(int posX, int posY, int nutri, Reserva* reservaFood) : Alimento('p', posX, posY, reservaFood) {
    reservaFood->incContadorIds();
    this->setFoodId(reservaFood->getContadorIds());
    if(posX == -1) {
        int tempX {0};
        int tempY {0};
        do {
            tempX = this->aleatorio(0, reservaFood->getDimX());
            tempY = this->aleatorio(0, reservaFood->getDimY());
        } while(reservaFood->checkPosOcupado(tempX, tempY));
        this->setPosX(tempX);
        this->setPosY(tempY);
    }
    this->setNutri(nutri);
    this->setToxic(0);
    this->setDuracao(nutri * 2);
    this->setCheiros("carne");
    this->setIsAlive(true);
};
Corpo::Corpo(const Corpo& outro) : Alimento (outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    this->setFoodId(outro.getFoodId());
    this->setPosX(outro.getPosX());
    this->setPosY(outro.getPosY());
    this->setNutri(outro.getNutri());
    this->setToxic(outro.getToxic());
    this->setDuracao(outro.getDuracao());
    this->setCheiros("carne");
    this->setIsAlive(outro.getIsAlive());
}
void Corpo::cicloTurno() {
    // diminui valor nutritivo
    if(getNutri() > 0)
        dimNutri();
    // aumenta toxicidade
    if(getToxic() < getDuracao())
        incToxic();
}