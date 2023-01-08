#include "Macaco.h"
#include "Humano.h"
#include "../Reserva/Local.h"
#include "../Alimentos/Alimento.h"


Macaco::Macaco(char l, int posX, int posY, Reserva *reserva) : Animal(l, posX, posY, reserva){
    nasce();
    populateWithinRange();
};
Macaco::Macaco(const Macaco& outro) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    nasce();
    setPosX(aleatorio((this->getPosX() - 2 < 0) ? 0 : this->getPosX() - 2, (this->getPosX() - 2 >= outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX()-1 : this->getPosX() + 2));
    setPosY(aleatorio((this->getPosY() - 2 < 0) ? 0 : this->getPosY() - 2, (this->getPosY() - 2 >= outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY()-1 : this->getPosY() + 2));
    populateWithinRange();
}
Macaco::~Macaco() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
}
void Macaco::nasce() {
    setIsAlive(true);
    setSaude(constantes::sMacaco);
    setPercepcao(constantes::pMacaco);
    setdeslMin(1);
    setdeslMax(1);
    setIdade(0);
    escolhePeso(10, 20);
    setFome(0);
    contadorXp = 0;
    setAlimentacao("fruta");
}


void Macaco::checkVitality() {
    if(getSaude() <= 0 || getIdade() >= constantes::vMacaco)
        dies();
}
int Macaco::getVelocidade() {
    return aleatorio(getdeslMin(), getdeslMax());
}


int Macaco::getContadorXp() { return this->contadorXp;}

// verifica as imediações e move-se
void Macaco::checkSurrounding() {
    // verifica o que está dentro do raio de percepção
    // e movimenta de acordo
    int direction = 0;
    int distAliX, distAliY, distPredX, distPredY = getPercepcao();
    int movingDirectionX = this->getPosX();
    int movingDirectionY = this->getPosY();
    // verifica se há alimentos perto caso não esteja a fugir
    if(!alimentosPerto.empty()) {
        for(auto& alimento : alimentosPerto) {
            for(int i = 0; i != alimento->getQuantidadeCheiros();++i){
                if(alimento->getCheiro(i) == getAlimentacao()) {
                    // distancia mais curta ao alimento que cheira a fruta
                    if(abs(alimento->getPosX() - this->getPosX()) <= distAliX) {
                        distAliX = abs(alimento->getPosX() - this->getPosX());
                        if(distAliX <= getdeslMax()) {
                            movingDirectionX = alimento->getPosX();
                        } else {
                            (alimento->getPosX() < this->getPosX()) ?
                                    movingDirectionX = this->getPosX() - this->getVelocidade() :
                                    movingDirectionX = this->getPosX() + this->getVelocidade() ;
                        }
                    }
                    if(abs(alimento->getPosY() - this->getPosY()) <= distAliY) {
                        distAliY = abs(alimento->getPosY() - this->getPosY());
                        if(distAliY <= getdeslMax() && distAliX <= getdeslMax()) {
                            movingDirectionY = alimento->getPosY();
                        } else {
                            (alimento->getPosY() < this->getPosY()) ?
                                    movingDirectionY = this->getPosY() - this->getVelocidade() :
                                    movingDirectionY = this->getPosY() + this->getVelocidade() ;
                        }
                    }
                    direction = 1; // assinala que está a ir numa direção não aleatória
                }
            }
        }
    }
    (direction) ? move(movingDirectionX, movingDirectionY) :
    // mover aleatório
    move(aleatorio(getPosX() - getdeslMax(), getPosX() + getdeslMax()), aleatorio(getPosY() - getdeslMax(), getPosY() + getdeslMax()));
}

Animal* Macaco::fazOutro() {
    if (getContadorXp() < 100) {
    Animal *pA = new Macaco(*this);
    Local *pL = new Local(pA->getAnimalId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva());
    reservaAnimal->addLocal(pL);
    return pA;
    } else {
        Animal *pA = new Humano('H', getPosX() + 1, getPosX(), reservaAnimal);
        Local *pL = new Local(pA->getAnimalId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva());
        reservaAnimal->addLocal(pL);
        return pA;
    }
}

void Macaco::xpGain() {
    contadorXp += 25;
}

void Macaco::cicloTurno() {
    // atualiza a população Within Range de acordo com a nova posição
    populateWithinRange();
    // atualiza vida
    setIdade(this->getIdade() + 1);
    checkVitality();
    if(getIsAlive()) {
        // atualiza a saúde e a velocidade de acordo com a fome
        if(this->getFome() > 10) {
            setSaude(this->getSaude() - 1);
            setdeslMax(2);
            checkVitality();
        }
    }
    if(getIsAlive()) {
        // primeiro come se houver alimento na posição
        for (auto& alimento : alimentosPerto) {
            if (alimento->getPosX() == getPosX() && alimento->getPosY() == getPosY()) {
                for (int i = 0; i != alimento->getQuantidadeCheiros(); ++i) {
                    if (alimento->getCheiro(i) == getAlimentacao()) {
                        come(alimento->getNutri(), alimento->getToxic());
                        xpGain();
                        alimento->setIsAlive(false);
                    }
                }
            }
        }
        // verifica se depois de comer ainda está vivo
        checkVitality();
        // pode ter morrido devido a toxicidade elevada
    }
    if(getIsAlive()) {
        // verifica tudo o que o rodeia
        // e move-se de acordo
        checkSurrounding();
        if(this->getIdade() % 8 == 0 ) {
            if(aleatorio(0, 1))
                reservaAnimal->addAnimal(fazOutro());
        }

    }
    if(!getIsAlive())
        dies();
    reservaAnimal->updateLocal(getAnimalId(), getPosX(), getPosY());
}