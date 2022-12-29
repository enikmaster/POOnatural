#include "Lobo.h"
#include "../Reserva/Reserva.h"

Lobo::Lobo() : SLobo(25), VLobo(40){
    cout << "######## LOBO ##########\n";
    Animal::setdeslMin(1);
    Animal::setdeslMax(1);
    Animal::setPercepcao(5);
    cout << "SLobo: " <<  SLobo << "\t" << "Percepcao: "<< Animal::getPercepcao() << endl;
    Animal::checkSurroundings(Animal::getPosX(), Animal::getPosY(), Animal::getPercepcao());
    Animal::move(Animal::getdeslMin(),Animal::getdeslMax());
    Animal::setPeso(15);
};

void Lobo::fomeca() { // vai ser chamada a cada tick
    // Incrementa por cada tick
    int fome = Animal::getFome();
    Animal::setFome(fome + 2);

    if (fome > 25){
        SLobo -= 2;
    }
    if (fome > 15 && fome < 20) {
        SLobo--;
        Animal::setdeslMin(2);
        Animal::setdeslMax(2);
    }
}

void Lobo::repro() {
    int randVal = aleatorio(1, 30);;
    if (randVal == 30) {
        // new Lobo em novoLobo::getPosX - rand(1-15) e getPosT - rand(1-15)
    }
}


Lobo::~Lobo() {
    if (VLobo == 0) {
        //delete
    }
    cout << "\nLobo Destruido!\n";
};