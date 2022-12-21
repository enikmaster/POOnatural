#ifndef INC_03_LEARN_RESERVA_H
#define INC_03_LEARN_RESERVA_H
#include <iostream>
#include <vector>
//#include "Animal.h"
#include "Local.h"
using namespace std;
class Reserva {
    static int contadorIds;
    int globalTick;
    int dimX;
    int dimY;
    // tem animais
//    vector<Animal*> animais;
    // tem alimentos
    // vector<Alimento*> alimentos;
    // tem localizações ocupadas
    vector<Local*> locaisOcupados;
public:
    Reserva(int largura, int altura) : dimX(largura), dimY(altura) {}
    ~Reserva() {}
    // getters
    int getDimX() const { return dimX;}
    int getDimY() const { return dimY;}
    int getGlobalTicks() const {return globalTick;}
    string getAsString() const;
    static int getContadorIds() { return contadorIds; }
    // setters

    // actions
    void incContadorIds() {++contadorIds;}
    void incGlobalTicks() {++globalTick;}
    // tem produtos
    // tem expositores ocupados
};


#endif //INC_03_LEARN_RESERVA_H
