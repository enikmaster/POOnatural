#ifndef TESTETP_CANGURU_H
#define TESTETP_CANGURU_H
#include "../Includes.h"
#include "Animal.h"

class Canguru : public Animal {
public:
    Canguru(char l, int posX, int posY, Reserva* reserva);
    Canguru(char l, Reserva* reserva);
    Canguru(const Canguru& outro);
    ~Canguru() override;
    //getters
    int getVelocidade();
    int getIdPai() const { return idPai; };
    bool isNaBolsa() const { return naBolsa; };
    int getIdadeNaBolsa() const { return idadeNaBolsa; };
//    bool isAttacked() const { return attacked; };
    bool temMedo() const { return medo; };
    // setters
    void setAlimentacao(std::string novaAlimentacao) { this->alimentacao = std::move(novaAlimentacao); };
    void setNaBolsa(bool value) { naBolsa = value; };
    void setIdadeNaBolsa(int value) { this->idadeNaBolsa = value + 5; };
//    void setAttacked(bool value) { attacked = value; };
    void setIdPai(const int newIdPai) { this->idPai = newIdPai; };
    void setMedo(bool value) { medo = value; };
    // actions
    void nasce();
    void checkSurrounding();
    bool isBaby() const;
    bool isAdult() const;
    Animal* fazOutro() override;
    void cicloTurno() override;
    Canguru* clone() override { return new Canguru(*this);};
private:
    std::string alimentacao;
    int idPai;
    bool naBolsa;
    int idadeNaBolsa;
    //bool attacked;
    bool medo;
};

#endif //TESTETP_CANGURU_H