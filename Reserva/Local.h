#ifndef INC_03_LEARN_LOCAL_H
#define INC_03_LEARN_LOCAL_H
#include "../Includes.h"
#include "Reserva.h"

using namespace std;
class Local {
public:
    Local(int o, int lx, int ly, char to, Reserva* r);
    Local(const Local& outro);
    //~Local() {}
    // getters
    int getOcupaId() const {return ocupaId;}
    int getLocalX() const {return localX;}
    int getLocalY() const {return localY;}
    char getTipoOcupante() const {return this->tipoOcupante;}
    Reserva* getReserva() const { return this->reserva;}
    // setters
    void setLocalX(int newLocalX) {this->localX = newLocalX;}
    void setLocalY(int newLocalY) {this->localY = newLocalY;}
    void setReserva(Reserva* newReserva) {this->reserva = newReserva;}
    // actions
    Local* clone() { return new Local(*this);};
private:
    int ocupaId;
    int localX;
    int localY;
    char tipoOcupante;
    Reserva* reserva;

    friend class Reserva;
};

#endif //INC_03_LEARN_LOCAL_H
