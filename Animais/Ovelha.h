#ifndef TESTETP_OVELHA_H
#define TESTETP_OVELHA_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Ovelha : public Animal {
public:
    Ovelha(char l, int x, int y, Reserva* zoo);
    Ovelha(char l, Reserva* zoo);
    //Ovelha(const Ovelha& outro, bool value);
    Ovelha(const Ovelha& outro, bool value=false);
    ~Ovelha() override;
    // getters
    std::string getAlimentacao() const {return this->alimentacao;};
    int getVelocidade();
    // setters
    void setAlimentacao(std::string novaAlimentacao) {this->alimentacao = std::move(novaAlimentacao);};
    // actions
    void checkVitality();
    void checkSurrounding();
    void nasce();
    void cicloTurno() override;
    Animal* fazOutro() override;
    Ovelha* clone() override {return new Ovelha(*this, true);};
private:
    std::string alimentacao;
};

#endif //TESTETP_OVELHA_H
