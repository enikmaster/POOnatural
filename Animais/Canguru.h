#ifndef TESTETP_CANGURU_H
#define TESTETP_CANGURU_H
#include "../Inc.h"
#include "Animal.h"
#include "../Reserva.h"

class Canguru : public Animal{
private:
    int SCanguru;
    int VCanguru;
    int tickMarsupial;

public:
    Canguru(Reserva *reserva);
    ~Canguru();


    int getTickMarsupial();
    void setTickMarsupial(int a);
    void checkSurroundings(Reserva *r, Local *l, int x, int y, int radius, int paiID);
    void move(Reserva *r,int paiID, int medo);
    bool isAdulto();
    void dies(Reserva *r, int id);
    Animal* fazOutro(Reserva *r);
    bool bolsaMarsupial(Reserva *r, int paiID);
};


#endif //TESTETP_CANGURU_H
