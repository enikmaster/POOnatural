#ifndef TESTETP_LOBO_H
#define TESTETP_LOBO_H
#include "../Includes.h"
#include "Animal.h"

class Lobo : public Animal {
public:
    Lobo(char l, int posX, int posY, Reserva* reserva);
    Lobo(char l, Reserva* reserva);
    Lobo(const Lobo& outro);
    ~Lobo() override;
    //getters;
    std::string getAlimentacao() const { return alimentacao; };
    int getVelocidade();
    int getReproDay() const { return this->reproDay;};
    // setters
    void setAlimentacao(std::string novaAlimentacao) { this->alimentacao = std::move(novaAlimentacao); };
    void setReproDay() { reproDay = aleatorio(5, constantes::vLobo); };
    // actions
    void nasce();
    void checkSurrounding();
    void checkVitality();
    Animal* fazOutro() override;
    void cicloTurno() override;
private:
    std::string alimentacao;
    int reproDay;
};

#endif //TESTETP_LOBO_H