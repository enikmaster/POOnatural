#include "Reserva.h"
#include "../Animais/Animal.h"
#include "../Alimentos/Alimento.h"
#include "Local.h"
using namespace std;
template<class T> class DeleteVector {
public:
    // Overloaded () operator.
    // This will be called by for_each() function.
    bool operator()(T x) const {
        // Delete pointer.
        delete x;
        return true;
    }
};
int Reserva::contadorIds = 0;
Reserva::Reserva(int largura, int altura) : dimX(largura), dimY(altura), origemVisX(0), origemVisY(0) {

}
Reserva::Reserva(const Reserva& outra) : Reserva(outra.getDimX(), outra.getDimY()) {};
// getters
string Reserva::getAsString() const {
    ostringstream os;
    os << getDimX() << "x" << getDimY() << endl;
    return os.str();
}
Animal* Reserva::getAnimal(int id) {
    for(auto& animal : animais) {
        if(animal->getAnimalId() == id ) {
            Animal* animalPerto = animal;
            return animalPerto;
        }
    }
    return nullptr;
};
Alimento* Reserva::getAlimento(int id) {
    for(auto& alimento : alimentos) {
        if(alimento->getFoodId() == id) {
            Alimento* alimentoPerto = alimento;
            return alimentoPerto;
        }
    }
    return nullptr;
};
// setters
void Reserva::setOrigemVisX(int newX) {
    /*if((origemVisX + newX*2) > getDimX()*2) {
        origemVisX = getDimX()*2 - 32;
    }
    if((origemVisX - newX*2) <= 0) {
        origemVisX = 0;
    }
    if(origemVisX + newX*2 <= getDimX() && origemVisX - newX*2 > 0) {
        origemVisX = newX*2;
    }*/
    origemVisX = newX*2;
}
void Reserva::setOrigemVisY(int newY) {
    origemVisY = newY*2;
}
// actions
bool Reserva::checkIdExist(int arg) const {
    if(arg <= getContadorIds()) {
        for (auto &it: locaisOcupados) {
            if (arg == it->getOcupaId())
                return true;
        }
    }
    return false;
}
bool Reserva::checkIdAlimentos(int arg) const {
    if(!alimentos.empty()) {
        for(auto& alimento : alimentos) {
            if(alimento->getFoodId() == arg)
                return true;
        }
    }
    return false;
}
bool Reserva::checkIdAnimais(int arg) const {
    if(!animais.empty()) {
        for(auto& animal : animais) {
            if(animal->getAnimalId() == arg)
                return true;
        }
    }
    return false;
}
bool Reserva::checkPosOcupado(int posX, int posY) const {
    if(!locaisOcupados.empty()) {
        for (auto& local: locaisOcupados) {
            if (local->getLocalX() == posX && local->getLocalY() == posY)
                return true;
        }
    }
    return false;
}
void Reserva::checkWithinRange(int elX, int elY, int percepcao, vector<int>& idAnimais, vector<int>& idAlimentos) const {
    for(auto& local : locaisOcupados) {
        if(local->getLocalX() < elX - percepcao || local->getLocalX() > elX + percepcao)
            continue;
        if(local->getLocalY() < elY - percepcao || local->getLocalY() > elY + percepcao)
            continue;
        (std::isupper(local->getTipoOcupante())) ? idAnimais.push_back(local->getOcupaId()) : idAlimentos.push_back(local->getOcupaId());
    }
}
void Reserva::addFood(Alimento* alimento) {
    alimento->setReserva(this);
    alimentos.push_back(alimento);
}
void Reserva::removeFood(int fid) {
    for(vector<Alimento*>::iterator alimento = alimentos.begin(); alimento != alimentos.end(); ++alimento){
        if((*alimento)->getFoodId() == fid) {
            removeLocal(fid);
            delete *alimento;
            alimentos.erase(alimento);
            return;
        }
    }
}
void Reserva::removeFood(int posX, int posY) {
    for(vector<Alimento*>::iterator alimento = alimentos.begin(); alimento != alimentos.end(); ++alimento){
        if((*alimento)->getPosX() == posX && (*alimento)->getPosY() == posY) {
            removeLocal((*alimento)->getFoodId());
            delete *alimento;
            alimentos.erase(alimento);
            return;
        }
    }
}
void Reserva::addAnimal(Animal* animal) {
    animal->setReserva(this); // dúvida!!!!
    animais.push_back(animal);
}
void Reserva::removeAnimal(int aid) {
    for(vector<Animal*>::iterator animal = animais.begin(); animal != animais.end(); ++animal) {
        if((*animal)->getAnimalId() == aid) {
            removeLocal(aid);
            delete *animal;
            animais.erase(animal);
            return;
        }
    }
}
bool Reserva::removeAnimal(int posX, int posY) {
    for(vector<Animal*>::iterator animal = animais.begin(); animal != animais.end(); ++animal) {
        if((*animal)->getPosY() == posX && (*animal)->getPosY() == posY) {
            removeLocal((*animal)->getAnimalId());
            delete *animal;
            animais.erase(animal);
            return true;
        }
    }
    return false;
}
void Reserva::addLocal(Local* local) {
    local->setReserva(this);
    locaisOcupados.push_back(local);
}
bool Reserva::removeLocal(int lid) {
    for(vector<Local*>::iterator local = locaisOcupados.begin(); local != locaisOcupados.end(); ++local ) {
        if((*local)->getOcupaId() == lid) {
            delete *local;
            locaisOcupados.erase(local);
            return true;
        }
    }
    return false;
}
void Reserva::updateLocal() {
    for(auto* local : locaisOcupados) {
        if(std::isupper(local->getTipoOcupante())) {
            for(auto* animal : animais) {
                if(animal->getAnimalId() == local->getOcupaId()) {
                    local->setLocalX(animal->getPosX());
                    local->setLocalY(animal->getPosY());
                }
            }
        } else {
            for(auto* animal : animais) {
                if(animal->getAnimalId() == local->getOcupaId()) {
                    local->setLocalX(animal->getPosX());
                    local->setLocalY(animal->getPosY());
                }
            }
        }
    }
}
void Reserva::limpaMortos() {
    for(vector<Animal*>::iterator animal = animais.begin(); animal != animais.end(); ++animal) {
        if(!(*animal)->getIsAlive()) {
            removeLocal((*animal)->getAnimalId());
            delete *animal;
            animais.erase(animal);
        }
    }
   // for(vector<Alimento*>::iterator alimento = alimentos.begin(); alimento != alimentos.end(); ++animal)
}
void Reserva::deleteAll() {
    for_each(animais.begin(), animais.end(), DeleteVector<Animal*>() );
    for_each(alimentos.begin(), alimentos.end(), DeleteVector<Alimento*>());
    for_each(locaisOcupados.begin(), locaisOcupados.end(), DeleteVector<Local*>());
    animais.clear();
    alimentos.clear();
    locaisOcupados.clear();
}
void Reserva::alimentar(int aid, int nutri, int tox) {

}
