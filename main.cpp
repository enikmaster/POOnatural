// POO 22/23
// Biblioteca para manipulação da consola
//
// Uso fora do âmbito de POO -> Perguntar primeiro aos professores
// Depósito em repositórios públicos -> Perguntar primeiro aos professores
//
// Pode ser aumentada com funcionalidades novas (desde que funcionem)

#include "Includes.h"
#include "Comandos.h"
#include "Reserva.h"
#include <string>
#include <sstream>
#include "Reserva.cpp"
#include "Terminal.h"
#include <iomanip>
#include <curses.h>

using namespace term;

void print_size(Terminal& t) {
    std::ostringstream o;
    o << std::setw(7) << t.getNumCols() << "x" << t.getNumRows();
    std::string str = o.str();
    t.clear();
    t << set_color(0) << move_to(t.getNumCols()-str.length(), t.getNumRows()-1) << str;
}


int main() {
/*
    Terminal &t = Terminal::instance();
    const char *str = "World";

    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }

    t << move_to(10, 1) << "Hello " << str;
    for(int i=0; i<20; i++) {
        t << move_to(20, i+3) << set_color(i) << i;
    }
    t << move_to(40, 3) << set_color(0) << "Carregue numa tecla";
    t.getchar();

    print_size(t);

    {
        int x=0;
        int y = 10;
        do {
            t << no_color();
            Window window = Window(x, y, 30, 5);
            window << set_color(1) << move_to(0, 0) ;
            window << "movimente isto com as teclas de direcao e depois carregue em enter";

            std::string s;
            s.resize(200);
            window >> s;
            if (s == "KEY_RESIZE") {
                print_size(t);
                continue;
            }
            if (s == "KEY_UP") {
                if( y>0 ) y--;
                continue;
            }
            if (s == "KEY_DOWN") {
                if( y<t.getNumRows()-5 ) y++;
                continue;
            }
            if (s == "KEY_LEFT") {
                if( x>0 ) x--;
                continue;
            }
            if (s == "KEY_RIGHT") {
                if( x<t.getNumCols()-30 ) x++;
                continue;
            }

            Window w2 = t.create_window(0, 20, 30, 3, false);
            w2 << s;
            break;
        } while(true);

    }

    t << move_to(0, 10) << "";

    std::string str_in;
    str_in.resize(50);
    t << no_color() << "Introduza uma string: ";
    t >> str_in;
    t << move_to(10, 3) << str_in;

    t << "\n" << "carregue numa tecla";
    t.getchar();

    return 0;

    */
    Terminal &t = Terminal::instance();
    t << move_to(50, 7) << "Bem-" << "Vindo!";

    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }
    t << move_to(45, 16) << set_color(2) << "Carregue numa tecla!";
    t.getchar();

    print_size(t);
    t << no_color();
    Window windowReserva = Window(2, 1, 88, 23);
    windowReserva << set_color(1) << move_to(2, 1) ;

    Window windowMenu = Window(90, 1, 25, 23);
    //windowMenu << set_color(1) << move_to(0, 0) ;

    Window windowChat = Window(2, 24, 113, 5);
    //windowChat << set_color(1) << move_to(0, 0) ;

    std::string str_in;
    str_in.resize(50);
    //windowChat << no_color() << "Introduza uma string: ";
    //getchar();
    int DimX, DimY;

    getReservaDims(DimX, DimY, windowChat);
    Reserva zoo(DimX, DimY, windowReserva);
    getInput(zoo);

    return 0;
}