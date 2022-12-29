#include "Coelho.h"
#include "../Reserva/Reserva.h"


Coelho::Coelho() : SCoelho(20), VCoelho(30) {
    cout << "######## COELHO ##########\n";
    Animal::setdeslMin(1);
    Animal::setdeslMax(2);
    Animal::setPercepcao(4);
    cout << "SCoelho: " <<  SCoelho << "\t" << "Percepcao: "<< Animal::getPercepcao() << endl;
    Animal::move(Animal::getdeslMin(),Animal::getdeslMax());
    Animal::checkSurroundings(Animal::getPosX(), Animal::getPosY(), Animal::getPercepcao());
    cout << "X: " << Animal::getPosX() << "\t"<<"Y: " << Animal::getPosY() << endl;
    Animal::escolhePeso(1,4);
    cout << "Peso: " << getPeso();

}
Coelho::~Coelho() {
    if (VCoelho == 0) {
        //delete
    }
    cout << "Coelho Destruido!\n";
}

void Coelho::fomeca() { // vai ser chamada a cada tick
    int fome = Animal::getFome();
    Animal::setFome(fome + 1);

    if (fome > 20){
        SCoelho -= 2;
        Animal::setdeslMin(1);
        Animal::setdeslMax(4);
    }
    if (fome > 10 && fome < 20) {
        SCoelho--;
        Animal::setdeslMin(1);
        Animal::setdeslMax(3);
    }
}

void Coelho::repro() {
    if ((Animal::getTick() % 8) == 0) {
        int flag = aleatorio(0,1);
        if ( flag == 1 ) {
            // new Coelho em novoCoelho::getPosX - rand(1-10) e getPosT - rand(1-10)
        }
    }
}