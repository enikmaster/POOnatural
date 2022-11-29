#include "Constantes.h"
#include "Comandos.h"
#include "Terminal.h"

using namespace std;

Constantes::Constantes() {};
Constantes::~Constantes() {};

void Constantes::getSCoelho(){
    //janela << term::move_to(0, 1) << SCoelho;
}
void Constantes::getFromFile() {
    string line;
    fstream myfile;
    myfile.open("constantes.txt", ios::in); // read mode
    if (myfile.is_open()) {

        while (getline(myfile, line)) {
            vector<string> args = split(line);
            if(args.at(0) == "SCoelho") {
                this->SCoelho = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "VCoelho") {
                this->VCoelho = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "PCoelho") {
                this->PCoelho = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "SOvelha") {
                this->SOvelha = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "VOvelha") {
                this->VOvelha = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "POvelha") {
                this->POvelha = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "SLobo") {
                this->SLobo = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "VLobo") {
                this->VLobo = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "PLobo") {
                this->PLobo = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "SCanguru") {
                this->SCanguru = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "VCanguru") {
                this->VCanguru = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "PCanguru") {
                this->PCanguru = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "SMacaco") {
                this->SMacaco = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "VMacaco") {
                this->VMacaco = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "PMacaco") {
                this->PMacaco = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "SHumano") {
                this->SHumano = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "VHumano") {
                this->VHumano = stoi(args.at(1));
                continue;
            }
            if(args.at(0) == "PHumano") {
                this->PHumano = stoi(args.at(1));
                continue;
            }

        }
        myfile.close();
    }
}