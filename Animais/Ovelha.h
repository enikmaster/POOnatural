#ifndef TESTETP_OVELHA_H
#define TESTETP_OVELHA_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Ovelha : public Animal {
public:
    Ovelha(char l, int x, int y, Reserva* zoo);
    Ovelha(char l, Reserva* zoo);
    Ovelha(const Ovelha& outro);
    ~Ovelha() override;
    // getters
    std::string getAlimentacao() const {return this->alimentacao;};
    int getVelocidade();
    // setters
    void setAlimentacao(std::string novaAlimentacao) {this->alimentacao = std::move(novaAlimentacao);};
    // actions
    void checkVitality();
    void checkSurrounding();
    Animal* fazOutro() override;
    void nasce();
    void cicloTurno() override;
private:
    std::string alimentacao;
};

#endif //TESTETP_OVELHA_H
