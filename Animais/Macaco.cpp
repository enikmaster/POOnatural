#include "Macaco.h"
#include "../Reserva.h"


Macaco::Macaco() : SMacaco(50), VMacaco(40){

};

void Macaco::xpGain() {
    if ( contadorXp == 100) {
        //new Humano
    }
}

Macaco::~Macaco(){
    if (VMacaco == 0) {
        //delete
    }
    cout << "\nMacaco Destruido!\n";

}