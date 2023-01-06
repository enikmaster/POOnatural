#ifndef TESTETP_LOBO_H
#define TESTETP_LOBO_H
#include <utility>

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
    int getReproDay() { return this->reproDay;};
    bool getReproduziu() const { return reproduziu; };
    // setters
    void setAlimentacao(std::string novaAlimentacao) { this->alimentacao = std::move(novaAlimentacao); };
    void setReproDay() { reproDay = aleatorio(5, constantes::vLobo); };
    void setReproduziu(bool value) { reproduziu = value; };
    // actions
    void nasce();
    void checkSurrounding();
    void checkVitality();
    void mata();
    Animal* fazOutro() override;
    void cicloTurno() override;
private:
    std::string alimentacao;
    int reproDay;
    bool reproduziu;
/*
private:
    int SLobo;
    int VLobo;
    bool pariu;
    int velo;
    int posPaiX;
    int posPaiY;
    Reserva *reserva;

public:
    Lobo(Reserva *reserva);
    ~Lobo();

    void fomeca();
    Animal* fazOutro(Reserva *obj, int id);
    void dies(Reserva *a, int id);
    void checkSurroundings(Reserva *r, Local *l, int x, int y, int radius, int id);
    void move(int xTarget, int yTarget, const string& tipoDeAlvo);
*/
};

#endif //TESTETP_LOBO_H