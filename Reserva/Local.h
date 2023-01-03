#ifndef INC_03_LEARN_LOCAL_H
#define INC_03_LEARN_LOCAL_H
#include "../Includes.h"
#include "Reserva.h"

using namespace std;
class Local {
public:
    Local(int o, int lx, int ly, string to , Reserva* r);
    //~Local() {}
    // getters
    int getOcupaId() const {return ocupaId;}
    int getLocalX() const {return localX;}
    int getLocalY() const {return localY;}
    string getLetraOcupante() const {return this->tipoOcupante;};
    int getTipoOcupante() const {return (int)tipoOcupante[0];}
    Reserva* getReserva() const {return reserva;}
    // setters
    void setOcupaId(int newId) {this->ocupaId = newId;}
    void setLocalX(int newLocalX) {this->localX = newLocalX;}
    void setLocalY(int newLocalY) {this->localX = newLocalY;}
    void setTipoOcupante(string& newTipoOcupante) {this->tipoOcupante = newTipoOcupante;}
    void setReserva(Reserva* newReserva) {this->reserva = newReserva;}
    // actions
    void tipoOcupanteToUpper();
private:
    int ocupaId;
    int localX;
    int localY;
    string tipoOcupante;
    Reserva* reserva;

    friend class Reserva;
};

#endif //INC_03_LEARN_LOCAL_H
