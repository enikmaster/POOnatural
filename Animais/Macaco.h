#ifndef TESTETP_MACACO_H
#define TESTETP_MACACO_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Macaco : public Animal{
private:
    int contadorXp;
    std::string alimentacao;


public:
    Macaco(char l, int posX, int posY, Reserva *reserva);
    Macaco(char l, Reserva* reserva) : Macaco(l, -1, -1, reserva) {};
    Macaco(const Macaco& outro);
    ~Macaco() override;
    // getters
    string getAlimentacao() const {return this->alimentacao;};
    int getVelocidade();
    // setters
    void setAlimentacao(std::string novaAlimentacao) {alimentacao = std::move(novaAlimentacao);};
    // actions
    void checkVitality();
    void checkSurrounding();
    Animal* fazOutro() override;
    void nasce();
    void cicloTurno() override;
    Macaco* clone() override { return new Macaco(*this);};

    void xpGain();
    int getContadorXp();
};


#endif //TESTETP_MACACO_H
