#ifndef TESTETP_ALIMENTO_H
#define TESTETP_ALIMENTO_H
#include "../Inc.h"

class Alimento {

private:
    int posX, posY;
    int tick = 0;
    char letra;
    int foodId;
    int nutri;
    int toxic = 0;
    int duracao; // duracao na reserva
    string cheiro1;
    string cheiro2;

public:
    Alimento();
    ~Alimento();
    // getters
    int getPosX();
    int getPosY();
    int getTick();
    int getFoodId();
    int getLetra();
    int getfoodId();
    int getNutri();
    int getToxic();
    int getDuracao();
    string getCheiro1();
    string getCheiro2();

    // setters
    void setPosX(int a);
    void setPosY(int a);
    void setTick();
    void setFoodId();
    void setLetra(char a);
    void setNutri(int a);
    void setToxic(int a);
    void setDuracao(int a);
    void setCheiro1(string a);
    void setCheiro2(string a);

    // actions
    void birth();
    void dies();
    void repro();
    virtual void podridao();

};


#endif //TESTETP_ALIMENTO_H
