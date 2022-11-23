#include <string>
#include <vector>
#include <iostream>
#include "Animal.h"
#include "Alimento.h"
#include "curses.h"
#include "Terminal.h"


using namespace std;

int main() {

    Animal a;
    cout << a.escolhePeso() << endl;
    a.move(1,1);
    a.checkSurroundings(10,10,4);

    return 0;
}
