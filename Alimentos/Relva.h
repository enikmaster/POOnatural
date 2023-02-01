#ifndef TESTETP_RELVA_H
#define TESTETP_RELVA_H
#include "../Includes.h"
#include "Alimento.h"

class Relva : public Alimento{
public:
    Relva(char l, int x, int y, Reserva* zoo);
    Relva(char l, Reserva* zoo);
    Relva(const Relva& outro, bool clone = false);
    ~Relva() override = default;
    // getters
    int getSpawnTime() const {return this->spawnTime;};
    // setters
    void setSpawnTime(const int st) {this->spawnTime = st;};
    // actions
    void nasce();
    void dimDuracao();
    void checkVitality();
    void cicloTurno() override;
    Alimento* fazOutro() override;
    Relva* clone() override { return new Relva(*this, true); }
private:
    int spawnTime; // altura em que deve duplicar-se
};



#endif //TESTETP_RELVA_H
