#ifndef TESTETP_RELVA_H
#define TESTETP_RELVA_H
#include "../Includes.h"
#include "Alimento.h"

class Relva : public Alimento{
public:
    Relva(string l, int x, int y, Reserva* zoo);
    Relva(string& l, Reserva* zoo);
    ~Relva();

    //int get() const {return this->getDuracao();};

    // methods
    //Alimento* clonar();
};



#endif //TESTETP_RELVA_H
