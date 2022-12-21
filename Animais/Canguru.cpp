#include "Canguru.h"
#include "../Reserva.h"

Canguru::Canguru() : SCanguru(20), VCanguru(70) {
    cout << "######## CANGURU ##########\n";
    Animal::setdeslMin(1);
    Animal::setdeslMax(1);
    Animal::setPercepcao(7);
    Animal::checkSurroundings(Animal::getPosX(), Animal::getPosY(), Animal::getPercepcao());
    Animal::move(Animal::getdeslMin(),Animal::getdeslMax());
    Animal::setPeso(10);

};
// substituir futuramente por um fim no getInput ?
bool Canguru::isAdulto() {
    if (Animal::getTick() < 10) {
        // nao é adulto -> return false
        // falta implementar a verificaçao se o canguru nao-adulto est´a 4 posiçoes
        // do canguru com o ID que lhe deu spawn
        // etc
        return false;
    }
    if (Animal::getTick() == 20) {
        Animal::setPeso(20);
        return true;
    }


}

void Canguru::repro() {
    if ((Animal::getTick() == 30) == 0) {
            // new Canguru em novoCanguru::getPosX - rand(1-3) e getPosT - rand(1-3)
    }
}

Canguru::~Canguru() {
    if (VCanguru == 0) {
        //delete
    }
    cout << "Canguru Destruido!\n";
};