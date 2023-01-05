#ifndef TESTETP_ALIMENTO_H
#define TESTETP_ALIMENTO_H
#include "../Includes.h"

class Reserva;
using namespace std;
class Alimento {
    int foodId;
    char letra;
    int posX;
    int posY;
    int nutri;
    int toxic;
    int duracao; // duracao na reserva
    vector<string> cheiros;
    bool isAlive;
protected:
    Reserva* reservaAlimento;
public:
    Alimento(char l, const int x, const int y, Reserva* newReserva);
    Alimento(const char l, Reserva* newReserva) : Alimento(l, -1, -1, newReserva) {};
    Alimento(const Alimento& outro) {};
    virtual ~Alimento();
    // getters
    Reserva* getReserva() const;
    int getPosX() const { return this->posX;}
    int getPosY() const { return this->posY;}
    int getFoodId() const { return this->foodId;};
    char getLetra() const { return this->letra;};
    int getNutri() const { return this->nutri;};
    int getToxic() const { return this->toxic;};
    int getDuracao() const { return this->duracao;};
    string getCheiro(int pos) const {return this->cheiros.at(pos);};
    int getQuantidadeCheiros() const {return this->cheiros.size();};
    bool getIsAlive() const { return this->isAlive;};
    // setters
    void setReserva(Reserva* reserva) {this->reservaAlimento = reserva;};
    void setPosX(const int x){ this->posX = x;};
    void setPosY(const int y){ this->posY = y;};
    void setFoodId(const int fi) { this->foodId = fi;};
    void setNutri(const int n){ this->nutri = n;};
    void setToxic(const int t){ this->toxic = t;};
    void setDuracao(const int d){ this->duracao = d;};
    void setCheiros(const string& c);
    void setIsAlive(const bool value) {this->isAlive = value;};
    // actions
    virtual void cicloTurno() {};
    virtual Alimento* fazOutro() {return nullptr;};
    int aleatorio(int min, int max) const { return min + rand() % (max + 1 - min);};
};

#endif //TESTETP_ALIMENTO_H
