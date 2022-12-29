#include "Alimento.h"
#include "../Reserva/Reserva.h"

Alimento::Alimento(string l, const int x, const int y, Reserva* newReserva) : letra(std::move(l)), posX(x), posY(y), reservaAlimento(newReserva) {
    setFoodId(reservaAlimento->getContadorIds());
    reservaAlimento->incContadorIds();
    if(x == -1) {
        int temp = 0;
        do {
            temp = rand() % reservaAlimento->getDimX();
        } while(reservaAlimento->checkPosXOcupado(temp));
        setPosX(temp);
    }
    if(y == -1) {
        int temp = 0;
        do {
            temp = rand() % reservaAlimento->getDimY();
        } while(reservaAlimento->checkPosYOcupado(temp));
        setPosY(temp);
    }
};
Alimento::~Alimento() {};

// getters

// setters
void Alimento::setCheiros(const string& c) {
    cheiros.push_back(c);
};
