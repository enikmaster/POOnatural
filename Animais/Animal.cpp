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
Animal::~Animal() {}
// getters
// setters
void Animal::addAnimalPerto(Animal* novoAnimal) {
    animaisPerto.push_back(novoAnimal);
}
void Animal::removeAnimalPerto(Animal* velhoAnimal) {
    for(vector<Animal*>::iterator animal = animaisPerto.begin(); animal != animaisPerto.end(); ++animal) {
        if((*animal)->getAnimalId() == velhoAnimal->getAnimalId()) {
            animaisPerto.erase(animal);
            return;
        }
    }
}
void Animal::addAlimentoPerto(Alimento* novoAlimento) {
    alimentosPerto.push_back(novoAlimento);
}
void Animal::removeAlimentoPerot(Alimento* velhoAlimento) {
    for(vector<Alimento*>::iterator alimento = alimentosPerto.begin(); alimento != alimentosPerto.end(); ++alimento) {
        if((*alimento)->getFoodId() == velhoAlimento->getFoodId()) {
            alimentosPerto.erase(alimento);
            return;
        }
    }
}
// actions
void Animal::moveRand(int min, int max) {
    setPosX( getPosX() + aleatorio(-1,3) * aleatorio(min, max));
    setPosY( getPosY() + aleatorio(-1,3) * aleatorio(min, max));
}
void Animal::escolhePeso(int min, int max){
    setPeso(aleatorio(min, max));
}
int Animal::aleatorio(int min, int max) {
    return min + rand() % (max - min);
}