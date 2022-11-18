#ifndef POONATURAL_ALIMENTO_H
#define POONATURAL_ALIMENTO_H
#include <string>
#include <vector>
#include "Animal.h"
#include "Animal.cpp"
using namespace std;

string getCheiro(int x){

    vector<string> cheiros2;
    cheiros2.push_back("erva");
    cheiros2.push_back("verdura");
    cheiros2.push_back("carne");
    cheiros2.push_back("ketchup");

}



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

class Alimento {
public:
    // con/de-structors\
    Alimento();
    ~Alimento();
    // getters
    void getFoodId();
    // setters
    void setFoodId();


    int nutri;
    int toxic;
private:
    unsigned foodId;
    string name;
};


#endif //POONATURAL_ALIMENTO_H
