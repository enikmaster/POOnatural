#ifndef TESTETP_OVELHA_H
#define TESTETP_OVELHA_H
#include "../Inc.h"
#include "Animal.h"

class Ovelha : public Animal {
private:
    int SOvelha;
    int VOvelha;
    int percepcao;

public:
    Ovelha();
    ~Ovelha();

    void fomeca();
    void repro();

};


#endif //TESTETP_OVELHA_H
