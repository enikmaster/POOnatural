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
    Reserva* getReserva() const;
    int getDimX() const { return dimX;}
    int getDimY() const { return dimY;}
    int getOrigemVisX() const { return origemVisX;}
    int getOrigemVisY() const { return origemVisY;}
    string getAsString() const;
    static int getContadorIds() { return contadorIds; };
    Animal* getAnimal(int id);
    Alimento* getAlimento(int id);
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
    void checkWithinRange(int elX, int elY, int percepcao, vector<int>& idAnimais, vector<int>& idAlimentos) const;
    void addFood(Alimento* alimento);
    void removeFood(int fid);
    void removeFood(int posX, int posY);
    void updateFood();
    void addAnimal(Animal* animal);
    void removeAnimal(int aid);
    bool removeAnimal(int posX, int posY);
    void updateAnimal();
    void addLocal(Local* local);
    bool removeLocal(int lid);
    void updateLocal();
    void deleteAll();
    void alimentar(int aid, int nutri, int tox);


    // TO DO IMPORTANTES
    // quando EXIT tem de ir aos save games e limpar a memória
    // e dentro de cada save ir à reserva e limpar os vetores que estão na memoria
    // as funções já existem, é usar nos sítios certos
    //
    // Rever os ficheiros Constantes.*
    friend class Next;
    friend class Interface;
};

#endif //INC_03_LEARN_RESERVA_H
