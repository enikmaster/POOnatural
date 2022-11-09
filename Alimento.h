#ifndef POO_ALIMENTO_H
#define POO_ALIMENTO_H
#include <string>

class Alimento {
public:
    // con/de-structors
    Alimento();
    ~Alimento();
    // getters
    void getFoodId();
    // setters
    void setFoodId();
private:
    unsigned foodId;
    string name;
};


#endif //POO_ALIMENTO_H
