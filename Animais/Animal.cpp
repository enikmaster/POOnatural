#include "Animal.h"
#include "../Alimentos/Alimento.h"
#include "../Reserva/Reserva.h"

Animal::Animal(char l, const int x, const int y, Reserva* novaReserva) : letra(l), posX(x), posY(y), reservaAnimal(novaReserva) {
    this->setAnimalID(reservaAnimal->getContadorIds());
    reservaAnimal->incContadorIds();
    if(x == -1) {
        int tempX, tempY = 0;
        do {
            tempX = this->aleatorio(0, reservaAnimal->getDimX());
            tempY = this->aleatorio(0, reservaAnimal->getDimY());
        } while(reservaAnimal->checkPosOcupado(tempX, tempY));
        this->setPosX(tempX);
        this->setPosY(tempY);
    }
}
// getters
Reserva* Animal::getReserva() const {
    Reserva* pCopiaReserva = reservaAnimal;
    return pCopiaReserva;
}
// setters
void Animal::addAnimalPerto(Animal* novoAnimal) {
    animaisPerto.push_back(novoAnimal);
}
void Animal::addAlimentoPerto(Alimento* novoAlimento) {
    alimentosPerto.push_back(novoAlimento);
}
// actions
// preenche uma lista de animais perto e
// uma lista de alimentos perto
void Animal::populateWithinRange() {
    alimentosPerto.clear();
    animaisPerto.clear();
    vector<int> idAnimaisPerto;
    vector<int> idAlimentosPerto;
    reservaAnimal->checkWithinRange(getPosX(), getPosY(), getPercepcao(), idAnimaisPerto, idAlimentosPerto);
    if(!idAlimentosPerto.empty()){
        for(int& it : idAlimentosPerto)
            addAlimentoPerto(reservaAnimal->getAlimento(it));
    }
    if(!idAnimaisPerto.empty()) {
        for(int& it : idAnimaisPerto)
            addAnimalPerto(reservaAnimal->getAnimal(it));
    }
}
// move o animal para a nova posição
void Animal::move(int xTarget, int yTarget) {
    if(xTarget >= reservaAnimal->getDimX())
        setPosX(xTarget - reservaAnimal->getDimX());
    if(xTarget < 0)
        setPosX(xTarget + reservaAnimal->getDimX());
    if(xTarget >= 0 && xTarget < reservaAnimal->getDimX())
        setPosX(xTarget);
    if(yTarget >= reservaAnimal->getDimY())
        setPosX(yTarget - reservaAnimal->getDimY());
    if(yTarget < 0)
        setPosX(yTarget + reservaAnimal->getDimY());
    if(yTarget >= 0 && yTarget < reservaAnimal->getDimY())
        setPosY(yTarget);
}
// indica ao animal que está morto para a reserva saber que tem de o retirar
void Animal::dies() {
    this->setIsAlive(false);
}
void Animal::escolhePeso(int min, int max){
    this->setPeso(aleatorio(min, max));
}
int Animal::aleatorio(int min, int max) {
    return min + rand() % (max + 1 - min);
}
void Animal::come(int nutri, int toxic) {
    this->setSaude(this->getSaude() + nutri - toxic);
    this->setFome(0);
}
