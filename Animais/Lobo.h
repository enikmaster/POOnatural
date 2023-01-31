#ifndef TESTETP_LOBO_H
#define TESTETP_LOBO_H
#include "../Includes.h"
#include "Animal.h"
#include "../Reserva/Reserva.h"

class Lobo : public Animal {
public:
    Lobo(char l, int posX, int posY, Reserva* reserva);
    Lobo(char l, Reserva* reserva);
    Lobo(const Lobo& outro, bool value = false);
    ~Lobo() override;
    //getters;
    std::string getAlimentacao() const { return alimentacao; };
    int getVelocidade();
    int getReproDay() const { return this->reproDay;};
    // setters
    void setAlimentacao(std::string novaAlimentacao) { this->alimentacao = std::move(novaAlimentacao); };
    void setReproDay(const int rDay) { this->reproDay = rDay; };
    // actions
    void nasce();
    void checkSurrounding();
    void checkVitality();
    void cicloTurno() override;
    Animal* fazOutro() override;
    Lobo* clone() override { return new Lobo(*this, true);};
private:
    std::string alimentacao;
    int reproDay;
};

#endif //TESTETP_LOBO_H