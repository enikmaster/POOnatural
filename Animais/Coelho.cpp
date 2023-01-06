#include "Coelho.h"
#include "../Alimentos/Alimento.h"
#include "../Reserva/Local.h"

Coelho::Coelho(char l, int posX, int posY, Reserva *reserva) : Animal(l, posX, posY, reserva) {
    nasce();
    populateWithinRange();
}
Coelho::Coelho(const Coelho& outro) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    nasce();
    setPosX(aleatorio((this->getPosX() - 10 < 0) ? 0 : this->getPosX() - 10, (this->getPosX() - 10 > outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX() : this->getPosX() + 10));
    setPosY(aleatorio((this->getPosY() - 10 < 0) ? 0 : this->getPosY() - 10, (this->getPosY() - 10 > outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY() : this->getPosY() + 10));
    populateWithinRange();
}
Coelho::~Coelho() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
}
void Coelho::nasce() {
    setIsAlive(true);
    setSaude(constantes::sCoelho);
    setPercepcao(constantes::pCoelho);
    setdeslMin(1);
    setdeslMax(2);
    setIdade(0);
    escolhePeso(1, 4);
    setFome(0);
    setAlimentacao("verdura");
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
    int direction = 0;
    int distAliX, distAliY, distPredX, distPredY = getPercepcao();
    int movingDirectionX = this->getPosX();
    int movingDirectionY = this->getPosY();
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
            for(int i = 0; i != alimento->getQuantidadeCheiros();++i){
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
    Animal *pA = new Coelho(*this);
    Local *pL = new Local(pA->getAnimalId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva());
    reservaAnimal->addLocal(pL);
    return pA;
}
void Coelho::cicloTurno() {
    // atualiza vida
    setIdade(this->getIdade() + 1);
    checkVitality();
    if(getIsAlive()) {
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
        if(this->getFome() <= 10)
            setdeslMax(2);
        checkVitality();
    }
    if(getIsAlive()) {
        // primeiro come se houver alimento na posição
        for (auto& alimento : alimentosPerto) {
            if (alimento->getPosX() == getPosX() && alimento->getPosY() == getPosY()) {
                for (int i = 0; i != alimento->getQuantidadeCheiros(); ++i) {
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
            if(aleatorio(0, 1))
                reservaAnimal->addAnimal(fazOutro());
        }
        // atualiza a população Within Range de acordo com a nova posição
        populateWithinRange();
    }
    if(!getIsAlive())
        dies();
    reservaAnimal->updateLocal(getAnimalId(), getPosX(), getPosY());
}

/*
void Coelho::fomeca() { // vai ser chamada a cada tick
    int fome = Animal::getFome();
    Animal::setFome(fome + 1);

    if (fome > 20){
        SCoelho -= 2;
        Animal::setdeslMin(1);
        Animal::setdeslMax(4);
    }
    if (fome > 10 && fome < 20) {
        SCoelho--;
        Animal::setdeslMin(1);
        Animal::setdeslMax(3);
    }
}


Animal* Coelho::fazOutro(Reserva *r) {
    if ((Animal::getTick() % 8) == 0) {
        int flag = rand() % 2 + 1;
        if ( flag == 1 ) {
            Animal* p = new Coelho(r);
            r->pushBackVectorAnimais(p);
            Reserva::contAnimais++;
            int aux1=rand() % 21 - 10;
            int aux2=rand() % 21 - 10;
            p->setPosX(aux1);
            p->setPosY(aux2);
            Local *a = new Local(Reserva::contPosOcupadas, p->getPosX()+aux1, p->getPosY()+aux2, "animal",'C', r);
            r->pushBackVectorPosOcupadas(a);
            Reserva::contPosOcupadas++;
        }
    }
}

void Coelho::move(int xTarget, int yTarget, int flag) {

    // IMPORTANTE:
    // SE FLAG = 1, ENTAO O COELHO ESTÁ A CAMINHAR PARA O OBJETO
    // SE FLAG = -1, ENTAO O COELHO ESTÁ A FUGIR DO OBJETO

    int runningSpeed = rand () % getdeslMax() + getdeslMin();

    if (getPosX() < xTarget) {
        setPosX(getPosX()+flag*runningSpeed);
        return;
    }
    if (getPosX() > xTarget) {
        setPosX(getPosX()-flag*runningSpeed);
        return;
    }
    if (getPosY() < yTarget) {
        setPosY(getPosY()+flag*runningSpeed);
        return;
    }
    if (getPosY() > yTarget) {
        setPosY(getPosY()-flag*runningSpeed);
        return;
    }
}


void Coelho::checkSurroundings(Reserva *r, Local *l, int x, int y, int radius, int id) {

    Animal* esteCoelho = r->getAnimalById(r, id);

    for (int i = x-radius; i < x+radius+1; i++) {
        for (int j = y+radius; i > j-radius-1; j--) {
            if ( i == x && j == y ) {
                // na mesma pos:
                if (l->getLocalX() == x && l->getLocalY() == y) {
                    if (l->getSiglaOcupante() == 'r' || l->getSiglaOcupante() == 't') {
                        Alimento* alvo = r->getAlimentoById(r, l->getOcupaId());
                        if (alvo->getCheiro1() == "verdura") {
                        Animal::setFome( alvo->getNutri() );
                        r->removeAlimentoFromVector(l->getOcupaId());
                        r->removePosFromVector(l->getOcupaId());
                        delete alvo;
                        return;
                        }
                    }
                }
            }
            // se estiver no range e for animal
            if (l->getLocalX() == x && l->getLocalY() == y) {
                if (l->getTipoOcupante() == "animal") {
                    Animal* alvo = r->getAnimalById(r, l->getOcupaId());
                    if (alvo->getPeso() > 10) {
                        move(alvo->getPosX(), alvo->getPosY(), -1);
                        return;
                    }
                }
            }
            // se estiver no range e for alimento
            if (l->getLocalX() == x && l->getLocalY() == y) {
                if (l->getSiglaOcupante() == 'r' || l->getSiglaOcupante() == 't') {
                    Alimento* alvo = r->getAlimentoById(r, l->getOcupaId());
                    if (alvo->getCheiro1() == "verdura")
                        move(alvo->getPosX(), alvo->getPosY(), 1);
                    return;
                }
            }
        }
    }
}

void Coelho::dies(Reserva *r, int id) {
    if (VCoelho == 0) {
        r->removeAnimalFromVector(id);
        delete r->getAnimalById(r,id);
        return;
    }
}*/