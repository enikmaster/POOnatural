#include "Constantes.h"
#include "Includes.h"
#include "Interfaces/Interface.h"

int constantes::sCoelho;
int constantes::vCoelho;
int constantes::pCoelho;
int constantes::sOvelha;
int constantes::vOvelha;
int constantes::pOvelha;
int constantes::sLobo;
int constantes::vLobo;
int constantes::pLobo;
int constantes::sCanguru;
int constantes::vCanguru;
int constantes::pCanguru;
int constantes::sMacaco;
int constantes::vMacaco;
int constantes::pMacaco;
int constantes::sHumano;
int constantes::vHumano;
int constantes::pHumano;

void Constantes::getFromFile() {
    // corre o ficheiro das constantes e passa os valores para variáveis globais
    std::string line;
    std::fstream myfile;
    myfile.open("../constantes.txt", std::ios::in); // read mode
    if(myfile.is_open()) {
        while (getline(myfile, line)) {
            std::vector<std::string> args = split(line);
            if(args.at(0) == "SCoelho") {
                this->setSCoelho(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "VCoelho") {
                this->setVCoelho(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "PCoelho") {
                this->setPCoelho(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "SOvelha") {
                this->setSOvelha(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "VOvelha") {
                this->setVOvelha(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "POvelha") {
                this->setPOvelha(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "SLobo") {
                this->setSLobo(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "VLobo") {
                this->setVLobo(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "PLobo") {
                this->setPLobo(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "SCanguru") {
                this->setSCanguru(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "VCanguru") {
                this->setVCanguru(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "PCanguru") {
                this->setPCanguru(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "SMacaco") {
                this->setSMacaco(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "VMacaco") {
                this->setVMacaco(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "PMacaco") {
                this->setPMacaco(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "SHumano") {
                this->setSHumano(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "VHumano") {
                this->setVHumano(stoi(args.at(1)));
                continue;
            }
            if(args.at(0) == "PHumano") {
                this->setPHumano(stoi(args.at(1)));
                continue;
            }
        }
        myfile.close();
    } else {
        std::cout << "Erro a abrir o ficheiro" << endl;
        getchar();
    }
}