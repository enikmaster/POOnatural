#include "Reserva.h"
#include <sstream>
using namespace std;
int Reserva::contadorIds = 0;
string Reserva::getAsString() const {
    ostringstream os;
    os << getDimX() << "x" << getDimY() << endl;
    return os.str();
}