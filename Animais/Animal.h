#ifndef TESTETP_ANIMAL_H
#define TESTETP_ANIMAL_H
#include "../Includes.h"
//#include "../Reserva/Reserva.h"
// int s = cin >> getline(contantes.txt);

class Reserva;
class Animal {
private:
    int posX, posY;
    int tick = 0;
    int animalID;
    char letra;
    int percepcao;
    int fome;
    int deslMin;
    int deslMax;
    int saude; //SAnimal
    int vida; //VAnimal (ao fim de x ticks, o animal vai morrer)
    int peso;
    bool agressividade;
    //Registo* registoAlimentar;
    Reserva* reserva;
public:

    // constructores:
    Animal();
    ~Animal();

    // getters
    int getPosX();
    int getPosY();
    int getdeslMin();
    int getdeslMax();
    char getLetra();
    int getTick();
    int getAnimalID() const {return this->animalID; };
    int getPercepcao();
    int getFome();
    void getSaude();
    void getVida();
    int getPeso();
    void getAgressividade();
    void getRegistoAlimentar();

    // setters
    void setPosX(int valorDeslocamento);
    void setPosY(int valorDeslocamento);
    void setdeslMin(int min);
    void setdeslMax(int max);
    void setLetra(char a);
    void setAnimalID();
    void setPercepcao(int a);
    void setFome(int a);
    void setSaude();
    void setVida();
    void setPeso(int a);
    void setAgressividade();
    void setReserva(Reserva* reserva) {this->reserva = reserva;};
    //void setRegistoAlimentar();

    // actions
    void move(int min, int max);
    void checkSurroundings(int x, int y, int radius);
    void escolhePeso(int a, int b);
    int aleatorio(int a, int b);
    void dies();
    void birth();
    void feed();
    virtual void repro();
    virtual void fomeca();

};


#endif //TESTETP_ANIMAL_H
