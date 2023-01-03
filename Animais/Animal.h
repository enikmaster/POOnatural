#ifndef TESTETP_ANIMAL_H
#define TESTETP_ANIMAL_H
#include "../Includes.h"
#include "../Constantes.h"
class Alimento;
class Reserva;
class Animal {
private:
    int animalId;
    int posX;
    int posY;
    std::string letra;
    int percepcao;
    int deslMin;
    int deslMax;
    int saude; //SAnimal
    int idade; //VAnimal (ao fim de x ticks, o animal vai morrer)
    int peso;
    int paiId;
    int fome;
    //Registo* registoAlimentar;

protected:
    std::vector<Animal*> animaisPerto;
    std::vector<Alimento*> alimentosPerto;
    Reserva* reservaAnimal;
public:
    // constructores:
    Animal(std::string l, int x, int y, Reserva* novaReserva);
    Animal(std::string& l, Reserva* novaReserva) : Animal(l, -1, -1, novaReserva) {};
//    Animal(const Animal& outro) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {};
    virtual ~Animal() {};
    // getters
    int getPosX() const {return this->posX;};
    int getPosY() const {return this->posY;};
    int getdeslMin() const {return this->deslMin;};
    int getdeslMax() const {return this->deslMax;};
    std::string getLetra() const {return this->letra;};
    int getAnimalId() const {return this->animalId;};
    int getPercepcao() const {return this->percepcao;};
    int getFome() const {return this->fome;};
    int getSaude() const {return this->saude;};
    int getIdade() const {return this->idade;};
    int getPeso() const {return this->peso;};
    int getPaiId() const {return this->paiId;};
    Reserva* getReserva();
    //void getRegistoAlimentar() {};
    // setters
    void setPosX(int offsetX) {this->posX = offsetX;};
    void setPosY(int offsetY) {this->posY = offsetY;};
    void setdeslMin(int min) { this->deslMin = min;};
    void setdeslMax(int max) { this->deslMax = max;};
    void setAnimalID(int ai) {this->animalId = ai;};
    void setPercepcao(int perc) {this->percepcao = perc;};
    void setFome(int fa) {this->fome = fa;};
    void setSaude(int sa) {this->saude = sa;};
    void setIdade(int ia) {this->idade = ia;};
    virtual void setPeso(int pa) {this->peso = pa;};
    void setPaiId(int pai) {this->paiId = pai;};
    void setReserva(Reserva* reserva) {this->reservaAnimal = reserva;};
    void addAnimalPerto(Animal* novoAnimal);
    void addAlimentoPerto(Alimento* novoAlimento);
    //void setRegistoAlimentar();

    // actions
    virtual void move(int xTarget, int yTarget, int min, int max) {};
    virtual void checkWithinRange() {};
    virtual void checkSurroundings(int x, int y, int radius) {};
    void escolhePeso(int a, int b);
    int aleatorio(int a, int b);
    //virtual Animal* fazOutro() {};
    virtual void come() {};
    virtual void dies() {};
    virtual void repro() {};
    virtual void incFome() {};
    virtual void cicloTurno() {};
};


#endif //TESTETP_ANIMAL_H
