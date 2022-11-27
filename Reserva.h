#ifndef POONATURAL_RESERVA_H
#define POONATURAL_RESERVA_H

#include "Includes.h"

class Reserva {
public:
    // constructor
    Reserva(int DimX, int DimY, term::Window &janela);
    ~Reserva();
    // getters
    int getId() const;
    int getDimX() const;
    int getDimY() const;
//    vector<Animal> getAnimais() const;
//    vector<Alimento> getAlimentos() const;
    // setters
    void setId();
    void setDimX();
    void setDimY();
//    vector<Animal> addAnimal(const Animal newAnimal);
//    vector<Alimento> addAlimento(const Alimento newAlimento);
//    vector<Animal> rmAnimal(const Animal deadAnimal);
//    vector<Alimento> rmAlimento(const Alimento deadAlimento);

private:
    int elementoId;
    int dimX;
    int dimY;
//    vector<Animal*> animais;
//    vector<Alimento*> alimentos;
    // mais alguma coisa?
};


#endif