#include "Lobo.h"
#include "../Reserva.h"
#include "../Alimentos/Alimento.h"
#include "../Alimentos/Corpo.h"
#include "../Local.h"



Lobo::Lobo(Reserva *reserva) : SLobo(25), VLobo(40), velo(1){
    cout << "######## LOBO ##########\n";
    Animal::setdeslMin(1);
    Animal::setdeslMax(1);
    Animal::setPercepcao(5);
    Animal::setLetra('L');
    Animal::setAnimalID(Reserva::contAnimais);
    Reserva::contAnimais++;
    cout << "SLobo: " <<  SLobo << "\t" << "Percepcao: "<< Animal::getPercepcao() << endl;
    Animal::checkSurroundings(Animal::getPosX(), Animal::getPosY(), Animal::getPercepcao());
    Animal::setPeso(15);
    Lobo::dies(reserva, 1);
}

void Lobo::fomeca() { // vai ser chamada a cada tick
    // Incrementa por cada tick
    int fome = Animal::getFome();
    Animal::setFome(fome + 2);

    if (fome > 25){
        SLobo -= 2;
        velo = 2;
    }
    if (fome > 15 && fome <= 25) {
        SLobo--;
        velo = 2;
    }
}

void Lobo::dies(Reserva *r, int id) {
    if (VLobo == 0) {
        // quando morre, deixa ao seu lado um Corpo
        Alimento *p = new Corpo(r, getPosX()+1, getPosY(), 10, 0);
        r->pushBackVectorAlimentos(p);
        Reserva::contAlimentos++;
        Local *a = new Local(Reserva::contPosOcupadas, p->getPosX(), p->getPosY(), "animal",'l', r);
        Reserva::contPosOcupadas++;
        r->pushBackVectorPosOcupadas(a);
        cout << "Xau lobo!\n";
        r->removeAnimalFromVector(id);
        delete r->getAnimalById(r,id);
    }
}

