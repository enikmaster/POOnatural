#ifndef TESTETP_RELVA_H
#define TESTETP_RELVA_H
#include "../Inc.h"
#include "Alimento.h"

class Relva : public Alimento{
private:
    int VRelva;

public:
    Relva();
    ~Relva();

    int getVRelva();
    void setVRelva(int a);

    // methods
    void spawn();
};



#endif //TESTETP_RELVA_H
