#include "Reserva.h"
#include "Interface/Interface.h"
#include "Terminal.h"

using namespace term;
int main() {
    srand((unsigned) time(nullptr));
    fflush(stdin);
    Terminal &t = Terminal::instance();
    for(int i=1; i<20; i++)
        t.init_color(i, i, 0);

    t << move_to(50, 7) << "Bem-Vindo!";
    t << move_to(47, 10) << set_color(2) << "Reserva Natural";
    t << move_to(0, 20) << set_color(3) << "Para iniciar a Reserva deve indicar as dimensoes. O maximo admitido e' 500 e o minimo e' 16.";
    t << move_to(0, 21) << set_color(3) << "Se pretender uma Reserva criada com dimensoes aleatorias, coloque 0 0.";
    // pedir ao user as dimensões da reserva
    int DimX, DimY;
    getReservaDims(DimX, DimY, t);
    t.clear();
    refresh();
    t << no_color();
    Reserva zoo(DimX, DimY);
    Interface hub(zoo);

    // inicia o simulador
    hub.start();
    return 0;
}