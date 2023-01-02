#include "Coelho.h"
#include "../Reserva/Reserva.h"

Coelho::Coelho(Reserva *r) : SCoelho(20), VCoelho(30) {
    setSaude(sOvelha);
    setIdade(0);
    setdeslMin(1);
    setdeslMax(1);
    setPercepcao(3);
    escolhePeso(4, 8);
    setAlimentacao("erva");
    populateWithinRange();

    cout << "######## COELHO ##########\n";
    Animal::setdeslMin(1);
    Animal::setdeslMax(2);
    Animal::setPercepcao(4);
    cout << "SCoelho: " <<  SCoelho << "\t" << "Percepcao: "<< Animal::getPercepcao() << endl;
    //Coelho::checkSurroundings(r, Animal::getPosX(), Animal::getPosY(), Animal::getPercepcao(), Animal::getAnimalID());
    cout << "X: " << Animal::getPosX() << "\t"<<"Y: " << Animal::getPosY() << endl;
    Animal::escolhePeso(1,4);
    cout << "Peso: " << getPeso();
    Coelho::dies(r, getAnimalID());

}

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
}

Coelho::~Coelho() { cout << "Coelho Destruido!\n";}