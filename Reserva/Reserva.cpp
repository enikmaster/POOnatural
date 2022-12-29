#include "Reserva.h"
#include "../Animais/Animal.h"
#include "../Alimentos/Alimento.h"
#include "Local.h"
using namespace std;
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
    for(auto& itr: alimentos){
        if(itr->getFoodId() == fid) {
            removeLocal(fid);
            delete itr;
            return;
        }
    }
}
void Reserva::removeFood(int posX, int posY) {
    for(auto& itr: alimentos){
        if(itr->getPosX() == posX && itr->getPosY() == posY) {
            removeLocal(itr->getFoodId());
            delete itr;
            return;
        }
    }
}
void Reserva::addAnimal(Animal* animal) {
    animal->setReserva(this);
    animais.push_back(animal);
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
    for(vector<Animal*>::iterator itr = animais.begin(); itr != animais.end();)
        animais.erase(itr);
    for(vector<Alimento*>::iterator itr = alimentos.begin(); itr != alimentos.end();)
        alimentos.erase(itr);
    for(vector<Local*>::iterator itr = locaisOcupados.begin(); itr != locaisOcupados.end();)
        locaisOcupados.erase(itr);
//    for(auto itr = saves.begin(); itr != saves.end();)
//        saves.erase(itr);
}