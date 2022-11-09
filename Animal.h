#ifndef POO_ANIMAL_H
#define POO_ANIMAL_H
#include <string>

class Animal {
public:
    // con/de-structors
    Animal(char especie, int linha, int coluna);
    ~Animal();
    // getters
    string getAnimalName();
    // setters
    void setAnimalName();
private:
    unsigned animalId;
    string animalName;
};


#endif //POO_ANIMAL_H
