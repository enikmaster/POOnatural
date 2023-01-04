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
void Animal::escolhePeso(int min, int max){
    this->setPeso(aleatorio(min, max));
}
int Animal::aleatorio(int min, int max) {
    return min + rand() % (max + 1 - min);
}