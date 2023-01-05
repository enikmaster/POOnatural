#ifndef TESTETP_COELHO_H
#define TESTETP_COELHO_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Coelho : public Animal {
public:
    Coelho(char l, int posX, int posY, Reserva *reserva);
    Coelho(char l, Reserva* reserva) : Coelho(l, -1, -1, reserva) {};
    Coelho(const Coelho& outro);
    ~Coelho() override;
    // getters
    string getAlimentacao() {return this->alimentacao;};
    int getVelocidade();
    // setters
    void setAlimentacao(std::string novaAlimentacao) {alimentacao = std::move(novaAlimentacao);};
    // actions
    void checkVitality();
    void populateWithinRange();
    void checkSurrounding();
    void move(int xTarget, int yTarget);
    void dies() override;
    Animal* fazOutro() override;
    void nasce();
    void cicloTurno() override;
private:
    std::string alimentacao;

    /*void fomeca();
    void dies(Reserva *r, int id);
    Animal* fazOutro(Reserva *r);
    void checkSurroundings(Reserva *r, Local *l, int x, int y, int radius, int id);
    void move(int xTarget, int yTarget, int flag);*/

};


#endif //TESTETP_COELHO_H
