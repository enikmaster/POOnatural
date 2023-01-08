#include "Humano.h"

Humano::Humano(char l, int posX, int posY, Reserva *reserva) : Animal(l, posX, posY, reserva){
    nasce();
}
Humano::~Humano() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
}

void Humano::nasce() {
    setIsAlive(true);
    setSaude(constantes::sHumano);
    setPercepcao(constantes::pHumano);
    setdeslMin(1);
    setdeslMax(1);
    setIdade(0);
    escolhePeso(10,12);
    setFome(0);
    checkDirection();
}

void Humano::checkDirection() {
    if(reservaAnimal->getDimX() - getPosX() >= reservaAnimal->getDimY() - getPosY()) {
        // vai para cima/baixo
        if (getPosX() < reservaAnimal->getDimX()/2 ) {
            // vai para cima
            setDirection("esquerda");
        } else {
            // vai para baixo
            setDirection("direita");
        }
    }
    if (reservaAnimal->getDimX() - getPosY() < reservaAnimal->getDimY() - getPosY()) {
        // vai para cima/baixo
        if (getPosY() < reservaAnimal->getDimY()/2 ) {
            // vai para cima
            setDirection("cima");
        } else {
            // vai para baixo
            setDirection("baixo");
        }
    }
}

void Humano::checkSurrounding() {

    if (reservaAnimal->getDimX()-1 == getPosX() || reservaAnimal->getDimY()-1 == getPosY()) {
        return dies();
    }
    if (0 == getPosX() || 0 == getPosY()) {
        return dies();
    }
    if (direction == "cima") {
        move(getPosX(), getPosY() - getdeslMax());
    }
    if (direction == "baixo") {
        move(getPosX(), getPosY() + getdeslMax());
    }
    if (direction == "esquerda") {
        move(getPosX() - getdeslMax(), getPosY());
    }
    if (direction == "direita") {
        move(getPosX() + getdeslMax(), getPosY());
    }
}


void Humano::checkVitality() {
    if(getIdade() >= constantes::vHumano)
        dies();
}

void Humano::cicloTurno() {
    // atualiza vida
    setIdade(this->getIdade() + 1);
    checkVitality();

    if(getIsAlive()) {
        // verifica tudo o que o rodeia
        // e move-se de acordo
        checkSurrounding();
    }
    if(!getIsAlive())
        dies();
    reservaAnimal->updateLocal(getAnimalId(), getPosX(), getPosY());
}

