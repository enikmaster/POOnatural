#ifndef TESTETP_ALIMENTO_H
#define TESTETP_ALIMENTO_H
#include "../Includes.h"

class Reserva;
using namespace std;
class Alimento {
    int foodId;
    string letra;
    int posX;
    int posY;
    int nutri;
    int toxic;
    int duracao; // duracao na reserva
    vector<string> cheiros;
protected:
    Reserva* reservaAlimento;
public:
    Alimento(string l, const int x, const int y, Reserva* newReserva);
    Alimento(const string& l, Reserva* newReserva) : Alimento(l, -1, -1, newReserva) {};
    Alimento(const Alimento& outro) {};
    virtual ~Alimento();
    // getters
    int getPosX() const { return this->posX;}
    int getPosY() const { return this->posY;}
    int getFoodId() const { return this->foodId;};
    string getLetra() const { return this->letra;};
    int getNutri() const { return this->nutri;};
    int getToxic() const { return this->toxic;};
    int getDuracao() const { return this->duracao;};
    string getCheiro(int pos) const {return this->cheiros.at(pos);};
    int getQuantidadeCheiros() const {return this->cheiros.size();};
    // setters
    void setReserva(Reserva* reserva) {this->reservaAlimento = reserva;};
    void setPosX(const int x){ this->posX = x;};
    void setPosY(const int y){ this->posY = y;};
    void setFoodId(const int fi) { this->foodId = fi;};
    void setNutri(const int n){ this->nutri = n;};
    void setToxic(const int t){ this->toxic = t;};
    void setDuracao(const int d){ this->duracao = d;};
    void setCheiros(const string& c);

    // actions
    virtual void cicloTurno() {};
};

#endif //TESTETP_ALIMENTO_H
