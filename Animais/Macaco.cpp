#include "Macaco.h"
#include "Humano.h"
#include "../Reserva/Local.h"
#include "../Alimentos/Alimento.h"


Macaco::Macaco(char l, int posX, int posY, Reserva *reserva) : Animal(l, posX, posY, reserva){
    reserva->incContadorIds();
    this->setAnimalID(reserva->getContadorIds());
    if (posX == -1) {
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
};
Macaco::Macaco(const Macaco& outro, bool value) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva(), value) {
    if(!getToClone()) {
        outro.reservaAnimal->incContadorIds();
        this->setAnimalID(outro.reservaAnimal->getContadorIds());
        this->nasce();
        this->setPosX(aleatorio((this->getPosX() - 2 < 0) ? 0 : this->getPosX() - 2,
                          (this->getPosX() - 2 >= outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX() - 1 :
                          this->getPosX() + 2));
        this->setPosY(aleatorio((this->getPosY() - 2 < 0) ? 0 : this->getPosY() - 2,
                          (this->getPosY() - 2 >= outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY() - 1 :
                          this->getPosY() + 2));
        this->populateWithinRange();
    } else {
        this->nasce();
        this->setAnimalID(outro.getAnimalId());
        this->setSaude(outro.getSaude());
        this->setPeso(outro.getPeso());
        this->setIdade(outro.getIdade());
        this->setFome(outro.getFome());
        this->setXP(outro.getXP());
        this->setToClone(false);
    }
}
Macaco::~Macaco() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
}
void Macaco::nasce() {
    this->setIsAlive(true);
    this->setSaude(constantes::sMacaco);
    this->setPercepcao(constantes::pMacaco);
    this->setdeslMin(1);
    this->setdeslMax(1);
    this->escolhePeso(10, 20);
    this->setIdade(0);
    this->setFome(0);
    this->setXP(0);
    this->setAlimentacao("fruta");
}

void Macaco::checkVitality() {
    if(getSaude() <= 0 || getIdade() >= constantes::vMacaco)
        dies();
}
int Macaco::getVelocidade() {
    return aleatorio(getdeslMin(), getdeslMax());
}

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
    if (getXP() < 100) {
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