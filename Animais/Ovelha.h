#ifndef TESTETP_OVELHA_H
#define TESTETP_OVELHA_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Ovelha : public Animal {
public:
    Ovelha(std::string l, int x, int y, Reserva* zoo);
    Ovelha(std::string& l, Reserva* zoo);
    ~Ovelha();
    // getters
    string getAlimentacao() {return this->alimentacao;};
    int getVelocidade();
    // setters
    void setAlimentacao(std::string novaAlimentacao) {this->alimentacao = std::move(novaAlimentacao);};
    // actions
    bool isAlive() const;
    void come(int nutri, int toxic);
    void populateWithinRange();
    void checkSurrounding();
    void move(int xTarget, int yTarget);
    void dies();
    //Animal* fazOutro(Reserva *r);
    void cicloTurno();
private:
    std::string alimentacao;
};

#endif //TESTETP_OVELHA_H
