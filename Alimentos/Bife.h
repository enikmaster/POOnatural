#ifndef TESTETP_BIFE_H
#define TESTETP_BIFE_H
#include "../Includes.h"
#include "Alimento.h"

class Bife : public Alimento {
private:

public:
    Bife();
    ~Bife();

    // methods
    void podridao();
};


#endif //TESTETP_BIFE_H
