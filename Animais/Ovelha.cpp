#include "Ovelha.h"
#include "../Alimentos/Corpo.h"
#include "../Reserva/Local.h"

Ovelha::Ovelha(char l, const int x, const int y, Reserva* zoo) : Animal(l, x, y, zoo) {
    this->nasce();
    this->populateWithinRange();
}
Ovelha::Ovelha(char l, Reserva* zoo) : Ovelha(l, -1, -1, zoo) {};
Ovelha::Ovelha(const Ovelha& outro) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {
    this->nasce();
    this->setSaude(outro.getSaude());
    this->setPosX(aleatorio((this->getPosX() - 12 < 0) ? 0 : this->getPosX() - 12, (this->getPosX() - 12 > outro.reservaAnimal->getDimX()) ? outro.reservaAnimal->getDimX() : this->getPosX() + 12));
    this->setPosY(aleatorio((this->getPosY() - 12 < 0) ? 0 : this->getPosY() - 12, (this->getPosY() - 12 > outro.reservaAnimal->getDimY()) ? outro.reservaAnimal->getDimY() : this->getPosY() + 12));
    this->populateWithinRange();
};
Ovelha::~Ovelha() {
    // remove todas as listas de percepção
    animaisPerto.clear();
    alimentosPerto.clear();
    // criar um novo alimento corpo junto a esta posição
    Alimento* pCorpo = new Corpo(this->getPosX()+1, this->getPosY(), this->getPeso(), this->getReserva());
    reservaAnimal->addFood(pCorpo);
    Local* pLocal = new Local(pCorpo->getFoodId(), pCorpo->getPosX(), pCorpo->getPosY(), pCorpo->getLetra(), this->getReserva());
    reservaAnimal->addLocal(pLocal);
}
// getters
int Ovelha::getVelocidade() {
    return (this->getdeslMax() == this->getdeslMin()) ? this->getdeslMax() : this->aleatorio(this->getdeslMin(), this->getdeslMax());
}
// setters

// actions
void Ovelha::checkVitality() {
    if(this->getSaude() <= 0 && this->getIdade() >= constantes::vOvelha)
        this->dies();
}
void Ovelha::come(int nutri, int toxic) {
    this->setSaude(this->getSaude() + nutri - toxic);
}
void Ovelha::populateWithinRange() {
    alimentosPerto.clear();
    animaisPerto.clear();
    vector<int> idAnimaisPerto;
    vector<int> idAlimentosPerto;
    reservaAnimal->checkWithinRange(this->getPosX(), this->getPosY(), this->getPercepcao(), idAnimaisPerto, idAlimentosPerto);
    if(!idAlimentosPerto.empty()){
        for(int& it : idAlimentosPerto)
            addAlimentoPerto(reservaAnimal->getAlimento(it));
    }
    if(!idAnimaisPerto.empty()) {
        for(int& it : idAnimaisPerto)
            addAnimalPerto(reservaAnimal->getAnimal(it));
    }
}

