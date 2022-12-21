#include "Corpo.h"

Corpo::Corpo(int x, int y, int nutri) {
    Alimento::setLetra('p');
    Alimento::setPosX(x);
    Alimento::setPosY(y);
    Alimento::setNutri(nutri);
    Alimento::setCheiro1("carne");
};

void Corpo::podridao(int nutri) {
    // corre sempre uma vez por cada tick global
    if (getTick() < 2 * nutri)
        setToxic(getToxic() + 1);
    setNutri(getNutri() - 1);
}

Corpo::~Corpo() {};