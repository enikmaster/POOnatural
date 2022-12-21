#ifndef INC_03_LEARN_COMANDO_H
#define INC_03_LEARN_COMANDO_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
class Comando {
public:
    Comando(string c, string d, string a = "") : cmd(c), descr(d), args(a) {};
    ~Comando() {}; // virtual
    // getters
    string getCmd() const { return cmd; }
    string getDescr() const { return descr; }
    string getArgs() const { return args; }
    int getNumArgs() const { return numArgs; }
    // actions
    string getAsString() const;
    int executa(string& comando) const;
    int executa(string& comando, string& arg1)const;
    int executa(string& comando, string& arg1, string& arg2)const;
    int executa(string& comando, string& arg1, string& arg2, string& arg3)const;
    int executa(string& comando, string& arg1, string& arg2, string& arg3, string& arg4)const;
private:
    string cmd;
    string descr;
    string args;
    int numArgs;
};

ostream& operator<<(ostream& out, const Comando& a);

#endif //INC_03_LEARN_COMANDO_H
