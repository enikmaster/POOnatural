#include "Feed.h"

Feed::Feed(std::string& cmd, int posX, int posY, int nutri, int toxic, Reserva* r) : Comando(cmd) {
    r->alimentarPorXY(posX, posY, nutri, toxic);

}