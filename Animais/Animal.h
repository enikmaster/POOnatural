#ifndef TESTETP_ANIMAL_H
#define TESTETP_ANIMAL_H
#include "../Includes.h"

// int s = cin >> getline(contantes.txt);

class Reserva;
class Animal {
private:
    int animalId;
    int posX;
    std::string letra;
    int posY;
    int tick = 0;
    int percepcao;
    int fome;
    int deslMin;
    int deslMax;
    int saude; //SAnimal
    int vida; //VAnimal (ao fim de x ticks, o animal vai morrer)
    int peso;
    bool agressividade;
    //Registo* registoAlimentar;
    Reserva* reservaAnimal;
public:

    // constructores:
    Animal();
    ~Animal();

    // getters
    int getPosX();
    int getPosY();
    int getdeslMin();
    int getdeslMax();
    std::string getLetra();
    int getTick();
    int getAnimalId() const {return this->animalId; };
    int getPercepcao();
    int getFome();
    int getSaude();
    int getVida();
    int getPeso();
    void getAgressividade();
    void getRegistoAlimentar();

    // setters
    void setPosX(int valorDeslocamento);
    void setPosY(int valorDeslocamento);
    void setdeslMin(int min);
    void setdeslMax(int max);
    void setLetra(char l);
    void setAnimalID();
    void setPercepcao(int perc);
    void setFome(int f);
    void setSaude();
    void setVida();
    void setPeso(int pa);
    void setAgressividade();
    void setReserva(Reserva* reserva) {this->reservaAnimal = reserva;};
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
