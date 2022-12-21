#include "Comando.h"
#include "../Interface.h"

using namespace std;
string Comando::getAsString() const {
    ostringstream os;
    os << "Comando: " << getCmd() << " " << getArgs() << endl;
    os << "Descricao: " << getDescr() << endl;
    return os.str();
}

int Comando::executa(string& comando) const {
    if(comando == "n"){
        //avancaTurno();
        return 0;
    }
    if(comando == "anim") {
        //anim();
        return 0;
    }
    if(comando == "visanim") {
        //visanim();
        return 0;
    }
    if(comando == "exit")
        return -2;
    return 1;
}
int Comando::executa(string& comando, string& arg1) const {
    if(comando == "animal"){
        //criaAnimal(arg1) {
        return 0;
    }
    if(comando == "killid") {
        //killid(arg1);
        return 0;
    }
    if(comando == "food") {
        //criaFood(arg1);
        return 0;
    }
    if(comando == "nofood") {
        //noFood(arg1);
        return 0;
    }
    if(comando == "info") {
        //myInfo(arg1);
        return 0;
    }
    if(comando == "n") {
        //avancaTurno(arg1);
        return 0;
    }
    if(comando == "store") {
        //myStore(arg1);
        return 0;
    }
    if(comando == "restore") {
        //myRestore(arg1);
        return 0;
    }
    if(comando == "load") {
        //myLoad(arg1);
        return 0;
    }
    if(comando == "help")
        return -1;
    return 1;
}
int Comando::executa(string& comando, string& arg1, string& arg2) const {
    if(comando == "kill"){
        //kill(arg1, arg2);
        return 0;
    }
    if(comando == "nofood") {
        //noFood(arg1, arg2);
        return 0;
    }
    if(comando == "empty") {
        //myEmpty(arg1, arg2);
        return 0;
    }
    if(comando == "see") {
        //see(arg1, arg2);
        return 0;
    }
    if(comando == "n") {
        //avancaTurno(arg1, arg2);
        return 0;
    }
    if(comando == "slide") {
        //slide(arg1, arg2);
        return 0;
    }
    return 1;
}
int Comando::executa(string& comando, string& arg1, string& arg2, string& arg3) const {
    if(comando == "animal"){
        //criaAnimal(arg1, arg2, arg3);
        return 0;
    }
    if(comando == "food") {
        //food(arg1, arg2, arg3);
        return 0;
    }
    if(comando == "feedid") {
        //feedid(arg1, arg2, arg3);
        return 0;
    }
    return 1;
}
int Comando::executa(string& comando, string& arg1, string& arg2, string& arg3, string& arg4) const {
    if(comando == "feed") {
        //feed(arg1, arg2, arg3, arg4);
        return 0;
    }
    return 1;
}
void criaAnimal(string& arg1) {}
void criaAnimal(string& arg1, string& arg2, string& arg3) {}

ostream& operator<<(ostream& out, const Comando& a) {
    out << a.getAsString();
    return out;
}