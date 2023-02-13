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
int Reserva::contadorIds {0};
Reserva::Reserva(int largura, int altura) : dimX(largura), dimY(altura) {};
Reserva::Reserva(const Reserva& outra) : Reserva(outra.getDimX(), outra.getDimY()) {
    for(auto alimento(outra.alimentos.begin()); alimento != outra.alimentos.end(); ++alimento) {
        Alimento* pAl = (*alimento)->clone();
        pAl->setReserva(this);
        this->alimentos.push_back(pAl);
    }
    for(auto animal(outra.animais.begin()); animal != outra.animais.end(); ++animal) {
        Animal* pAnim = (*animal)->clone();
        pAnim->setReserva(this);
        this->animais.push_back(pAnim);
    }
    for(auto local{outra.locaisOcupados.begin()}; local != outra.locaisOcupados.end(); ++local) {
        Local* pLocal = (*local)->clone();
        pLocal->setReserva(this);
        this->locaisOcupados.push_back(pLocal);
    }
};
Reserva::~Reserva() {
    this->deleteAll();
}
// getters
string Reserva::getAsString() const {
    ostringstream os;
    os << getDimX() << "x" << getDimY() << endl;
    return os.str();
}
Animal* Reserva::getAnimal(int id) {
    for(auto& animal : animais) {
        if(animal->getAnimalId() == id ) {
            Animal* animalPerto {animal};
            return animalPerto;
        }
    }
    return nullptr;
};
Alimento* Reserva::getAlimento(int id) {
    for(auto& alimento : alimentos) {
        if(alimento->getFoodId() == id) {
            Alimento* alimentoPerto {alimento};
            return alimentoPerto;
        }
    }
    return nullptr;
};
// setters
void Reserva::setToEmptyByPos(int posX, int posY) {
    for(auto& animal : animais) {
        if(animal->getPosX() == posX && animal->getPosY() == posY)
            animal->setToEmpty(false);
    }
}
// actions
bool Reserva::checkPosOcupado(int posX, int posY) const {
    // verifica se a posição x,y está ocupada
    if(!locaisOcupados.empty()) {
        for (auto& local : locaisOcupados) {
            if (local->getLocalX() == posX && local->getLocalY() == posY)
                return true;
        }
    }
    return false;
}
void Reserva::checkWithinRange(int elX, int elY, int percepcao, vector<int>& idAnimais, vector<int>& idAlimentos) const {
    // cria um lista de locais ocupados por ID e tipo
    for(auto& local : locaisOcupados) {
        if(local->getLocalX() < elX - percepcao || local->getLocalX() > elX + percepcao)
            continue;
        if(local->getLocalY() < elY - percepcao || local->getLocalY() > elY + percepcao)
            continue;
        (std::isupper(local->getTipoOcupante())) ? idAnimais.push_back(local->getOcupaId()) : idAlimentos.push_back(local->getOcupaId());
    }
}
void Reserva::addFood(Alimento* alimento) {
    // adiciona um ponteiro alimento à lista de alimentos da reserva
    alimento->setReserva(this);
    alimentos.push_back(alimento);
}
void Reserva::removeFood(int fid) {
    // remove um alimento da reserva por id
    for(vector<Alimento*>::iterator alimento {alimentos.begin()}; alimento != alimentos.end(); ++alimento){
        if((*alimento)->getFoodId() == fid) {
            // remove o local que o alimento ocupa
            removeLocal(fid);
            delete *alimento;
            alimentos.erase(alimento);
            return;
        }
    }
}
void Reserva::removeFood(int posX, int posY) {
    // remove um alimento da reserva por posição
    for(vector<Alimento*>::iterator alimento {alimentos.begin()}; alimento != alimentos.end(); ++alimento){
        if((*alimento)->getPosX() == posX && (*alimento)->getPosY() == posY) {
            // remove o local que o alimento ocupa
            removeLocal((*alimento)->getFoodId());
            delete *alimento;
            alimentos.erase(alimento);
            return;
        }
    }
}
void Reserva::addAnimal(Animal* animal) {
    // adiciona um ponteiro animal à lista de animais da reserva
    animal->setReserva(this);
    animais.push_back(animal);
}
void Reserva::removeAnimal(int aid) {
    // remove um animal da reserva por id
    for(vector<Animal*>::iterator animal{animais.begin()}; animal != animais.end(); ++animal) {
        if((*animal)->getAnimalId() == aid) {
            // remove o local que o animal ocupa
            removeLocal(aid);
            delete *animal;
            animais.erase(animal);
            return;
        }
    }
}
bool Reserva::removeAnimal(int posX, int posY) {
    // remove um animal da reserva por posição
    for(vector<Animal*>::iterator animal {animais.begin()}; animal != animais.end(); ++animal) {
        if((*animal)->getPosX() == posX && (*animal)->getPosY() == posY) {
            // remove o local que o animal ocupa
            removeLocal((*animal)->getAnimalId());
            delete *animal;
            animais.erase(animal);
            return true;
        }
    }
    return false;
}
void Reserva::addLocal(Local* local) {
    // adiciona um novo local ocupado
    local->setReserva(this);
    locaisOcupados.push_back(local);
}
bool Reserva::removeLocal(int lid) {
    // remove um local ocupado
    for(vector<Local*>::iterator local {locaisOcupados.begin()}; local != locaisOcupados.end(); ++local ) {
        if((*local)->getOcupaId() == lid) {
            delete *local;
            locaisOcupados.erase(local);
            return true;
        }
    }
    return false;
}
void Reserva::updateLocal(int id, int posX, int posY) {
    // atualiza a posição de um local ocupado
    for(vector<Local*>::iterator local {locaisOcupados.begin()}; local != locaisOcupados.end(); ++local) {
        if((*local)->getOcupaId() == id) {
            (*local)->setLocalX(posX);
            (*local)->setLocalY(posY);
        }
    }
}
void Reserva::limpaMortos() {
    // remove os animais e alimentos da reserva
    for(vector<Animal*>::iterator animal {animais.begin()}; animal != animais.end(); ++animal) {
        if(!(*animal)->getIsAlive()) {
            removeLocal((*animal)->getAnimalId());
            delete *animal;
            animais.erase(animal);
            --animal;
        }
    }
    for(vector<Alimento*>::iterator alimento {alimentos.begin()}; alimento != alimentos.end(); ++alimento) {
        if(!(*alimento)->getIsAlive()) {
            removeLocal((*alimento)->getFoodId());
            delete *alimento;
            alimentos.erase(alimento);
            --alimento;
        }
    }
}
void Reserva::deleteAll() {
    // liberta todos os elementos da reserva
    for_each(animais.begin(), animais.end(), DeleteVector<Animal*>() );
    for_each(alimentos.begin(), alimentos.end(), DeleteVector<Alimento*>());
    for_each(locaisOcupados.begin(), locaisOcupados.end(), DeleteVector<Local*>());
    animais.clear();
    alimentos.clear();
    locaisOcupados.clear();
}
void Reserva::alimentar(int aid, int nutri, int tox) {
    // alimenta um animal da reserva por id
    for (auto& animal: animais) {
        if ((*animal).getAnimalId() == aid) {
            (*animal).setSaude( (*animal).getSaude() + nutri - tox );
        }
    }
}
void Reserva::alimentarPorXY(int x, int y, int nutri, int tox) {
    // alimenta um animal da reserva por coords
        for (auto& animal: animais) {
            if ((*animal).getPosX() == x && (*animal).getPosY() == y) {
                (*animal).setSaude( (*animal).getSaude() + nutri - tox );
            }
        }
}
