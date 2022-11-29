//
// Created by Utilizador on 28-Nov-22.
//

#ifndef TRABALHOPRATICO_CONSTANTES_H
#define TRABALHOPRATICO_CONSTANTES_H
#include "Includes.h"
#include "Comandos.h"

class Constantes {
private:
    int SCoelho;
    int VCoelho;
    int PCoelho;
    int SOvelha;
    int VOvelha;
    int POvelha;
    int SLobo;
    int VLobo;
    int PLobo;
    int SCanguru;
    int VCanguru;
    int PCanguru;
    int SMacaco;
    int VMacaco;
    int PMacaco;
    int SHumano;
    int VHumano;
    int PHumano;

public:
    Constantes();
    ~Constantes();
    void getSCoelho();
    void getFromFile();
};


#endif //TRABALHOPRATICO_CONSTANTES_H
