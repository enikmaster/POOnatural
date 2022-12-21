#ifndef TESTETP_COELHO_H
#define TESTETP_COELHO_H

#include "../Inc.h"
#include "Animal.h"


class Coelho : public Animal {
private:
    int SCoelho;
    int VCoelho;

public:
    Coelho();
    ~Coelho();

    void fomeca();
    void repro();

};


#endif //TESTETP_COELHO_H
