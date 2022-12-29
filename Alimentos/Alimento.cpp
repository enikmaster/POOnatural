#include "Alimento.h"
#include "../Reserva/Reserva.h"

Alimento::Alimento(string l, const int x, const int y, Reserva* newReserva) : letra(std::move(l)), posX(x), posY(y), reserva(newReserva) {
    setFoodId(reserva->getContadorIds());
    reserva->incContadorIds();
    if(x == -1) {
        int temp = 0;
        do {
            temp = rand() % reserva->getDimX();
        } while(reserva->checkPosXOcupado(temp));
        setPosX(temp);
    }
    if(y == -1) {
        int temp = 0;
        do {
            temp = rand() % reserva->getDimY();
        } while(reserva->checkPosYOcupado(temp));
        setPosY(temp);
    }
};
Alimento::~Alimento() {};

// getters
void Alimento::getCheiros() const {
    for(auto& it : cheiros){
        //Interface::getWInfo() << move_to(0, 0) << it;
    }
}
//string Alimento::getCheiro1() { return this->cheiro1;}
//string Alimento::getCheiro2() { return this->cheiro2;}

// setters
void Alimento::setCheiros(const string& c) {
    cheiros.push_back(c);
};
//void Alimento::setCheiro1(string a) { this->cheiro1 = std::move(a);}
//void Alimento::setCheiro2(string a) { this->cheiro2 = std::move(a);}