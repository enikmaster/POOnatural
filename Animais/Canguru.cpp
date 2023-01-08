#include "Canguru.h"
#include "../Alimentos/Alimento.h"
#include "../Alimentos/Corpo.h"
#include "../Reserva/Local.h"

Canguru::Canguru(char l, int posX, int posY, Reserva* reserva) : Animal(l, posX, posY, reserva) {
    nasce();
    populateWithinRange();
}
Canguru::Canguru(char l, Reserva* reserva) : Canguru(l, -1, -1, reserva) {}
Canguru::Canguru(const Canguru& outro) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    nasce();
    setIdPai(outro.getAnimalId());
    setPosX(aleatorio((this->getPosX() - 3 < 0) ? 0 : this->getPosX() - 3, (this->getPosX() - 3 >= outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX()-1 : this->getPosX() + 3));
    setPosY(aleatorio((this->getPosY() - 3 < 0) ? 0 : this->getPosY() - 3, (this->getPosY() - 3 >= outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY()-1 : this->getPosY() + 3));
    populateWithinRange();
}
Canguru::~Canguru() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
    if(!getToEmpty()){
        // criar um novo alimento corpo junto a esta posição
        Alimento *pCorpo{new Corpo(this->getPosX() + 1, this->getPosY(), 15, this->getReserva())};
        pCorpo->setToxic(5);
        reservaAnimal->addFood(pCorpo);
        Local *pLocal = new Local(pCorpo->getFoodId(), pCorpo->getPosX(), pCorpo->getPosY(), pCorpo->getLetra(),
                                  this->getReserva());
        reservaAnimal->addLocal(pLocal);
    }
}
// getters
int Canguru::getVelocidade() {
    return aleatorio(getdeslMin(), getdeslMax());
}
// setters
// actions
// set dos valores iniciais
void Canguru::nasce() {
    setIsAlive(true);
    setPercepcao(constantes::pCanguru);
    setSaude(constantes::sCanguru);
    setdeslMin(1);
    setdeslMax(1);
    escolhePeso(10, 10);
    setIdade(0);
    setFome(0);
    setAlimentacao("indeterminado");
    setIdPai(0);
    setNaBolsa(false);
    setIdadeNaBolsa(0);
    setMedo(false);
}
// verifica os arredores e move-se
void Canguru::checkSurrounding() {
    // verifica o que está dentro do raio de percepção
    // e movimenta de acordo
    int movingDirectionX {aleatorio(getPosX() - getdeslMax(), getPosX() + getdeslMax())};
    int movingDirectionY {aleatorio(getPosY() - getdeslMax(), getPosY() + getdeslMax())};
    int posPaiX {getPosX()};
    int posPaiY {getPosY()};
    bool orfan {true};
    // verifica se há animais perto
    if(!isAdult()){
        if (!animaisPerto.empty()) {
            // procura e regista a posição do progenitor
            if (getIdPai() != 0) {
                for (auto &animal: animaisPerto) {
                    if (animal->getAnimalId() == this->getIdPai()) {
                        orfan = false;
                        posPaiX = animal->getPosX();
                        posPaiY = animal->getPosY();
                    }
                }
                if (orfan)
                    setIdPai(0);
            }
            // se for bebe, fica sempre perto do progenitor
            if (!orfan && isBaby()) {
                do {
                    movingDirectionX = aleatorio(getPosX() - getdeslMax(), getPosX() + getdeslMax());
                } while (!(movingDirectionX > posPaiX - 4 && movingDirectionX < posPaiX + 4));
                do {
                    movingDirectionY = aleatorio(getPosY() - getdeslMax(), getPosY() + getdeslMax());
                } while (!(movingDirectionY > posPaiY - 4 && movingDirectionY < posPaiY + 4));
            }
            for (auto& animal : animaisPerto) {
                if (animal->getAnimalId() == this->getAnimalId() || animal->getAnimalId() == this->getIdPai()) {
                    setMedo(false);
                    setdeslMax(1);
                    setdeslMin(1);
                    continue;
                }
                // apercebe-se de uma animal que não é ele ou o progenitor
                // se não tiver progenitor
                if (orfan) {
                    setMedo(true);
                    setdeslMax(2);
                    setdeslMin(2);
                }
                // se tiver progenitor
                if (!orfan) {
                    // se já está na bolsa
                    if (naBolsa) {
                        if (getIdadeNaBolsa() == getIdade()) {
                            setNaBolsa(false);
                            setMedo(false);
//                            setVisible(true);
                        }
                        movingDirectionX = posPaiX;
                        movingDirectionY = posPaiY;
                    } else { // se não está na bolsa
                        if (this->getPosX() == posPaiX &&
                            this->getPosY() == posPaiY) { // se já está na posição do progenitor
                            setNaBolsa(true);
//                            setVisible(false);
                            setIdadeNaBolsa(this->getIdade());
                        } else { // se não está na posição do progenitor
                            setMedo(true);
                            setdeslMax(2);
                            setdeslMin(2);
                            if (abs(this->getPosX() - posPaiX) <= getdeslMax()) {
                                movingDirectionX = posPaiX;
                            } else {
                                (posPaiX < this->getPosX()) ?
                                        movingDirectionX = this->getPosX() - this->getVelocidade() :
                                        movingDirectionX = this->getPosX() + this->getVelocidade();
                            }
                            if (abs(this->getPosY() - posPaiY) <= getdeslMax()) {
                                movingDirectionY = posPaiY;
                            } else {
                                (posPaiY < this->getPosY()) ?
                                        movingDirectionY = this->getPosY() - this->getVelocidade() :
                                        movingDirectionY = this->getPosY() + this->getVelocidade();
                            }
                        }
                    }
                }
            }
        }
    }
    // movimenta-se
    move(movingDirectionX, movingDirectionY);
    // depois de se movimentar verifica se está na posição do progenitor e entra na bolsa
    if(!isAdult()){
        if (!orfan && !naBolsa) {
            if (this->getPosX() == posPaiX && this->getPosY() == posPaiY) { // se já está na posição do progenitor
                setNaBolsa(true);
//                setVisible(false);
                setIdadeNaBolsa(this->getIdade());
            }
        }
    }
}
// verifica se tem idade inferior a 10
bool Canguru::isBaby() const {
    return (getIdade() < 10);
}
// verifica se tem idade igual ou superior a 20
bool Canguru::isAdult() const {
    return (getIdade() >= 20);
}
// faz uma cópia de si mesmo
Animal* Canguru::fazOutro() {
    Animal* pA {new Canguru(*this)};
    Local* pL {new Local(pA->getAnimalId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva())};
    reservaAnimal->addLocal(pL);
    return pA;
}
void Canguru::cicloTurno() {
    // verifica se não foi morto
    if(getIsAlive()){
        populateWithinRange();
        // atualiza a vida
        setIdade(getIdade() + 1);
        if(isAdult())
            setPeso(20);
        checkSurrounding();
        if(this->getIdade() % 30 == 0)
            reservaAnimal->addAnimal(this->fazOutro());
    }
    if(!getIsAlive())
        dies();
    reservaAnimal->updateLocal(getAnimalId(), getPosX(), getPosY());
}