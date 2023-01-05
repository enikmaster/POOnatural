#include "Corpo.h"

Corpo::Corpo(int posX, int posY, int nutri, Reserva* reservaFood) : Alimento('p', posX, posY, reservaFood) {
    setNutri(nutri);
    setToxic(0);
    setDuracao(nutri * 2);
    setCheiros("carne");
    setIsAlive(true);
};
void Corpo::cicloTurno() {
    // diminui valor nutritivo
    if(getNutri() > 0)
        dimNutri();
    // aumenta toxicidade
    if(getToxic() < getDuracao())
        incToxic();
}