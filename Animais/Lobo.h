#ifndef TESTETP_LOBO_H
#define TESTETP_LOBO_H
#include "../Inc.h"
#include "Animal.h"

class Lobo : public Animal{
private:
    int SLobo;
    int VLobo;
    int percepcao;
    bool pariu;

public:
    Lobo();
    ~Lobo();

    void fomeca();
    void repro();
};


#endif //TESTETP_LOBO_H
