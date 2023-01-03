#include "Local.h"

Local::Local(int o, int lx, int ly, string to , Reserva* r) : ocupaId(o), localX(lx), localY(ly), tipoOcupante(std::move(to)), reserva(r) {
    tipoOcupanteToUpper();
};

void Local::tipoOcupanteToUpper() {
    if(isupper(getTipoOcupante())) {
        //setTipoOcupante(toupper(tipoOcupante[0]));
    }
}