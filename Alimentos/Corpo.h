#ifndef TESTETP_CORPO_H
#define TESTETP_CORPO_H
#include "../Inc.h"
#include "Alimento.h"
#include "../Animais/Animal.h"

class Corpo : public Alimento{
public:
    Corpo(int x, int y, int nutri);
    ~Corpo();

    // methods
    void podridao(int nutri);

};


#endif //TESTETP_CORPO_H
