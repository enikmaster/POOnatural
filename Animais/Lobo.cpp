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
        // atualiza a população Within Range de acordo com a nova posição
        populateWithinRange();
    }
    if(!getIsAlive())
        dies();
    reservaAnimal->updateLocal(getAnimalId(), getPosX(), getPosY());
}

/*
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
}*/