void Lobo::checkSurroundings(Reserva *r, Local *l, int x, int y, int radius, int id) {

    int lenTotal = ((radius * 2) + 1) * 2;
    Animal* esteLobo = r->getAnimalById(r, id);

    for (int i = x-radius; i < x+radius+1; i++) {
        for (int j = y+radius; i > j-radius-1; j--) {
            if ( i == x && j == y ) {
                // na mesma pos:
                if (l->getLocalX() == x && l->getLocalY() == y){
                    // se estiver na pos de um alimento:
                    if (l->getSiglaOcupante() == 'p' || l->getSiglaOcupante() == 'b') {
                        Alimento* alvo = r->getAlimentoById(r, l->getOcupaId());
                        Animal::setFome( alvo->getNutri() );
                        r->removeAlimentoFromVector(l->getOcupaId());
                        r->removePosFromVector(l->getOcupaId());
                        delete alvo;
                        return;
                    }
                    // se estiver na pos de outro animal:
                    if (l->getTipoOcupante() == "animal") {
                        Animal* alvo = r->getAnimalById(r, l->getOcupaId());
                        if (alvo->getPeso() < getPeso()){
                            r->removeAnimalFromVector(l->getOcupaId());
                            r->removePosFromVector(l->getOcupaId());
                            delete alvo;
                            return;
                        }
                        else { //o outro animal é maior e vao lutar
                            int w = rand() % 2 + 1;
                            switch (w) {
                                case (1):
                                    r->removeAnimalFromVector(l->getOcupaId());
                                    r->removePosFromVector(l->getOcupaId());
                                    delete alvo;
                                case (2):
                                    r->removeAnimalFromVector(l->getOcupaId());
                                    r->removePosFromVector(l->getOcupaId());
                                    delete esteLobo;
                            }
                            return;
                        }
                    }
                }
            }
            //se estiver a uma ou duas posicoes de distancia do alvo:
            for (int a2 = 1, b2 = 2; a2 < 3; a2++, b2++) {
                // verificar a 1 de distancia e a 2 de distancia
                // (Porquê? porque o lobo esta a correr de 3 em 3 unidades quando cheira carne).
                for (int a = x-a2; a < x+b2; a++) {
                    for (int b = y+a2; b > y-b2; b--) {
                        if ( a == x && b == y )
                            continue;
                        if (l->getLocalX() == a && l->getLocalY() == b) {
                            if (a2 == 1 && getFome() > 15) {
                                // se estiver a uma posicao de distancia do alimento
                                if (l->getSiglaOcupante() == 'p' || l->getSiglaOcupante() == 'b') {
                                    Alimento* alvo = r->getAlimentoById(r, l->getOcupaId());
                                    Animal::setFome( alvo->getNutri() );
                                    r->removeAlimentoFromVector(l->getOcupaId());
                                    r->removePosFromVector(l->getOcupaId());
                                    delete alvo;
                                    Lobo::setPosX(l->getLocalX());
                                    Lobo::setPosY(l->getLocalY());
                                    return;
                                }
                                if (l->getTipoOcupante() == "animal") {
                                    if (l->getSiglaOcupante() == 'G')
                                        continue;
                                    Animal* alvo = r->getAnimalById(r,l->getOcupaId());
                                    r->removeAnimalFromVector(l->getOcupaId());
                                    r->removePosFromVector(l->getOcupaId());
                                    delete alvo;
                                    Alimento *n = new Corpo(r, l->getLocalX()+1, l->getLocalY(), 10, 0);
                                    r->pushBackVectorAlimentos(n);
                                    Reserva::contAlimentos++;
                                    Local *c = new Local(Reserva::contPosOcupadas, l->getLocalX()+1, l->getLocalY(), "alimento",'p', r);
                                    Reserva::contPosOcupadas++;
                                    r->pushBackVectorPosOcupadas(c);

                                    Lobo::setPosX(l->getLocalX());
                                    Lobo::setPosY(l->getLocalY());
                                    return;
                                }
                            }
                            if (a2 == 2 && getFome() > 15){
                                // se está a 2 posiçoes de distancia e tem fome >15
                                if (l->getTipoOcupante() == "animal") {
                                    if (l->getSiglaOcupante() == 'G')
                                        continue;
                                    Animal* alvo = r->getAnimalById(r,l->getOcupaId());
                                    r->removeAnimalFromVector(l->getOcupaId());
                                    r->removePosFromVector(l->getOcupaId());
                                    delete alvo;
                                    Alimento *n = new Corpo(r, l->getLocalX()+1, l->getLocalY(), 10, 0);
                                    r->pushBackVectorAlimentos(n);
                                    Reserva::contAlimentos++;
                                    Local *c = new Local(Reserva::contPosOcupadas, l->getLocalX()+1, l->getLocalY(), "alimento",'p', r);
                                    Reserva::contPosOcupadas++;
                                    r->pushBackVectorPosOcupadas(c);

                                    Lobo::setPosX(l->getLocalX());
                                    Lobo::setPosY(l->getLocalY());
                                    return;
                                }
                            }

                        }
                    }
                }
            }

            // se estiver no range, mas nao na mesma pos que o lobo:
            if (l->getLocalX() == j && l->getLocalY() == i){
                if (l->getTipoOcupante() == "alimento") {
                    move( l->getLocalX(), l->getLocalY(), "alimento");
                    return;
                } else { // continua o ciclo for, perguntando pelo maior peso,
                        // isto é possivel porque o objetivo é dar return no fim.
                        int maior=0;
                    for (int i2 = i; i2 > y-radius; i2--) {
                        for (int j2 = j; j2 < x+radius; j2++) {
                            if ( r->getAnimalById(r, l->getOcupaId())->getPeso() > maior)
                                maior = r->getAnimalById(r, l->getOcupaId())->getPeso();
                        }
                    }
                    move(r->getAnimalById(r, l->getOcupaId())->getPosX(), r->getAnimalById(r, l->getOcupaId())->getPosY(), "animal" );
                    return;
                }

            }
            // se estiver na ultima iteraçao do ciclo e nao encontrar nada:
            if (i == y-radius+1 && j == x+radius-1)
                moveRand(Animal::getdeslMin(), Animal::getdeslMax());
        }
    }
}

Animal* Lobo::fazOutro(Reserva *r, int id) {
    int randVal = Animal::aleatorio(1, 30);
    //if randVal = 30;
    if (randVal == 2) {
        pariu = true;
        // criar os objetos  + mete-los nos vetores
        Animal *p = new Lobo(r);
        r->pushBackVectorAnimais(p);
        Reserva::contAnimais++;
        Local *a = new Local(Reserva::contPosOcupadas, p->getPosX(), p->getPosY(), "animal", 'l', r);
        Reserva::contPosOcupadas++;
        r->pushBackVectorPosOcupadas(a);
        p->setPosX((rand() % 31 + -15));
        p->setPosY((rand() % 31 + -15));
        r->printListaAnimais();


        // procura pelo pai por animalID na reserva e obtem as suas coords
        // recebe-as e novoLobo::getPosX - rand(1-15) e getPosT - rand(1-15)
        return p;
    }
}
void Lobo::move(int xTarget, int yTarget, const string& tipoDeAlvo) {

    if (Animal::getFome() > 15 && tipoDeAlvo == "animal")
        velo = 3;

    if (getPosX() < xTarget) {
        setPosX(getPosX()+1 * velo);
        return;
    }
    if (getPosX() > xTarget) {
        setPosX(getPosX()-1 * velo);
        return;
    }
    if (getPosY() < yTarget) {
        setPosY(getPosY()+1 * velo);
        return;
    }
    if (getPosY() > yTarget) {
        setPosY(getPosY()-1 * velo);
        return;
    }
}


Lobo::~Lobo() {
    cout << "\nLobo Destruido!\n";
}