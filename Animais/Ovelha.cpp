#include "Ovelha.h"
#include "../Alimentos/Corpo.h"
#include "../Reserva/Local.h"

Ovelha::Ovelha(char l, const int x, const int y, Reserva* zoo) : Animal(l, x, y, zoo) {
    zoo->incContadorIds();
    this->setAnimalID(zoo->getContadorIds());
    if (x == -1) {
        int tempX{0};
        int tempY{0};
        do {
            tempX = this->aleatorio(0, reservaAnimal->getDimX() - 1);
            tempY = this->aleatorio(0, reservaAnimal->getDimY() - 1);
        } while (zoo->checkPosOcupado(tempX, tempY));
        this->setPosX(tempX);
        this->setPosY(tempY);
    }
    this->nasce();
    this->populateWithinRange();
}
Ovelha::Ovelha(char l, Reserva* zoo) : Ovelha(l, -1, -1, zoo) {}
Ovelha::Ovelha(const Ovelha& outro, bool value) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva(), value) {
    if(!getToClone()) {
        outro.reservaAnimal->incContadorIds();
        this->setAnimalID(outro.reservaAnimal->getContadorIds());
        this->nasce();
        this->setSaude(outro.getSaude());
        this->setPosX(aleatorio((this->getPosX() - 12 < 0) ? 0 : this->getPosX() - 12, (this->getPosX() - 12 >= outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX() - 1 : this->getPosX() + 12));
        this->setPosY(aleatorio((this->getPosY() - 12 < 0) ? 0 : this->getPosY() - 12, (this->getPosY() - 12 >= outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY() - 1 : this->getPosY() + 12));
        this->populateWithinRange();
    } else {
        this->nasce();
        this->setAnimalID(outro.getAnimalId());
        this->setSaude(outro.getSaude());
        this->setPeso(outro.getPeso());
        this->setFome(outro.getFome());
        this->setIdade(outro.getIdade());
        setToClone(false);
    }
}
Ovelha::~Ovelha() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
    // criar um novo alimento corpo junto a esta posição
    Alimento* pCorpo {new Corpo(this->getPosX() + 1, this->getPosY(), this->getPeso(), this->getReserva())};
    reservaAnimal->addFood(pCorpo);
    Local* pLocal {new Local(pCorpo->getFoodId(), pCorpo->getPosX(), pCorpo->getPosY(), pCorpo->getLetra(), this->getReserva())};
    reservaAnimal->addLocal(pLocal);
}
// getters
int Ovelha::getVelocidade() {
    return (this->getdeslMax() == this->getdeslMin()) ? this->getdeslMax() : this->aleatorio(this->getdeslMin(), this->getdeslMax());
}
// setters
// actions
// verifica se está na hora de morrer
void Ovelha::checkVitality() {
    if(getSaude() <= 0 || getIdade() >= constantes::vOvelha)
        dies();
}
// verifica as imediações e move-se
void Ovelha::checkSurrounding() {
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
            if(animal->getPeso() > 15) { // apercebe-se de um predador
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
                // enfim, são ovelhas
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
// set dos valores iniciais
void Ovelha::nasce() {
    this->setIsAlive(true);
    this->setPercepcao(constantes::pOvelha);
    this->setSaude(constantes::sOvelha);
    this->setdeslMin(1);
    this->setdeslMax(1);
    this->setIdade(0);
    this->escolhePeso(4, 8);
    this->setFome(0);
    this->setAlimentacao("erva");
}
// faz uma cópia de si mesmo
Animal* Ovelha::fazOutro() {
    Animal* pA {new Ovelha(*this)};
    Local* pL {new Local(pA->getAnimalId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva())};
    reservaAnimal->addLocal(pL);
    return pA;
}
void Ovelha::cicloTurno() {
    if(getIsAlive()) {
        // atualiza a população Within Range antes de tudo o resto
        populateWithinRange();
        // atualiza vida
        setIdade(this->getIdade() + 1);
        checkVitality();
        // atualiza a fome
        setFome(this->getFome() + 1);
        // atualiza a saúde e a velocidade de acordo com a fome
        if(this->getFome() > 20)
            setSaude(this->getSaude() - 2);
        if(this->getFome() <= 20 && this->getFome() > 15) {
            setSaude(this->getSaude() - 1);
            setdeslMax(2);
        }
        if(this->getFome() <= 15)
            setdeslMax(1);
        checkVitality();
    }
    if(getIsAlive()) {
        // primeiro come se houver alimento na posição
        for (auto& alimento : alimentosPerto) {
            if (alimento->getPosX() == getPosX() && alimento->getPosY() == getPosY()) {
                for (int i {0}; i != alimento->getQuantidadeCheiros(); ++i) {
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
        if(this->getIdade() % 15 == 0 )
            reservaAnimal->addAnimal(fazOutro());
    }
    if(!getIsAlive())
        dies();
    reservaAnimal->updateLocal(getAnimalId(), getPosX(), getPosY());
}