#include "Ovelha.h"
#include "../Reserva.h"

Ovelha::Ovelha() : SOvelha(30), VOvelha(35) {
    cout << "######## OVELHA ##########\n";
    Animal::setdeslMin(1);
    Animal::setdeslMax(1);
    Animal::setPercepcao(3);
    cout << "SOvelha: " <<  SOvelha << "\t" << "Percepcao: "<< Animal::getPercepcao() << endl;
    Animal::checkSurroundings(Animal::getPosX(), Animal::getPosY(), Animal::getPercepcao());
    Animal::move(Animal::getdeslMin(),Animal::getdeslMax());
    cout << "X: " << Animal::getPosX() << "\t"<<"Y: " << Animal::getPosY() << endl;
    Animal::escolhePeso(4,8);
};


void Ovelha::fomeca() { // vai ser chamada a cada tick
    // Incrementa por cada tick
    int fome = Animal::getFome();
    Animal::setFome(fome + 1);

    if (fome > 20){
        SOvelha -= 2;
    }
    if (fome > 15 && fome < 20) {
        SOvelha--;
        Animal::setdeslMin(1);
        Animal::setdeslMax(2);
    }
}

void Ovelha::repro() {
    if ((Animal::getTick() % 15) == 0) {
            // new Ovelha em novoOvelha::getPosX - rand(1-12) e getPosT - rand(1-12)
    }
}

Ovelha::~Ovelha() {
    if (VOvelha == 0 || Animal::getTick() == 35 ) {
        //delete
    }
    cout << "\nOvelha Destruida!\n";
};