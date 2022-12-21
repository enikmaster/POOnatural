#ifndef TESTETP_CANGURU_H
#define TESTETP_CANGURU_H
#include "../Inc.h"
#include "Animal.h"

class Canguru : public Animal{
private:
    int SCanguru;
    int VCanguru;

public:
    Canguru();
    ~Canguru();

    void repro();
    bool isAdulto();
};


#endif //TESTETP_CANGURU_H
