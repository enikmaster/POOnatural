#ifndef POONATURAL_MACACO_H
#define POONATURAL_MACACO_H
#include "Animal.h"
using namespace std;

class Macaco: public Animal {
public:
    // construtores / destrutores
    Macaco();
    ~Macaco();
    // setters
    unsigned setSaude();
    unsigned setVida();
    unsigned setPercecao();
    string setName();
    // actions
private:
    string name;
};


#endif //POONATURAL_MACACO_H
