#include "Relva.h"

Relva::Relva(string l, const int x, const int y, Reserva* zoo) : Alimento(std::move(l), x, y, zoo) {
    setNutri(3);
    setDuracao(vRelva);
    setToxic(0);
    setCheiros("erva");
    setCheiros("verdura");
};
Relva::Relva(string& l, Reserva* zoo) : Relva(l, -1, -1, zoo) {}

/*void Relva::spawn() {
    // passados 75% de 20 = 5
    if (Relva::getTick() == 5) {
        // new Relva  novoRelva::getPosX - rand(4-8) e getPosT - rand(4-8)
        // se naquela posicao já houver um alimento, envia um getTick() para o
        // metodo Relva::tryAgain(int tick, int posX, int posY); (to be implemented)
        // Relva::tryAgain(int a, int posX, int posY) {
        //     a++;
        //     if (getTick() == a) { new Relva etc}
        // }
        // isto funciona se este metodo fôr chamado a cada tick global
    }

};*/

Relva::~Relva() {

}
