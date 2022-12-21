#include "Relva.h"
#include "../Reserva.h"

Relva::Relva() {
    Alimento::setLetra('r');
    Alimento::setNutri(3);
    VRelva = 20;
    Alimento::setToxic(0);
    Alimento::setCheiro1("erva");
    Alimento::setCheiro1("verdura");

};

int Relva::getVRelva() { return this-> VRelva;}
void Relva::setVRelva(int a) { VRelva = a;}

void Relva::spawn() {
    // passados 75% de 20 = 5
    if (Relva::getTick() == 5) {
        // new Relva  novoRelva::getPosX - rand(4-8) e getPosT - rand(4-8)
        // se naquela posicao já houver um alimento, envia um getTick() para o
        // metodo Relva::tryAgain(int tick, int posX, int posY); (to be implemented)
        // Relva::tryAgain(int a, int posX, int posY) {
        //     a++;
        //     if (getTick() == a) { new Relva etc}
        // }
        // isto funciona se este metodo fôr chamado a cada tick global
    }

};

Relva::~Relva() {
    if (VRelva == 0) {
        //delete
    }
};
