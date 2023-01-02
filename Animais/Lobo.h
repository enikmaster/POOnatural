#ifndef TESTETP_LOBO_H
#define TESTETP_LOBO_H
#include "../Inc.h"
#include "Animal.h"
#include "../Reserva.h"

//class Local;
class Lobo : public Animal{
private:
    int SLobo;
    int VLobo;
    bool pariu;
    int velo;
    int posPaiX;
    int posPaiY;
    Reserva *reserva;

public:
    Lobo(Reserva *reserva);
    ~Lobo();

    void fomeca();
    Animal* fazOutro(Reserva *obj, int id);
    void dies(Reserva *a, int id);
    void checkSurroundings(Reserva *r, Local *l, int x, int y, int radius, int id);
    void move(int xTarget, int yTarget, const string& tipoDeAlvo);

};


#endif //TESTETP_LOBO_H
