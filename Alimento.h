#ifndef POONATURAL_ALIMENTO_H
#define POONATURAL_ALIMENTO_H
#include <string>
#include <vector>
#include "Animal.h"
#include "curses.h"
#include "Terminal.h"

using namespace std;
/*
string getCheiro(int x){

    vector<string> cheiros2;
    cheiros2.push_back("erva");
    cheiros2.push_back("verdura");
    cheiros2.push_back("carne");
    cheiros2.push_back("ketchup");
return 0;
};
*/

/*
class Relva{
    int VRelva = 20;
    int nutri = 3;
    int toxic = 0;
    int nrCheiros = 2;
    string cheiro = "erva verdura";
};
class Cenoura{
    int nutri = 4;
    int toxic = 1; // funcao toxic c ticks
    string cheiro = "verdura";
};
*/
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
    unsigned foodId;
    string name;
    int nutri;
    int toxic;
    int vida; // durancao no tabuleiro
    vector<string> cheiros;
};


#endif //POONATURAL_ALIMENTO_H
