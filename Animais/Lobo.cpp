#include "Lobo.h"
#include "../Alimentos/Alimento.h"
#include "../Alimentos/Corpo.h"
#include "../Reserva/Local.h"

Lobo::Lobo(char l, int posX, int posY, Reserva* reserva) : Animal(l, posX, posY, reserva) {
    nasce();
    populateWithinRange();
}
Lobo::Lobo(char l, Reserva* reserva) : Lobo(l, -1, -1, reserva) {};
Lobo::Lobo(const Lobo& outro) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    this->nasce();
    this->setPosX(aleatorio((this->getPosX() - 15 < 0) ? 0 : this->getPosX() - 15, (this->getPosX() - 15 >= outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX()-1 : this->getPosX() + 15));
    this->setPosY(aleatorio((this->getPosY() - 15 < 0) ? 0 : this->getPosY() - 15, (this->getPosY() - 15 >= outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY()-1 : this->getPosY() + 15));
    this->populateWithinRange();
}
Lobo::~Lobo() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
    // criar um novo alimento corpo junto a esta posição
    Alimento* pCorpo {new Corpo(this->getPosX() + 1, this->getPosY(), 10, this->getReserva())};
    reservaAnimal->addFood(pCorpo);
    Local* pLocal {new Local(pCorpo->getFoodId(), pCorpo->getPosX(), pCorpo->getPosY(), pCorpo->getLetra(), this->getReserva())};
    reservaAnimal->addLocal(pLocal);
}
//getters;
int Lobo::getVelocidade() {
    return aleatorio(getdeslMin(), getdeslMax());
}
// setters
// actions
// set dos valores iniciais
void Lobo::nasce() {
    setIsAlive(true);
    setPercepcao(constantes::pLobo);
    setSaude(constantes::sLobo);
    setdeslMin(1);
    setdeslMax(1);
    escolhePeso(15, 15);
    setIdade(0);
    setFome(0);
    setAlimentacao("carne");
    setReproDay();
}
void Lobo::checkSurrounding() {
    // verifica o que está dentro do raio de percepção
    // e movimenta de acordo
    int maisPesado {0};
    bool direction {false};
    int distAliX {getPercepcao()};
    int distAliY {getPercepcao()};
    int movingDirectionX {this->getPosX()};
    int movingDirectionY {this->getPosY()};
    // verifica se há alimentos perto caso não esteja a caçar
    if(!alimentosPerto.empty()) {
        for(auto& alimento : alimentosPerto) {
            for(int i {0}; i != alimento->getQuantidadeCheiros();++i){
                if(alimento->getCheiro(i) == getAlimentacao()) {
                    // distancia mais curta ao alimento que cheira a carne
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
                    direction = true; // assinala que está a ir numa direção não aleatória
                }
            }
        }
    }
    // verifica se há animais perto e não vai comer
    if(!animaisPerto.empty() && !direction ) {
        for(auto& animal : animaisPerto) {
            if(animal->getAnimalId() == this->getAnimalId())
                continue;
            if(animal->getPeso() > maisPesado) { // apercebe-se de uma presa
                if(getFome() > 15) {
                    setdeslMin(3);
                    setdeslMax(3);
                } else {
                    setdeslMin(2);
                    setdeslMax(2);
                }
                maisPesado = animal->getPeso();
                (animal->getPosX() < this->getPosX()) ?
                        movingDirectionX = this->getPosX() - this->getVelocidade() :
                        movingDirectionX = this->getPosX() + this->getVelocidade();
                (animal->getPosY() < this->getPosY()) ?
                        movingDirectionY = this->getPosY() - this->getVelocidade() :
                        movingDirectionY = this->getPosY() + this->getVelocidade();
                // vai em direção à presa mais pesada
                direction = true; // assinala que está a ir numa direção não aleatória
            }
        }
    }

    // se estiver a perseguir uma presa ou em direção a um alimento
    (direction) ? move(movingDirectionX, movingDirectionY) :
    // se não estiver, aleatório
    move(aleatorio(getPosX() - getdeslMax(), getPosX() + getdeslMax()), aleatorio(getPosY() - getdeslMax(), getPosY() + getdeslMax()));
}
void Lobo::checkVitality() {
    if(getSaude() <= 0)
        dies();
}
// faz uma cópia de si mesmo
Animal* Lobo::fazOutro() {
    Animal* pA {new Lobo(*this)};
    Local* pL {new Local(pA->getAnimalId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva())};
    reservaAnimal->addLocal(pL);
    return pA;
}
void Lobo::cicloTurno() {
    // verifica se está vivo
    // como cada animal é atualizado de cada vez, na altura a que chega a este
    // pode já ter sido morto
    if(getIsAlive()) {
        // atualiza a população Within Range de acordo com a nova posição
        populateWithinRange();
        // atualiza a vida
        setIdade(getIdade() + 1);
        // atualiza a fome
        setFome(getFome() + 2);
        if(getFome() <= 15) {
            // atualiza a velocidade
            setdeslMin(1);
            setdeslMax(1);
        }
        if(getFome() > 15 && getFome() <= 25) {
            // atualiza a velocidade e a saude
            setSaude(this->getSaude() - 1);
            setdeslMin(2);
            setdeslMax(2);
        }
        if(getFome() > 25)
            // atualiza a saude
            setSaude(this->getSaude() - 2);
        // verifica se não está morto
        checkVitality();
    }
    // mata e luta
    if(getIsAlive()) {
        for (auto& animal : animaisPerto) {
            if(animal->getAnimalId() == this->getAnimalId())
                continue;
            // animais na mesma posição que o Lobo mas peso igual ou superior
            // fight!!!
            if (animal->getPosX() == getPosX() && animal->getPosY() == getPosY() && animal->getPeso() >= getPeso()) {
                (aleatorio(0, 1)) ? animal->dies() : this->dies();
                if(!getIsAlive())
                    break;
            }
            // animais em posições adjacentes ou na mesma posição do Lobo e peso inferior
            // mata
            if(abs(animal->getPosX() - getPosX()) <= 1 && abs(animal->getPosY() - getPosY()) <= 1 && animal->getPeso() < getPeso())
                animal->dies();
        }
    }
    // come alimento
    if(getIsAlive()) {
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
        // pode ter morrido devido a toxicidade elevada da carne
    }
    if(getIsAlive()) {
        // verifica tudo o que o rodeia
        // e move-se de acordo
        checkSurrounding();
        if(this->getIdade() == this->getReproDay())
            reservaAnimal->addAnimal(fazOutro());
    }
    if(!getIsAlive())
        dies();
    reservaAnimal->updateLocal(getAnimalId(), getPosX(), getPosY());
}