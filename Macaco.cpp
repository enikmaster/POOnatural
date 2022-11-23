#include "Macaco.h"
#include <string>
using namespace std;

Macaco::Macaco() {};
Macaco::~Macaco() {};

unsigned Macaco::setSaude() {

}
unsigned Macaco::setVida() {

}
unsigned Macaco::setPercecao() {

}
string Macaco::setName() {
    this->name = "M" + this->getId();
}
