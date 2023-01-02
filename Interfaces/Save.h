#ifndef POONATURAL_SAVE_H
#define POONATURAL_SAVE_H
#include "../Includes.h"
class Reserva;
class Save {
public:
    Save(std::string saveName, Reserva* reservaSave) ;
    // getters
    std::string getNome() const {return this->nome;};
    Reserva* getReservaSave() const {return this->reservaSave;};
    // actions
    void clearReserva();
private:
    std::string nome;
    Reserva* reservaSave;
};

#endif //POONATURAL_SAVE_H
