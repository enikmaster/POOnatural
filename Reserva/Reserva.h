#ifndef INC_03_LEARN_RESERVA_H
#define INC_03_LEARN_RESERVA_H
#include "../Includes.h"

using namespace std;
class Animal;
class Alimento;
class Local;
class Reserva {
    static int contadorIds;
    int dimX;
    int dimY;
protected:
    vector<Animal*> animais;
    vector<Alimento*> alimentos;
    vector<Local*> locaisOcupados;
public:
    Reserva(int largura, int altura);
    Reserva(const Reserva& outra);
    //~Reserva() {};
    // getters
    int getDimX() const { return dimX;}
    int getDimY() const { return dimY;}
    string getAsString() const;
    static int getContadorIds() { return contadorIds; };
    Animal* getAnimal(int id);
    Alimento* getAlimento(int id);
    // setters
    void setToEmptyByPos(int posx, int posY);
    // actions
    void incContadorIds() {++contadorIds;}
    bool checkPosOcupado(int posX, int posY) const;
    void checkWithinRange(int elX, int elY, int percepcao, vector<int>& idAnimais, vector<int>& idAlimentos) const;
    void addFood(Alimento* alimento);
    void removeFood(int fid);
    void removeFood(int posX, int posY);
    void addAnimal(Animal* animal);
    void removeAnimal(int aid);
    bool removeAnimal(int posX, int posY);
    void addLocal(Local* local);
    bool removeLocal(int lid);
    void updateLocal(int id, int posX, int posY);
    void limpaMortos();
    void deleteAll();
    void alimentar(int aid, int nutri, int tox);
    void alimentarPorXY(int x, int y, int nutri, int tox);


    // TO DO IMPORTANTES
    // quando EXIT tem de ir aos save games e limpar a memória
    // e dentro de cada save ir à reserva e limpar os vetores que estão na memoria
    // as funções já existem, é usar nos sítios certos
    friend class Next;
    friend class Interface;
};

#endif //INC_03_LEARN_RESERVA_H
