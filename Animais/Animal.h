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
    char letra;
    int percepcao;
    int deslMin;
    int deslMax;
    int saude;
    int idade;
    int peso;
    int fome;
    bool isAlive;
    bool toEmpty {false};
    //Registo* registoAlimentar;

protected:
    std::vector<Animal*> animaisPerto;
    std::vector<Alimento*> alimentosPerto;
    Reserva* reservaAnimal;
public:
    // constructores:
    Animal(char l, int x, int y, Reserva* novaReserva);
    Animal(char l, Reserva* novaReserva) : Animal(l, -1, -1, novaReserva) {};
    Animal(const Animal& outro) : Animal(outro.getLetra(), outro.getPosX(), outro.getPosY(), outro.getReserva()) {};
    virtual ~Animal() {};
    // getters
    int getPosX() const {return this->posX;};
    int getPosY() const {return this->posY;};
    int getdeslMin() const {return this->deslMin;};
    int getdeslMax() const {return this->deslMax;};
    char getLetra() const {return this->letra;};
    int getAnimalId() const {return this->animalId;};
    int getPercepcao() const {return this->percepcao;};
    int getFome() const {return this->fome;};
    int getSaude() const {return this->saude;};
    int getIdade() const {return this->idade;};
    int getPeso() const {return this->peso;};
    bool getIsAlive() const {return this->isAlive;};
    int getQuantidadeAlimentosPerto() {return (int)alimentosPerto.size();};
    bool getToEmpty() const { return toEmpty; };
    Reserva* getReserva() const;
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
    void setIsAlive(bool value) {this->isAlive = value;};
    void setReserva(Reserva* reserva) {this->reservaAnimal = reserva;};
    void addAnimalPerto(Animal* novoAnimal);
    void addAlimentoPerto(Alimento* novoAlimento);
    void setToEmpty(bool value) { toEmpty = value; };
    //void setRegistoAlimentar();

    // actions
    void populateWithinRange();
    void move(int xTarget, int yTarget);
    void escolhePeso(int a, int b);
    int aleatorio(int a, int b);
    virtual Animal* fazOutro() {return nullptr;};
    void come(int nutri, int toxic);
    void dies();
    virtual void cicloTurno() {};
};


#endif //TESTETP_ANIMAL_H
