#include "Save.h"
#include "../Reserva/Reserva.h"

Save::Save(std::string saveName, Reserva* reservaSave): nome(std::move(saveName)), reservaSave(reservaSave) {};

// actions
void Save::clearReserva() {
    reservaSave->deleteAll();
}