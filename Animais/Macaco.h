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
    Macaco(const Macaco& outro, bool value = false);
    ~Macaco() override;
    // getters
    string getAlimentacao() const {return this->alimentacao;};
    int getVelocidade();
    int getXP() const { return this->contadorXp; };
    // setters
    void setAlimentacao(std::string novaAlimentacao) {alimentacao = std::move(novaAlimentacao);};
    void setXP(const int exp) {this->contadorXp = exp; };
    // actions
    void checkVitality();
    void checkSurrounding();
    void nasce();
    void cicloTurno() override;
    Animal* fazOutro() override;
    Macaco* clone() override { return new Macaco(*this);};

    void xpGain();
};


#endif //TESTETP_MACACO_H
