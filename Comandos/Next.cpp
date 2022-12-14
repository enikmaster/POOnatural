#include "Next.h"
#include "../Animais/Animal.h"
#include "../Alimentos/Alimento.h"
/*template<class T> class Ciclo {
public:
    // Overloaded () operator.
    // This will be called by for_each() function.
    bool operator()(T elemento) const {
        // executa o cicloTurno()
        elemento->cicloTurno();
        return true;
    }
};*/
// avança para o turno seguinte
Next::Next(string cmd, int arg1, Reserva* reserva) : Comando(std::move(cmd)) {
    //for_each(reserva->animais.begin(), reserva->animais.end(), Ciclo<Animal*>() );
    for(int rep = 1; rep <= arg1; ++rep) {
        for (auto *alimento: reserva->alimentos)
            (*alimento).cicloTurno();
        for (auto *animal: reserva->animais)
            (*animal).cicloTurno();
        reserva->limpaMortos();
    }
};