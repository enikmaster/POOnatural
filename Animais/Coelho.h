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
    Coelho* clone() override { return new Coelho(*this);};
private:
    std::string alimentacao;
};

#endif //TESTETP_COELHO_H