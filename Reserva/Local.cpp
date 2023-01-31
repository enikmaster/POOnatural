#include "Local.h"
Local::Local(int o, int lx, int ly, char to, Reserva* r) : ocupaId(o), localX(lx), localY(ly), tipoOcupante(to), reserva(r) {};
Local::Local(const Local& outro) : Local(outro.getOcupaId(), outro.getLocalX(), outro.getLocalY(), outro.getTipoOcupante(), outro.getReserva()){};