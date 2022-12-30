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
// getters
string Reserva::getAsString() const {
    ostringstream os;
    os << getDimX() << "x" << getDimY() << endl;
    return os.str();
}
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
    if(arg > getContadorIds())
        return false;
    for(auto& it : locaisOcupados) {
        if(arg == it->getOcupaId())
            return true;
    }
    return false;
}
bool Reserva::checkIdAlimentos(int arg) const {
    return false;
}
bool Reserva::checkIdAnimais(int arg) const {
    return false;
}
bool Reserva::checkPosXOcupado(int posX) const {
    if(locaisOcupados.size() == 0)
        return false;
    for(auto& it : locaisOcupados){
        if(it->getLocalX() == posX)
            return true;
    }
    return false;
}
bool Reserva::checkPosYOcupado(int posY) const {
    if(locaisOcupados.size() == 0)
        return false;
    for(auto& it : locaisOcupados) {
        if(it->getLocalY() == posY)
            return true;
    }
    return false;
}
void Reserva::addFood(Alimento* alimento) {
    alimento->setReserva(this);
    alimentos.push_back(alimento);
}
void Reserva::removeFood(int fid) {
    for(auto& alimento: alimentos){
        if(alimento->getFoodId() == fid) {
            removeLocal(fid);
            delete alimento;
            return;
        }
    }
}
void Reserva::removeFood(int posX, int posY) {
    for(auto& alimento: alimentos){
        if(alimento->getPosX() == posX && alimento->getPosY() == posY) {
            removeLocal(alimento->getFoodId());
            delete alimento;
            return;
        }
    }
}
void Reserva::addAnimal(Animal* animal) {
    animal->setReserva(this);
    animais.push_back(animal);
}
void Reserva::removeAnimal(int aid) {
    for(auto& animal : animais) {
        if(animal->getAnimalId() == aid) {
            removeLocal(aid);
            delete animal;
            return;
        }
    }
}
bool Reserva::removeAnimal(int posX, int posY) {
    for(vector<Animal*>::iterator animal = animais.begin(); animal != animais.end();) {
        if((*animal)->getPosY() == posX && (*animal)->getPosY() == posY) {
            removeLocal((*animal)->getAnimalId());
            delete (*animal);
            animais.erase(animal);
            return true;
        }
    }
    // dúvida aqui
    // depois de decobrir, repetir para os outros REMOVES
    for(auto& animal : animais) {
        if(animal->getPosX() == posX && animal->getPosY() == posY) {
            removeLocal(animal->getAnimalId());
            delete animal;
            // adicionar um alimento neste local?
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
    for(auto& itr : locaisOcupados) {
        if(itr->getOcupaId() == lid) {
            delete itr;
            return true;
        }
    }
    return false;
}
void Reserva::deleteAll() {
    for_each(animais.begin(), animais.end(), DeleteVector<Animal*>());
    for_each(alimentos.begin(), alimentos.end(), DeleteVector<Alimento*>());
    for_each(locaisOcupados.begin(), locaisOcupados.end(), DeleteVector<Local*>());
/*  com erase(), o destutor não é chamado.
    for(vector<Animal*>::iterator animal = animais.begin(); animal != animais.end();)
        animais.erase(animal);
    for(vector<Alimento*>::iterator alimento = alimentos.begin(); alimento != alimentos.end();)
        alimentos.erase(alimento);
    for(vector<Local*>::iterator local = locaisOcupados.begin(); local != locaisOcupados.end();)
        locaisOcupados.erase(local);
        */
    animais.clear();
    alimentos.clear();
    locaisOcupados.clear();
}