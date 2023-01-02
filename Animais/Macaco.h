#ifndef TESTETP_MACACO_H
#define TESTETP_MACACO_H
#include "../Inc.h"
#include "Animal.h"

class Macaco {
private:
    int SMacaco;
    int VMacaco;
    int contadorXp;

public:
    Macaco();
    ~Macaco();

    void xpGain();
    Animal* fazOutro();
};


#endif //TESTETP_MACACO_H
