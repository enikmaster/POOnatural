#ifndef POONATURAL_ALIMENTO_H
#define POONATURAL_ALIMENTO_H
//#include <string>
//#include <vector>
#include "Animal.h"
//#include "curses.h"
//#include "Terminal.h"

using namespace std;

class Alimento {
public:
    // con/de-structors\
    Alimento();
    ~Alimento();
    // getters
    void getFoodId();
    void getLetra();
    void getfoodId();
    void getNutri();
    void getToxic();
    void getVida();
    void getCheiros();

    // setters
    void setFoodId();
    void setLetra();
    void setfoodId();
    void setNutri();
    void setToxic();
    void setVida();
    void setCheiros();

    // actions
    void birth();
    void dies();
    void repro();

private:
    char letra;
    int foodId;
    int nutri;
    int toxic;
    int vida; // durancao no tabuleiro
    vector<string> cheiros;
};
#endif //POONATURAL_ALIMENTO_H