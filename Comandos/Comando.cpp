#include "Comando.h"
#include "Anim.h"
#include "Visanim.h"
#include "Exit.h"
#include "CriaAnimal.h"
#include "Killid.h"
#include "Food.h"
#include "Nofood.h"
#include "Info.h"
#include "Next.h"
#include "Store.h"
#include "Restore.h"
#include "Load.h"
#include "Kill.h"
#include "Empty.h"
#include "See.h"
#include "Slide.h"
#include "Feedid.h"
#include "Feed.h"

using namespace std;
string Comando::getAsString() const {
    ostringstream os;
    os << "Comando: " << getCmd() << " " << getArgs() << endl;
    os << "Descricao: " << getDescr() << endl;
    return os.str();
}
// executa os comandos
int Comando::executa(string& comando, Reserva* zoo)const {
    Reserva* pR = zoo;
    if(comando == "n"){
        Comando* pNext = new Next(comando, pR);
        delete pNext;
        return 0;
    }
    if(comando == "anim") {
        Comando* pAnim = new Anim(comando, pR);
        delete pAnim;
        return 0;
    }
    if(comando == "visanim") {
        Comando* pVisanim = new Visanim(comando, pR);
        delete pVisanim;
        return 0;
    }
    if(comando == "exit"){
        Comando* pExit = new Exit(comando, pR);
        delete pExit;
        return -2;
    }
    return 1;
}
int Comando::executa(string& comando, string& arg1, Reserva* zoo) const {
    Reserva* pR = zoo;
    if(comando == "animal"){
        Comando* pCriaAnimal = new CriaAnimal(comando, (char)toupper(arg1.at(0)), pR);
        delete pCriaAnimal;
        return 0;
    }
    if(comando == "killid") {
        Comando* pKillid = new Killid(comando, stoi(arg1), pR);
        delete pKillid;
        return 0;
    }
    if(comando == "food") {
        Comando* pFood = new Food(comando, (char)tolower(arg1.at(0)), pR);
        delete pFood;
        return 0;
    }
    if(comando == "nofood") {
        Comando* pNofood = new Nofood(comando, stoi(arg1), pR);
        delete pNofood;
        return 0;
    }
    if(comando == "info") {
        //Comando* pInfo = new Info(comando, stoi(arg1), pR);
        //delete pInfo;
        return -3;
    }
    if(comando == "n") {
        Comando* pNext = new Next(comando, stoi(arg1), pR);
        delete pNext;
        return 0;
    }
    if(comando == "store") {
//        Comando* pStore = new Store(comando, arg1, pR);
//        delete pStore;
        return -4;
    }
    if(comando == "restore") {
//        Comando* pRestore = new Restore(comando, arg1, pR);
//        delete pRestore;
        return -5;
    }
    if(comando == "load") {
        // Pensar muito bem neste comando
//        Comando* pLoad = new Load(comando, arg1, pR);
//        delete pLoad;
        return 0;
    }
    if(comando == "help")
        return -1;
    return 1;
}
int Comando::executa(string& comando, string& arg1, string& arg2, Reserva* zoo) const {
    Reserva* pR = zoo;
    if(comando == "kill"){
        Comando* pKill = new Kill(comando, stoi(arg1), stoi(arg2), pR);
        delete pKill;
        return 0;
    }
    if(comando == "nofood") {
        Comando* pNofood = new Nofood(comando, stoi(arg1), stoi(arg2), pR);
        delete pNofood;
        return 0;
    }
    if(comando == "empty") {
        Comando* pEmpty = new Empty(comando, stoi(arg1), stoi(arg2), pR);
        delete pEmpty;
        return 0;
    }
    if(comando == "see") {
//        Comando* pSee = new See(comando, stoi(arg1), stoi(arg2), pR);
//        delete pSee;
        return 0;
    }
    if(comando == "n") {
        Comando* pNext = new Next(comando, pR);
        delete pNext;
        return 0;
    }
    if(comando == "slide") {
        Comando* pSlide = new Slide(comando, arg1, stoi(arg2), pR);
        delete pSlide;
        return 0;
    }
    return 1;
}
int Comando::executa(string& comando, string& arg1, string& arg2, string& arg3, Reserva* zoo) const {
    Reserva* pR = zoo;
    if(comando == "animal"){
        Comando* pCriaAnimal = new CriaAnimal(comando, (char)toupper(arg1.at(0)), stoi(arg2), stoi(arg3), pR);
        delete pCriaAnimal;
        return 0;
    }
    if(comando == "food") {
        Comando* pFood = new Food(comando, (char)tolower(arg1.at(0)), stoi(arg2), stoi(arg3), pR);
        delete pFood;
        return 0;
    }
    if(comando == "feedid") {
        Comando* pFeedid = new Feedid(comando, stoi(arg1), stoi(arg2), stoi(arg3), pR);
        delete pFeedid;
        return 0;
    }
    return 1;
}
int Comando::executa(string& comando, string& arg1, string& arg2, string& arg3, string& arg4, Reserva* zoo) const {
    Reserva* pR = zoo;
    if(comando == "feed") {
//        Comando* pFeed = new Feed(comando, stoi(arg1), stoi(arg2), stoi(arg3), stoi(arg4), pR);
//        delete pFeed;
        return 0;
    }
    return 1;
}

ostream& operator<<(ostream& out, const Comando& a) {
    out << a.getAsString();
    return out;
}