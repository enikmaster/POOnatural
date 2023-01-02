#include "Feedid.h"
Feedid::Feedid(std::string& cmd, int arg1, int arg2, int arg3, Reserva* reservaFeedid) : Comando(cmd) {
    reservaFeedid->alimentar(arg1, arg2, arg3);
}