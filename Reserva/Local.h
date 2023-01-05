#ifndef INC_03_LEARN_LOCAL_H
#define INC_03_LEARN_LOCAL_H
#include "../Includes.h"
#include "Reserva.h"

using namespace std;
class Local {
public:
    Local(int o, int lx, int ly, char to, Reserva* r)
        : ocupaId(o), localX(lx), localY(ly), tipoOcupante(to), reserva(r) {};
    //~Local() {}
    // getters
    int getOcupaId() const {return ocupaId;}
    int getLocalX() const {return localX;}
    int getLocalY() const {return localY;}
    char getTipoOcupante() const {return this->tipoOcupante;}
    // setters
    void setLocalX(int newLocalX) {this->localX = newLocalX;}
    void setLocalY(int newLocalY) {this->localY = newLocalY;}
    void setReserva(Reserva* newReserva) {this->reserva = newReserva;}
private:
    int ocupaId;
    int localX;
    int localY;
    char tipoOcupante;
    Reserva* reserva;

    friend class Reserva;
};

#endif //INC_03_LEARN_LOCAL_H
