#include "Alimento.h"
#include "../Reserva/Reserva.h"

Alimento::Alimento(char l, const int x, const int y, Reserva* newReserva) : letra(l), posX(x), posY(y), reservaAlimento(newReserva), isAlive(true) {
    setFoodId(reservaAlimento->getContadorIds());
    reservaAlimento->incContadorIds();
    if(x == -1) {
        int tempX, tempY = 0;
        do {
            tempX = this->aleatorio(0, reservaAlimento->getDimX());
            tempY = this->aleatorio(0, reservaAlimento->getDimY());
        } while(reservaAlimento->checkPosOcupado(tempX, tempY));
        this->setPosX(tempX);
        this->setPosY(tempY);
    }
};
Alimento::~Alimento() {};

// getters
Reserva* Alimento::getReserva() const {
    Reserva* pA = reservaAlimento;
    return pA;
}
// setters
void Alimento::setCheiros(const string& c) {
    cheiros.push_back(c);
};
