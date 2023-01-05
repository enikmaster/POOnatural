#include "Cenoura.h"

Cenoura::Cenoura(char l, int posX, int posY, Reserva* reservaFood) : Alimento(l, posX, posY, reservaFood) {
    nasce();
}
Cenoura::Cenoura(char l, Reserva* reservaFood) : Cenoura(l, -1, -1, reservaFood) {};
void Cenoura::nasce() {
    setNutri(4);
    setToxic(0);
    setDuracao(1);
    setCheiros("verdura");
    setIsAlive(true);
}
void Cenoura::cicloTurno() {
    incDuracao();
    if(getToxic() < 3) {
        if(getDuracao() % 10 == 0)
            incToxic();
    }
}