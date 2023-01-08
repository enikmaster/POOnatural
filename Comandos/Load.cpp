#include "Load.h"
#include "../Interfaces/Interface.h"

Load::Load(string& cmd, string& filename, vector<string>& guardaFrases, Interface* inter): Comando(cmd) {
    string line;
    fstream fileCmd;
    fileCmd.open(("../" + filename), std::ios::in); // read mode
    if(fileCmd.is_open()) {
        while(getline(fileCmd, line))
            guardaFrases.push_back(line);
        fileCmd.close();
    } else {
        inter->infoErroFileOpen();
    }
}