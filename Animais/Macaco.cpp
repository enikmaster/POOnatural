#include "Macaco.h"
#include "../Reserva/Reserva.h"


Macaco::Macaco() : SMacaco(50), VMacaco(40){

};

void Macaco::xpGain() {
    if ( contadorXp == 100) {
        //new Humano
    }
}

Animal* Macaco::fazOutro() {
    return nullptr;
}

Macaco::~Macaco(){
    if (VMacaco == 0) {
        //delete
    }
    cout << "\nMacaco Destruido!\n";

}