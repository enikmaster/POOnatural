#ifndef TESTETP_ALIMENTO_H
#define TESTETP_ALIMENTO_H
#include "../Includes.h"

class Reserva;
using namespace std;
class Alimento {
    int foodId;
    int tick = 0;
    string letra;
    int posX;
    int posY;
    int nutri;
    int toxic = 0;
    int duracao; // duracao na reserva
    vector<string> cheiros;
    Reserva* reservaAlimento;
public:
    Alimento(string l, const int x, const int y, Reserva* newReserva);
    Alimento(const string& l, Reserva* newReserva) : Alimento(l, -1, -1, newReserva) {};
    Alimento(const Alimento& outro) {};
    virtual ~Alimento();
    // getters
    int getPosX() const { return this->posX;}
    int getPosY() const { return this->posY;}
    int getTick() const { return this->tick;};
    int getFoodId() const { return this->foodId;};
    string getLetra() const { return this->letra;};
    int getNutri() const { return this->nutri;};
    int getToxic() const { return this->toxic;};
    int getDuracao() const { return this->duracao;};
    string getCheiro(int pos) const {return this->cheiros.at(pos);};
    int getQuantidadeCheiros() const {return this->cheiros.size();};
    // setters
    void setPosX(const int x){ this->posX = x;};
    void setPosY(const int y){ this->posY = y;};
    void setReserva(Reserva* newReserva) { this->reservaAlimento = newReserva; };
    void setFoodId(const int fi) { this->foodId = fi;};
    void setLetra(string& l){ this->letra = l;};
    void setNutri(const int n){ this->nutri = n;};
    void setToxic(const int t){ this->toxic = t;};
    void setDuracao(const int d){ this->duracao = d;};
    void setCheiros(const string& c);
    void incTick() {++tick;};

    // actions
    //virtual Animal* clonar() const {};
    //void dies() {};
    //virtual void podridao() {};

    //friend class Reserva;
};

#endif //TESTETP_ALIMENTO_H
