#include "Bife.h"
#include "../Reserva/Reserva.h"

Bife::Bife(char l, int posX, int posY, Reserva* reservaFood) : Alimento(l, posX, posY, reservaFood) {
    setNutri(10);
    setToxic(2);
    setDuracao(30);
    setCheiros("carne");
    setCheiros("ketchup");
    setIsAlive(true);
};
Bife::Bife(char l, Reserva* reservaFood) : Bife(l, -1, -1, reservaFood) {};
void Bife::checkVitality() {
    if(getDuracao() <= 0)
        setIsAlive(false);
}
void Bife::cicloTurno() {
    // isto vai ser chamado a cada turno
    if(getNutri() > 0) {
        dimNutri();
    }
    dimDuracao();
    checkVitality();
}