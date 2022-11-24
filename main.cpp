#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Animal.h"
#include "Alimento.h"
#include "curses.h"
#include "Terminal.h"
#include "Comandos.h"


using namespace std;

int main() {
    string input;

    cout << "Insira um comando: " << endl;
    getline(cin, input);
    checkComandoUser(input);

    return 0;
}
