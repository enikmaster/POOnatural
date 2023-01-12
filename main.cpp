#include "Interfaces/Interface.h"
#include "Terminal.h"
#include "Constantes.h"

using namespace term;

int main() {
    srand((unsigned) time(nullptr));
    // cria um novo objeto Constantes em memória
    Constantes* pConstantes {new Constantes()};
    // liberta a memória do objeto Constantes
    delete pConstantes;
    fflush(stdin);
    Terminal& t {Terminal::instance()};
    refresh();
    // cria um novo Interface para o user
    Interface* pHub{new Interface()};
    // inicia o simulador
    pHub->start();
    // após terminar o simulador, limpa tudo
    delete pHub;
    return 0;
}