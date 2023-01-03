#include "Animal.h"
#include "../Alimentos/Alimento.h"
#include "../Reserva/Reserva.h"

Animal::Animal(std::string l, const int x, const int y, Reserva* novaReserva) : letra(std::move(l)), posX(x), posY(y), reservaAnimal(novaReserva) {
    setAnimalID(reservaAnimal->getContadorIds());
    reservaAnimal->incContadorIds();
    if(x == -1) {
        int temp = 0;
        do {
            temp = rand() % reservaAnimal->getDimX();
        } while(reservaAnimal->checkPosXOcupado(temp));
        setPosX(temp);
        do {
            temp = rand() % reservaAnimal->getDimY();
        } while(reservaAnimal->checkPosYOcupado(temp));
        setPosY(temp);
    }
}
// getters
//Reserva* Animal::getReserva() {
////    Reserva* pCopiaReserva = new Reserva();
//}
// setters
void Animal::addAnimalPerto(Animal* novoAnimal) {
    animaisPerto.push_back(novoAnimal);
}
void Animal::addAlimentoPerto(Alimento* novoAlimento) {
    alimentosPerto.push_back(novoAlimento);
}
// actions
void Animal::escolhePeso(int min, int max){
    setPeso(aleatorio(min, max));
}
int Animal::aleatorio(int min, int max) {
    return min + rand() % (max - min);
}