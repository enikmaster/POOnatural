#ifndef INC_03_LEARN_COMANDO_H
#define INC_03_LEARN_COMANDO_H
#include "../Includes.h"
#include "../Reserva/Reserva.h"

using namespace std;
class Comando {
public:
    Comando(string c, string d = "", string a = "") : cmd(std::move(c)), descr(std::move(d)), args(std::move(a)) {};
    virtual ~Comando() {};
    // getters
    string getCmd() const { return cmd; }
    string getDescr() const { return descr; }
    string getArgs() const { return args; }
    string getAsString() const;
    // actions
    int executa(string& comando, Reserva* zoo)const;
    int executa(string& comando, string& arg1, Reserva* zoo)const;
    int executa(string& comando, string& arg1, string& arg2, Reserva* zoo)const;
    int executa(string& comando, string& arg1, string& arg2, string& arg3, Reserva* zoo)const;
    int executa(string& comando, string& arg1, string& arg2, string& arg3, string& arg4, Reserva* zoo)const;

private:
    string cmd;
    string descr;
    string args;

    friend class Reserva;
};

ostream& operator<<(ostream& out, const Comando& a);

#endif //INC_03_LEARN_COMANDO_H
