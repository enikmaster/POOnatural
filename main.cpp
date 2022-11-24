// POO 22/23
// Biblioteca para manipulação da consola
//
// Uso fora do âmbito de POO -> Perguntar primeiro aos professores
// Depósito em repositórios públicos -> Perguntar primeiro aos professores
//
// Pode ser aumentada com funcionalidades novas (desde que funcionem)

#include <string>

#include <vector>
#include <fstream>
#include <sstream>
#include "Animal.h"
#include "Alimento.h"
#include "curses.h"
#include "Terminal.h"
#include "Comandos.h"

using namespace term;

void print_size(Terminal& t) {
    std::ostringstream o;
    o << std::setw(7) << t.getNumCols() << "x" << t.getNumRows();
    std::string str = o.str();
    t.clear();
    t << set_color(0) << move_to(t.getNumCols()-str.length(), t.getNumRows()-1) << str;
}

int main() {

    string input;

    cout << "Insira um comando: " << endl;
    getline(cin, input);
    checkComandoUser(input);


    return 0;
}