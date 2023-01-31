#ifndef TESTETP_COELHO_H
#define TESTETP_COELHO_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Coelho : public Animal {
public:
    Coelho(char l, int posX, int posY, Reserva *reserva);
    Coelho(char l, Reserva* reserva);
    Coelho(const Coelho& outro, bool value = false);
    ~Coelho() override;
    // getters
    string getAlimentacao() const {return this->alimentacao;};
    int getVelocidade();
    // setters
    void setAlimentacao(std::string novaAlimentacao) {alimentacao = std::move(novaAlimentacao);};
    // actions
    void checkVitality();
    void checkSurrounding();
    void nasce();
    void cicloTurno() override;
    Animal* fazOutro() override;
    Coelho* clone() override { return new Coelho(*this, true);};
private:
    std::string alimentacao;
};

#endif //TESTETP_COELHO_H