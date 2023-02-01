#include "Cenoura.h"
#include "../Reserva/Reserva.h"

Cenoura::Cenoura(char l, int posX, int posY, Reserva* reservaFood) : Alimento(l, posX, posY, reservaFood) {
    reservaFood->incContadorIds();
    this->setFoodId(reservaFood->getContadorIds());
    if(posX == -1) {
        int tempX {0};
        int tempY {0};
        do {
            tempX = this->aleatorio(0, reservaFood->getDimX());
            tempY = this->aleatorio(0, reservaFood->getDimY());
        } while(reservaAlimento->checkPosOcupado(tempX, tempY));
        this->setPosX(tempX);
        this->setPosY(tempY);
    }
    nasce();
}
Cenoura::Cenoura(char l, Reserva* reservaFood) : Cenoura(l, -1, -1, reservaFood) {};
Cenoura::Cenoura(const Cenoura& outro) : Alimento (outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    this->setFoodId(outro.getFoodId());
    this->setPosX(outro.getPosX());
    this->setPosY(outro.getPosY());
    this->setNutri(outro.getNutri());
    this->setToxic(outro.getToxic());
    this->setDuracao(outro.getDuracao());
    this->setCheiros("verdura");
    this->setIsAlive(outro.getIsAlive());
}
void Cenoura::nasce() {
    this->setNutri(4);
    this->setToxic(0);
    this->setDuracao(1);
    this->setCheiros("verdura");
    this->setIsAlive(true);
}
void Cenoura::cicloTurno() {
    incDuracao();
    if(getToxic() < 3) {
        if(getDuracao() % 10 == 0)
            incToxic();
    }
}