#include "Alimento.h"
#include "../Reserva/Reserva.h"

Alimento::Alimento(char l, const int x, const int y, Reserva* newReserva) : letra(l), posX(x), posY(y), reservaAlimento(newReserva), isAlive(true) {};
Alimento::~Alimento() {};

// getters
Reserva* Alimento::getReserva() const {
    Reserva* pA {reservaAlimento};
    return pA;
}
// setters
void Alimento::setCheiros(const string& c) {
    cheiros.push_back(c);
};
