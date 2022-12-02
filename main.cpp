// POO 22/23
// Biblioteca para manipulação da consola
//
// Uso fora do âmbito de POO -> Perguntar primeiro aos professores
// Depósito em repositórios públicos -> Perguntar primeiro aos professores
//
// Pode ser aumentada com funcionalidades novas (desde que funcionem)

#include "Includes.h"
#include "Comandos.h"
#include "Constantes.h"
#include "Reserva.h"
#include "Terminal.h"
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
    int showX = 2;
    int showY = 1;
    do {
        Window windowShow = Window(2,1, 16, 8);
        windowShow << set_color(2) << move_to(2,1);
        std::string s;
        windowShow >> s;
        if (s == "KEY_UP") {
            if( showY>0 ) --showY;
            continue;
        }
        if (s == "KEY_DOWN") {
            if( showY<t.getNumRows()-8 ) ++showY;
            continue;
        }
        if (s == "KEY_LEFT") {
            if( showX>0 ) --showX;
            continue;
        }
        if (s == "KEY_RIGHT") {
            if( showX<t.getNumCols()-16 ) ++showX;
            continue;
        }
        break;
    }while(true);
*/


    Terminal &t = Terminal::instance();
    t << move_to(50, 7) << "Bem-" << "Vindo!";

    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }
    t << move_to(45, 16) << set_color(2) << "Carregue numa tecla!";
    t.getchar();

    //resize_term(600,400);
    print_size(t);

    t << no_color();
    Window windowReserva = Window(2, 1, 88, 23);
    windowReserva << set_color(1) << move_to(2, 1);

    Window windowMenu = Window(90, 1, 25, 23);
    //windowMenu << set_color(1) << move_to(0, 0) ;

    Window windowChat = Window(2, 24, 113, 5);
    //windowChat << set_color(1) << move_to(0, 0) ;


    // Ler ficheiro Constantes:
    Constantes a;
    a.getFromFile();

    // Programa Principal:
    int DimX, DimY;
    getReservaDims(DimX, DimY, windowChat);
    Reserva zoo(DimX, DimY, windowReserva);
    getInput(zoo, windowChat, windowReserva, windowMenu);

    return 0;
}