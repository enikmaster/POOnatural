#include "Coelho.h"
#include "../Alimentos/Alimento.h"
#include "../Reserva/Local.h"

Coelho::Coelho(char l, int posX, int posY, Reserva *reserva) : Animal(l, posX, posY, reserva) {
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
    this->nasce();
    this->populateWithinRange();
}
Coelho::Coelho(char l, Reserva* reserva) : Coelho(l, -1, -1, reserva) {};
Coelho::Coelho(const Coelho& outro, bool value) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva(), value) {
    if(!getToClone()) {
        outro.reservaAnimal->incContadorIds();
        this->setAnimalID(outro.reservaAnimal->getContadorIds());
        this->nasce();
        this->setPosX(aleatorio((this->getPosX() - 10 < 0) ? 0 : this->getPosX() - 10, (this->getPosX() - 10 >= outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX()-1 : this->getPosX() + 10));
        this->setPosY(aleatorio((this->getPosY() - 10 < 0) ? 0 : this->getPosY() - 10, (this->getPosY() - 10 >= outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY()-1 : this->getPosY() + 10));
        this->populateWithinRange();
    } else {
        this->nasce();
        this->setAnimalID(outro.getAnimalId());
        this->setSaude(outro.getSaude());
        this->setPeso(outro.getPeso());
        this->setFome(outro.getFome());
        this->setIdade(outro.getIdade());
        this->setToClone(false);
    }
}
Coelho::~Coelho() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
}
// set dos valores iniciais
void Coelho::nasce() {
    this->setIsAlive(true);
    this->setSaude(constantes::sCoelho);
    this->setPercepcao(constantes::pCoelho);
    this->setdeslMin(1);
    this->setdeslMax(2);
    this->setIdade(0);
    this->escolhePeso(1, 4);
    this->setFome(0);
    this->setAlimentacao("verdura");
}
// getters
int Coelho::getVelocidade() {
    return aleatorio(getdeslMin(), getdeslMax());
}
// setters
// action
// verifica se está na hora de morrer
void Coelho::checkVitality() {
    if(getSaude() <= 0 || getIdade() >= constantes::vCoelho)
        dies();
}
// verifica as imediações e move-se
void Coelho::checkSurrounding() {
    // verifica o que está dentro do raio de percepção
    // e movimenta de acordo
    int direction {0};
    int distAliX {getPercepcao()};
    int distAliY {getPercepcao()};
    int distPredX {getPercepcao()};
    int distPredY {getPercepcao()};
    int movingDirectionX {this->getPosX()};
    int movingDirectionY {this->getPosY()};
    // verifica se há animais perto
    if(!animaisPerto.empty()) {
        for(auto& animal : animaisPerto) {
            if(animal->getAnimalId() == this->getAnimalId())
                continue;
            if(animal->getPeso() > 10) { // apercebe-se de um predador
                if(abs(animal->getPosX() - this->getPosX()) <= distPredX) {
                    distPredX = abs(animal->getPosX() - this->getPosX());
                    (animal->getPosX() > this->getPosX()) ?
                            movingDirectionX = this->getPosX() - this->getVelocidade() :
                            movingDirectionX = this->getPosX() + this->getVelocidade();
                }
                if(abs(animal->getPosY() - this->getPosY()) <= distPredY) {
                    distPredY = abs(animal->getPosY() - this->getPosY());
                    (animal->getPosY() > this->getPosY()) ?
                            movingDirectionY = this->getPosY() - this->getVelocidade() :
                            movingDirectionY = this->getPosY() + this->getVelocidade();
                }
                // foge sempre do predador mais perto, mesmo que isso o empurre para outro mais longe
                // enfim, são coelhos
                direction = 1; // assinala que está a ir numa direção não aleatória
            }
        }
    }
    // verifica se há alimentos perto caso não esteja a fugir
    if(!alimentosPerto.empty() && !direction) {
        for(auto& alimento : alimentosPerto) {
            for(int i {0}; i != alimento->getQuantidadeCheiros();++i){
                if(alimento->getCheiro(i) == getAlimentacao()) {
                    // distancia mais curta ao alimento que cheira a relva
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
                        if(distAliY <= getdeslMax() and distAliX <= getdeslMax()) {
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
    // se estiver a ir fugir de um predador ou em direção a um alimento
    (direction) ? move(movingDirectionX, movingDirectionY) :
    // se não estiver, aleatório
    move(aleatorio(getPosX() - getdeslMax(), getPosX() + getdeslMax()), aleatorio(getPosY() - getdeslMax(), getPosY() + getdeslMax()));
}
// faz uma cópia de si mesmo
Animal* Coelho::fazOutro() {
    Animal *pA {new Coelho(*this)};
    Local *pL {new Local(pA->getAnimalId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva())};
    reservaAnimal->addLocal(pL);
    return pA;
}
void Coelho::cicloTurno() {
    if(getIsAlive()) {
        // atualiza a população Within Range de acordo com a nova posição
        populateWithinRange();
        // atualiza vida
        setIdade(this->getIdade() + 1);
        checkVitality();
        // atualiza a fome
        setFome(this->getFome() + 1);
        // atualiza a saúde e a velocidade de acordo com a fome
        if(this->getFome() > 20) {
            setSaude(this->getSaude() - 2);
            setdeslMax(4);
        }
        if(this->getFome() <= 20 && this->getFome() > 10) {
            setSaude(this->getSaude() - 1);
            setdeslMax(3);
        }
        if(this->getFome() <= 10) {
            setdeslMax(2);
        }
        checkVitality();
    }
    if(getIsAlive()) {
        // primeiro come se houver alimento na posição
        for (auto& alimento : alimentosPerto) {
            if (alimento->getPosX() == getPosX() && alimento->getPosY() == getPosY()) {
                for(int i {0}; i != alimento->getQuantidadeCheiros(); ++i) {
                    if (alimento->getCheiro(i) == getAlimentacao()) {
                        come(alimento->getNutri(), alimento->getToxic());
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
            if(aleatorio(0, 1)) {
                reservaAnimal->addAnimal(fazOutro());
            }
        }
    }
    if(!getIsAlive())
        dies();
    reservaAnimal->updateLocal(getAnimalId(), getPosX(), getPosY());
}