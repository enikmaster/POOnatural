#include "Reserva.h"
// construtores e destrutores
using namespace std;
Reserva::Reserva(int DimX, int DimY, term::Window &janela) : dimX(DimX), dimY(DimY)  {
    if (DimX == 0) {
        setDimX();
        setDimY();
    } else {
        cout << "Dimensao X da reserva: " << getDimX() << endl;
        cout << "Dimensao Y da reserva: " << getDimX() << endl;
    }
    elementoId = 0;
}
Reserva::~Reserva() {
    cout << "Destruida" << endl;
}
// getters
int Reserva::getId() const {
    return elementoId;
}
int Reserva::getDimX() const {
    return dimX;
}
int Reserva::getDimY() const {
    return dimY;
}
/*vector<Animal> Reserva::getAnimais() const {
    // devolve o vetor ou o ponteiro? misterioso...
}
vector<Alimento> Reserva::getAlimentos() const {
    // devolve o vetor ou o ponteiro? misterioso...
}*/
// setters
void Reserva::setId() {
    ++elementoId;
}
void Reserva::setDimX() {
    srand((unsigned) time(NULL));
    dimX = 16 + (rand() % 485);
    cout << "Dimensao X da reserva: " << getDimX() << endl;
}
void Reserva::setDimY() {
    dimY = 16 + (rand() % 485);
    cout << "Dimensao Y da reserva: " << getDimY() << endl;
}
/*vector<Animal> Reserva::addAnimal(const Animal newAnimal) {
    this->animais.push_back(newAnimal);
    // devolvo o ponteiro, o vetor ou nada (void)???
}
vector<Alimento> Reserva::addAlimento(const Alimento newAlimento) {
    this->alimentos.push_back(newAlimento);
    // devolvo o ponteiro, o vetor ou nada (void)???
}
vector<Animal> Reserva::rmAnimal(const Animal deadAnimal) {

}
vector<Alimento> Reserva::rmAlimento(const Alimento deadAlimento) {

}*/