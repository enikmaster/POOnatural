#include "Humano.h"
#include "../Alimentos/Alimento.h"
#include "../Alimentos/Corpo.h"
#include "../Reserva/Local.h"

Humano::Humano(char l, int posX, int posY, Reserva *reserva) : Animal(l, posX, posY, reserva){
    reserva->incContadorIds();
    this->setAnimalID(reserva->getContadorIds());
    if(posX == -1) {
        int tempX{0};
        int tempY{0};
        do {
            tempX = this->aleatorio(0, reservaAnimal->getDimX() - 1);
            tempY = this->aleatorio(0, reservaAnimal->getDimY() - 1);
        } while (reserva->checkPosOcupado(tempX, tempY));
        this->setPosX(tempX);
        this->setPosY(tempY);
    }
    nasce();
    populateWithinRange();
}
Humano::Humano(char l, Reserva* reserva) : Humano(l, -1, -1, reserva) {};
Humano::Humano(const Humano& outro, bool value) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva(), value) {
    if(!getToClone()) {
        outro.reservaAnimal->incContadorIds();
        this->setAnimalID(outro.reservaAnimal->getContadorIds());
        this->nasce();
        this->setPosX(aleatorio((this->getPosX() - 15 < 0) ? 0 : this->getPosX() - 15, (this->getPosX() - 15 >= outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX() - 1 : this->getPosX() + 15));
        this->setPosY(aleatorio((this->getPosY() - 15 < 0) ? 0 : this->getPosY() - 15, (this->getPosY() - 15 >= outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY() - 1 : this->getPosY() + 15));
        this->populateWithinRange();
    } else {
        this->nasce();
        this->setAnimalID(outro.getAnimalId());
        this->setSaude(outro.getSaude());
        this->setPeso(outro.getPeso());
        this->setIdade(outro.getIdade());
        this->setFome(outro.getFome());
        this->setToClone(false);
    }
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

