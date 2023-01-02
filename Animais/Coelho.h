#ifndef TESTETP_COELHO_H
#define TESTETP_COELHO_H

#include "../Inc.h"
#include "Animal.h"
#include "../Reserva.h"


class Coelho : public Animal {
private:
    int SCoelho;
    int VCoelho;

public:
    Coelho(Reserva *reserva);
    ~Coelho();

    void fomeca();
    void dies(Reserva *r, int id);
    Animal* fazOutro(Reserva *r);
    void checkSurroundings(Reserva *r, Local *l, int x, int y, int radius, int id);
    void move(int xTarget, int yTarget, int flag);

};


#endif //TESTETP_COELHO_H