void Ovelha::checkSurrounding() {
    // verifica o que está dentro do raio de percepção
    // e manda movimentar de acordo
    int flag = 0;
    int distAliX, distAliY, distPredX, distPredY = getPercepcao();
    int movingDirectionX = this->getPosX();
    int movingDirectionY = this->getPosY();
    // verifica se há animais perto
    if(!animaisPerto.empty()) {
        for(auto& animal : animaisPerto) {
            if(animal->getAnimalId() == this->getAnimalId())
                continue;
            if(animal->getPeso() > 15) { // apercebe-se de um predador
                if(abs(animal->getPosX() - this->getPosX()) <= distPredX) {
                    distPredX = abs(animal->getPosX() - this->getPosX());
                    (animal->getPosX() > this->getPosX()) ? movingDirectionX = this->getPosX() - this->getVelocidade() : this->getPosX() + this->getVelocidade();
                }
                if(abs(animal->getPosY() - this->getPosY()) <= distPredY) {
                    distPredX = abs(animal->getPosY() - this->getPosY());
                    (animal->getPosY() > this->getPosY()) ? movingDirectionY = this->getPosY() - this->getVelocidade() : this->getPosY() + this->getVelocidade();
                }
                // foge sempre do predador mais perto, mesmo que isso o empurre para outro mais longe
                // enfim, são ovelhas
                flag = 1; // assinala que está a ir numa direção não aleatória
            }
        }
    }
    // verifica se há alimentos perto caso não esteja a fugir
    if(!alimentosPerto.empty() && !flag) {
        for(auto& alimento : alimentosPerto) {
            for(int i = 0; i != alimento->getQuantidadeCheiros();++i){
                if(alimento->getCheiro(i) == getAlimentacao()) {
                    // distancia mais curta ao alimento que cheira a relva
                    if(abs(alimento->getPosX() - this->getPosX()) <= distAliX) {
                        distAliX = abs(alimento->getPosX() - this->getPosX());
                        (alimento->getPosX() < this->getPosX()) ? movingDirectionX = this->getPosX() - this->getVelocidade() : movingDirectionX = this->getPosX() + this->getVelocidade() ;
                    }
                    if(abs(alimento->getPosY() - this->getPosY()) <= distAliY) {
                        distAliY = abs(alimento->getPosY() - this->getPosY());
                        (alimento->getPosY() < this->getPosY()) ? movingDirectionY = this->getPosY() - this->getVelocidade() : movingDirectionY = this->getPosY() + this->getVelocidade() ;
                    }
                    flag = 1; // assinala que está a ir numa direção não aleatória
                }
            }
        }
    }
    // se estiver a ir fugir de um predador ou em direção a um alimento
    (flag) ? move(movingDirectionX, movingDirectionY) :
    // se não estiver, aleatório
    move(
            aleatorio( this->getPosX() - this->getVelocidade(), this->getPosX() + this->getVelocidade() ),
            aleatorio( this->getPosY() - this->getVelocidade(), this->getPosY() + this->getVelocidade() ));

}
void Ovelha::move(int xTarget, int yTarget) {
//    apenas move para a posição fornecida
    setPosX(xTarget);
    setPosY(yTarget);
}
void Ovelha::dies() {
    // remover o animal da lista de animais da reserva e do local
    //reservaAnimal->removeAnimal(this->getAnimalId());
    this->setIsAlive(false);
}
void Ovelha::nasce() {
    this->setIsAlive(true);
    this->setPercepcao(constantes::pOvelha);
    this->setdeslMin(1);
    this->setdeslMax(1);
    this->setSaude(constantes::sOvelha);
    this->setIdade(0);
    this->escolhePeso(4, 8);
    this->setFome(0);
    this->setAlimentacao("erva");
}
Animal* Ovelha::fazOutro() {
    Animal* pA = new Ovelha(*this);
    Local* pL = new Local(pA->getAnimalId(), pA->getPosX(), pA->getPosY(), pA->getLetra(), pA->getReserva());
    reservaAnimal->addLocal(pL);
    return pA;
    /*if ((Animal::getTick() % 15) == 0) {
        Animal* p = new Ovelha(r);
        r->pushBackVectorAnimais(p);
        Reserva::contAnimais++;
        int aux1=rand() % 25 - 12;
        int aux2=rand() % 25 - 12;
        p->setPosX(aux1);
        p->setPosY(aux2);
        p->setSaude(SOvelha);
        Local *a = new Local(Reserva::contPosOcupadas, p->getPosX()+aux1, p->getPosY()+aux2, "animal",'C', r);
        r->pushBackVectorPosOcupadas(a);
        Reserva::contPosOcupadas++;
        return p;
    }
    return nullptr;*/
}
void Ovelha::cicloTurno() {
    // atualiza vida
    setIdade(this->getIdade() + 1);
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
    if(getIsAlive()) {
        // primeiro come se houver alimento na posição
        for (vector<Alimento* >::iterator alimento = alimentosPerto.begin(); alimento != alimentosPerto.end(); ++alimento) {
            if ((*alimento)->getPosX() == this->getPosX() && (*alimento)->getPosY() == this->getPosY()) {
                for (int i = 0; i != (*alimento)->getQuantidadeCheiros(); ++i) {
                    if ((*alimento)->getCheiro(i) == getAlimentacao()) {
                        come((*alimento)->getNutri(), (*alimento)->getToxic());
                        reservaAnimal->removeFood((*alimento)->getFoodId());
                        alimentosPerto.erase(alimento);
                    }
                }
            }
        }
    }
    // verifica se depois de comer ainda está vivo
    checkVitality();
    // pode ter morrido devido a toxicidade elevada
    if(getIsAlive()) {
        // verifica tudo o que o rodeia
        // e move-se de acordo
        checkSurrounding();
        if(this->getIdade() % 15 == 0 ) {
            reservaAnimal->addAnimal(fazOutro());
        }
        // atualiza a população Within Range de acordo com a nova posição
        populateWithinRange();
    }
    if(!getIsAlive()) {
        dies();
    }
}


