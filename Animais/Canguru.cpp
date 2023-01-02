#include "Canguru.h"
#include "../Reserva.h"
#include "../Local.h"
#include "../Alimentos/Corpo.h"


Canguru::Canguru(Reserva *reserva) : SCanguru(20), VCanguru(70), tickMarsupial(0){
    cout << "######## CANGURU ##########\n";
    setdeslMin(1);
    Animal::setdeslMax(1);
    Animal::setPercepcao(7);
    Animal::setPeso(20);
    if(!isAdulto()) {
        checkSurroundings(Animal::getPosX(), Animal::getPosY(), Animal::getPercepcao());
    } else
        Animal::moveRand(Animal::getdeslMin(),Animal::getdeslMax());



};

// substituir futuramente por um fim no getInput ?
bool Canguru::isAdulto() {
    if (Animal::getTick() < 10) {
        return false;
    }
    if (Animal::getTick() == 20) {
        Animal::setPeso(20);
        return true;
    }
}

void Canguru::dies(Reserva *r, int id) {
    if (VCanguru == 0) {
        Alimento *p = new Corpo(r, getPosX()+1, getPosY(), 15, 5);
        r->pushBackVectorAlimentos(p);
        r->removeAnimalFromVector(id);
        delete r->getAnimalById(r,id);
    }
}

Animal* Canguru::fazOutro(Reserva *r) {
    if ((Animal::getTick() == 30) == 0) {
        Animal* p = new Canguru(r);
        r->pushBackVectorAnimais(p);
        Local *a = new Local(Reserva::contPosOcupadas, p->getPosX(), p->getPosY(), "animal",'G', r);
        r->pushBackVectorPosOcupadas(a);
        Reserva::contPosOcupadas++;
        Reserva::contAnimais++;
        int aux1=rand() % 7 - 3;
        int aux2=rand() % 7 - 3;
        p->setPosX(aux1);
        p->setPosY(aux2);
        p->setpaiID(getAnimalID());
        p->setPeso(10);
        return p;
    }
    return nullptr;
}

void Canguru::move(Reserva *r, int paiID, int medo) {

    Animal *pai = r->getAnimalById(r,paiID);
    // fabs = valor absoluto da distancia entre os dois animais.
    if (fabs (pai->getPosX() - getPosX()) >= 5 ) {
        if (getPosX() < pai->getPosX()) {
            setPosX(getPosX()+1 * medo);
            return;
        }
        if (getPosX() > pai->getPosX()) {
            setPosX(getPosX()-1 * medo);
            return;
        }
    }

    if (fabs (pai->getPosY() - getPosY()) >= 5 ) {
        if (getPosY() < pai->getPosY()) {
            setPosY(getPosY()+1 * medo);
            return;
        }
        if (getPosY() > pai->getPosY()) {
            setPosY(getPosY()-1 * medo);
            return;
        }
    }
}

int Canguru::getTickMarsupial() { return this-> tickMarsupial;}
void Canguru::setTickMarsupial(int a) { tickMarsupial = a;}

bool Canguru::bolsaMarsupial(Reserva *r, int paiID) {
    Animal *pai = r->getAnimalById(r,paiID);

    if (getTickMarsupial() == 5) {
        // sai  da bolsa marsupial a duas posiçoes de distancia, de forma a que
        // o filho nao fique continuamente preso ao pai
        setPosX(getPosX() + 2);
        return false;
    }
    else {
        setPosX(pai->getPosX());
        setPosY(pai->getPosY());
        setTickMarsupial(getTickMarsupial()+1);
        return true;
    }



}

void Canguru::checkSurroundings(Reserva *r, Local *l, int x, int y, int radius, int paiID) {

    Animal *pai = r->getAnimalById(r,paiID);

    for (int i = x-radius; i < x+radius+1; i++) {
        for (int j = y+radius; i > j-radius-1; j--) {
            if ( i == x && j == y ) {
                if (pai->getPosX() == i && pai->getPosY() == j) {
                    // salta para a bolsa marsupial
                    bolsaMarsupial(r, paiID);
                    return;
                }
            }

            // se estiver no range
            if (l->getLocalX() == j && l->getLocalY() == i){
                if (l->getTipoOcupante() == "animal" && l->getOcupaId() != paiID) {
                    // se está a uma posiçao do pai, vai para a sua posiçao
                    for (int a = x-1; a < x+2; a++) {
                        for (int b = y + 1; b > y - 2; b--) {
                            if (a == x && b == y)
                                continue;
                            if ((l->getLocalX() == a && l->getLocalY() == b)) {
                                move(r, paiID, 1);
                                return;
                            }
                            else {
                                //corre para o pai
                                move(r, paiID, 2);
                                return;
                            }
                        }
                    }
                }
            }
            // se nao encontrou nada na ultima iteraçao:
            if (i == y-radius+1 && j == x+radius-1) {
                Animal::moveRand(getdeslMin(), getdeslMax());
                return;
            }

        }
    }
}

Canguru::~Canguru() {

    cout << "Canguru Destruido!\n";
};