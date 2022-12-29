#ifndef INC_03_LEARN_RESERVA_H
#define INC_03_LEARN_RESERVA_H
#include "../Includes.h"

using namespace std;
class Animal;
class Alimento;
class Local;
class Reserva {
    static int contadorIds;
    int globalTick;
    int dimX;
    int dimY;
    int origemVisX;
    int origemVisY;
protected:
    vector<Animal*> animais;
    vector<Alimento*> alimentos;
    vector<Local*> locaisOcupados;
public:
    Reserva(int largura, int altura);
    ~Reserva() {}
    // getters
    int getGlobalTicks() const {return globalTick;}
    int getDimX() const { return dimX;}
    int getDimY() const { return dimY;}
    int getOrigemVisX() const { return origemVisX;}
    int getOrigemVisY() const { return origemVisY;}
    string getAsString() const;
    static int getContadorIds() { return contadorIds; }
    // setters
    void setOrigemVisX(int newX);
    void setOrigemVisY(int newY);
    // actions
    void incContadorIds() {++contadorIds;}
    void incGlobalTicks() {++globalTick;}
    bool checkIdExist(int arg) const;
    bool checkIdAlimentos(int arg) const;
    bool checkIdAnimais(int arg) const;
    bool checkPosXOcupado(int posX) const;
    bool checkPosYOcupado(int posY) const;
    void addFood(Alimento* alimento);
    void removeFood(int id);
    void updateFood();
    void addAnimal(Animal* animal);
    void removeAnimal(int id);
    void updateAnimal();
    void addLocal(Local* local);
    bool removeLocal(int id);
    void updateLocal();
    void deleteAll();

    friend class Interface;
};

#endif //INC_03_LEARN_RESERVA_H
