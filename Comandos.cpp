#include "Includes.h"
#include "Reserva.h"
#include "Terminal.h"
#include "Comandos.h"

using namespace std;

const vector<string> listDirections {"up", "down", "left", "right"};
const vector<string> listEspecies {"c", "o", "l", "g", "m"};
const vector<string> listAlimentos {"r", "t", "b", "a"};
const vector<string> listComandos {"animal", "kill", "killid", "food", "feed",
                                   "feedid", "nofood", "empty", "see",
                                   "info", "n", "anim", "visanim", "store",
                                   "restore", "load", "slide", "exit", "help"};
// conta o numero de argumentos inseridos no terminal
int numArgs(stringstream& teste, string& temp ) {
    int cnt{0};
    while(teste >> temp)
        ++cnt;
    return cnt;
}

// divide a linha inserida em strings e guarda num vetor de strings
vector<string> split(const string& line) {
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    // invariant: we have processed characters [original value of i, i)
    while (i != line.size()) {
        // ignore leading blanks
        // invariant: characters in range [original i, current i) are all spaces
        while (i != line.size() && isspace(line.at(i)))
            ++i;

        // find end of next word
        string_size j = i;
        // invariant: none of the characters in range [original j, current j)is a space
        while (j != line.size() && !isspace(line.at(j)))
            j++;

        // if we found some nonwhitespace characters
        if (i != j) {
            // copy from s starting at i and taking j - i chars
            ret.push_back(line.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}
// verifica e devolve as dimensoes da reserva a ser criada
void getReservaDims(int& DimX, int& DimY, term::Window &janela) {
    string input;
    bool flag = false;
    do {
        janela << term::move_to(0, 0) << "Insira a dimensao da reserva (altura comprimento) ou 0 0 para um tamanho aleatorio: ";
        //getline(cin, input);
        janela >> input;
        stringstream iss (input);
        string temp{};
        int nArgs = numArgs(iss, temp);
        if(nArgs > 2 || nArgs == 0) {
            janela << term::move_to(0, 1) << "informacao invalida...";
            continue;
        }
        vector<string> args = split(input);
        if((stoi(args.at(0)) == 0) && (stoi(args.at(1)) == 0)) {
            DimX = 0;
            DimY = 0;
            flag = true;
        }
        if((stoi(args.at(0)) >= 16 && stoi(args.at(0)) <= 500) && (stoi(args.at(1)) >= 16 && stoi(args.at(1)) <= 500)) {
            DimX = stoi(args.at(0));
            DimY = stoi(args.at(1));
            flag = true;
        }
    }while(!flag);
}
// verifica se o comando existe na lista de comandos do programa
bool verificaCmd(const string &cmd, term::Window &janela){
    bool xpto = find(listComandos.begin(), listComandos.end(), cmd) != listComandos.end();
    if (!xpto)
        janela << term::move_to(0, 1) << "Inseriu mal o primeiro comando!\n";
    return xpto;
}
// verifica se a especie (letra) existe na lista
bool verificaEspecie(string &esp, term::Window &janela) {
    bool xpto = find(listEspecies.begin(), listEspecies.end(), esp) != listEspecies.end();
    if (!xpto){
        janela << term::move_to(0, 1) << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}
// verifica se o alimento (letra) existe na lista
bool verificaAlimento(string &tipo, term::Window &janela) {
    bool xpto = find(listAlimentos.begin(), listAlimentos.end(), tipo) != listAlimentos.end();
    if (!xpto){
        janela << term::move_to(0, 1) << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}
// verifica se a direcao existe na lista
bool verificaDirecao(string &dir, term::Window &janela) {
    bool xpto = find(listDirections.begin(), listDirections.end(), dir) != listDirections.end();
    if (!xpto){
        janela << term::move_to(0, 1) << "Inseriu mal o segundo comando!\n";
    }
    return xpto;
}
// verifica se a posição está dentro da reserva e posteriormente, se está associado a alguma coisa
bool verificaXY(const int &posX, const int &posY, const Reserva& reserva, term::Window &janela) {
    if (posX < 1 || posY < 1) {
        janela << term::move_to(0, 1) << "Inseriu valores invalidos de linhas e/ou colunas \n";
        return false;
    }
    if (posY > reserva.getDimY() || posX > reserva.getDimX() ){
        janela << term::move_to(0, 1) << "Inseriu valores invalidos de linhas e/ou colunas \n";
        return false;
    }
    return true;
}
// verifica se o id está na reserva
bool verificaId(const int &id, const Reserva &reserva) {
    return id == reserva.getId();
}
// verifica se a sintaxe do comando está correta
bool verificaSintaxe(const int nArgs, const int nArgsExp) {
    return nArgs == nArgsExp;
}
// envia para o output uma mensagem
void infoToUser(term::Window &janela) {
//    janela << clear();
    janela << term::move_to(0, 0) << "O que pretende validar: ";
}
// comandos
void criaAnimal(char especie, int lin, int col, term::Window &janela, term::Window& janelaReserva){
    janela << term::move_to(0, 1) << "A verificar na 2 fase\n";
    janelaReserva << term::move_to(6, 10) << term::set_color(1) << "A";
}
void criaAnimal(char especie, term::Window &janela, term::Window& janelaReserva) {
    srand((unsigned) time(NULL));
    int x1 = (rand() % 88) + 2 ;
    int x2 = (rand() % 22) + 1 ;
    janela << term::move_to(0, 1) << "A verificar na 2 fase";
    // adiciona um animal à reserva
    // vai à lista de animais da reserva buscar a posX e posY do animal criado
    // imprime esse animal na window reserva
    janelaReserva << term::move_to(x1, x2)<< term::set_color(1) << "A";
}
void killAnimal(int lin, int col, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void killAnimal(int id, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void placeAlimento(char tipo, int lin, int col, term::Window &janela, term::Window &janelaReserva){
    janelaReserva << term::move_to(10, 6) << term::set_color(2) << "L";
    janela << term::move_to(0, 1) << "A verificar na 2 fase\n";
};
void placeAlimento(char tipo, term::Window &janela, term::Window& janelaReserva) {
    int x1 = (rand() % 88) + 2 ;
    int x2 = (rand() % 22) + 1 ;
    janela << term::move_to(0, 1) << "A verificar na 2 fase\n";
    janelaReserva << term::move_to(x1, x2) << term::set_color(2)  << "L";
}
void feedDirectly(int lin, int col, int nut, int tox, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void feedId(int id, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void removeAlimento(int lin, int col, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void removeAlimento(int id, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void deletePos(int lin, int col, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void checkPos(int lin, int col, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void checkId(int id, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void tick(term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void tick(int pausa, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void listIdsReserva(term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void listIdsWindow(term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void store(string nome, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void restore(string nome, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void deslocaAreaViz(string dir, int tamanho, term::Window &janela){janela << term::move_to(0, 1) << "A verificar na 2 fase\n";};
void reservaInfo(Reserva& reserva, term::Window& janelaInfo) {
    janelaInfo << term::move_to(0, 0) << "DimX : " << reserva.getDimX();
    janelaInfo << term::move_to(0, 1) << "DimY : " << reserva.getDimY();
}
// recebe os comandos
void getInput(Reserva& reserva, term::Window &janela1, term::Window &janela2, term::Window &janela3) {
    reservaInfo(reserva, janela3);
    string input{};
    janela1.clear();
    infoToUser(janela1);
    //getline(cin, input);
    do {
        janela1 >> input;
        janela1.clear();
        stringstream iss (input);
        string temp{};
        int nArgs = numArgs(iss, temp);
        if(nArgs > 5) {
            janela1 << term::move_to(0, 1) << "demasiada informacao...";
            infoToUser(janela1);
            continue;
        }
        if(nArgs < 1) {
            janela1 << term::move_to(0, 1) << "sem instrucoes...";
            infoToUser(janela1);
            continue;
        }
        vector<string> args = split(input);
        // ################################  VERIFICAÇÕES  ########################################
        if ( !verificaCmd(args.at(0), janela1) ) {
            infoToUser(janela1);
            continue;
        }
        // CRIAR ANIMAL
        if ( args.at(0) == "animal") {
            if (!verificaEspecie(args.at(1), janela1)) {
                infoToUser(janela1);
                continue;
            }
            if(verificaSintaxe(nArgs, 2)) {
                // animal <letra>
                criaAnimal(args.at(1)[0], janela1, janela2);
                infoToUser(janela1);
                continue;
            }
            if(verificaSintaxe(nArgs, 4)) {
                if (!verificaXY(stoi(args.at(2)), stoi(args.at(3)), reserva,janela1)) {
                    infoToUser(janela1);
                    continue;
                }
                // animal <letra> <posX> <posY>
                criaAnimal(args.at(1)[0], stoi(args.at(2)), stoi(args.at(3)),janela1, janela2);
                infoToUser(janela1);
                continue;
            }
            if(nArgs != 2 && nArgs != 4){
                janela1 << term::move_to(0, 1) << "numero de argumentos invalido";
                infoToUser(janela1);
                continue;
            }
        }
        // MATAR ANIMAL POSIÇÃO
        if ( args.at(0) == "kill") {
            if (verificaSintaxe(nArgs, 3)) {
                if ( !verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva,janela1) ) {
                    infoToUser(janela1);
                    continue;
                }
                // kill <posX> <posY>
                killAnimal(int (stoi(args.at(1))), int (stoi(args.at(2))),janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "numero de argumentos invalido";
                infoToUser(janela1);
                continue;
            }
        }
        // MATAR ANIMAL ID
        if ( args.at(0) == "killid") {
            if (verificaSintaxe(nArgs, 2)) {
                if ( !verificaId(stoi(args.at(1)), reserva) ) {
                    janela1 << term::move_to(0, 1) << "Erro! ID invalido!\n" << "O que pretende validar: ";
                    continue;
                }
                // killid <id>
                killAnimal(stoi(args.at(1)),janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "numero de argumentos invalido";
                infoToUser(janela1);
                continue;
            }
        }
        // COLOCAR ALIMENTO
        if ( args.at(0) == "food") {
            if (!verificaAlimento(args.at(1), janela1)) {
                infoToUser(janela1);
                continue;
            }
            if (verificaSintaxe(nArgs, 2)) {
                // food <letra>
                placeAlimento(args.at(1)[0], janela1, janela2);
                infoToUser(janela1);
                continue;
            }
            if (verificaSintaxe(nArgs, 4)) {
                if ( !verificaXY(stoi(args.at(2)), stoi(args.at(3)), reserva, janela1)) {
                    infoToUser(janela1);
                    continue;
                }
                // food <letra> <posX> <posY>
                placeAlimento(args.at(1)[0], stoi(args.at(2)), stoi(args.at(3)), janela1, janela2);
                infoToUser(janela1);
                continue;
            }
            if(nArgs != 2 && nArgs != 4) {
                janela1 << term::move_to(0, 1) << "numero de argumentos invalido";
                infoToUser(janela1);
                continue;
            }
        }
        //  ALIMENTAR DIRETAMENTE ANIMAIS
        if ( args.at(0) == "feed") {
            if (verificaSintaxe(nArgs, 5)) {
                if ( !verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva, janela1) ) {
                    infoToUser(janela1);
                    continue;
                }
                // feed <posX> <posY> <nutri> <toxic>
                feedDirectly(stoi(args.at(1)),stoi(args.at(2)), stoi(args.at(3)), stoi(args.at(4)),janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "numero de argumentos invalido";
                infoToUser(janela1);
                continue;
            }
        }
        if ( args.at(0) == "feedid") {
            if (verificaSintaxe(nArgs, 2)) {
                if (!verificaId(stoi(args.at(1)), reserva)) {
                    infoToUser(janela1);
                    continue;
                }
                // feedid <id>
                feedId(stoi(args.at(1)),janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "numero de argumentos invalido";
                infoToUser(janela1);
                continue;
            }
        }
        //  REMOVER ALIMENTO
        if ( args.at(0) == "nofood") {
            if (verificaSintaxe(nArgs, 3)) {
                if ( !verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva, janela1) ) {
                    infoToUser(janela1);
                    continue;
                }
                // nofood <posX> <posY>
                removeAlimento( stoi(args.at(1)), stoi(args.at(2)),janela1);
                infoToUser(janela1);
                continue;
            }
            if (verificaSintaxe(nArgs, 2)) {
                if ( !verificaId(stoi(args.at(1)), reserva)) {
                    janela1 << term::move_to(0, 1) << "Erro! ID invalido!";
                    infoToUser(janela1);
                    continue;
                }
                // nofood <id>
                removeAlimento(reserva.getId(),janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros";
                infoToUser(janela1);
                continue;
            }
        }
        // ELIMINAR O QUE QUER QUE ESTEJA NUMA POSIÇÃO
        if ( args.at(0) == "empty") {
            if (verificaSintaxe(nArgs, 3)) {
                if (!verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva,janela1)) {
                    infoToUser(janela1);
                    continue;
                }
                // empty <posX> <posY>
                deletePos(stoi(args.at(1)), stoi(args.at(2)), janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // VER O QUE SE ENCONTRA NUMA POSIÇÃO
        if ( args.at(0) == "see") {
            if (verificaSintaxe(nArgs, 3)) {
                if (!verificaXY(stoi(args.at(1)), stoi(args.at(2)), reserva, janela1)) {
                    infoToUser(janela1);
                    continue;
                }
                // see <posX> <posY>
                checkPos(int(stoi(args.at(1))), int(stoi(args.at(2))), janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // VER INFORMAÇÃO ACERCA DE UM ELEMENTO DO SIMULADOR (ANIMAL OU ALIMENTO)
        if ( args.at(0) == "info") {
            if (verificaSintaxe(nArgs, 2)) {
                if (!verificaId(stoi(args.at(1)), reserva) ) {
                    infoToUser(janela1);
                    continue;
                }
                // info <id>
                checkId(int(stoi(args.at(1))), janela1 );
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // PASSAR PARA O INSTANTE SEGUINTE DA SIMULAÇÃO
        if ( args.at(0) == "n") {
            if (verificaSintaxe(nArgs, 1)) {
                // n
                tick(janela1);
                infoToUser(janela1);
                continue;
            }
            if (verificaSintaxe(nArgs, 2)) {
                // n <N>
                for(int i = 1; i < stoi(args.at(1)); ++i )
                    tick(janela1);
                infoToUser(janela1);
                continue;
            }
            if (verificaSintaxe(nArgs, 3)) {
                // n <N> <P>
                for(int i = 1; i < stoi(args.at(1)); ++i )
                    tick(5,janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // LISTAR ID DOS ANIMAIS NA RESERVA
        if (args.at(0) == "anim") {
            if (verificaSintaxe(nArgs, 1)) {
                // anim
                listIdsReserva(janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // LISTAR O ID DOS ANIMAIS NA AREA VISIVEL DA RESERVA
        if (args.at(0) == "visanim") {
            if (verificaSintaxe(nArgs, 1)) {
                // visanim
                listIdsWindow(janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // ARMAZENAR O ESTADO DA RESERVA EM MEMORIA
        if (args.at(0) == "store") {
            if (verificaSintaxe(nArgs, 2)) {
                // store <file>
                store(args.at(1),janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // REATIVAR UM ESTADO DA RESERVA PREVIAMENTE ARMAZENADO EM MEMORIA
        if (args.at(0) == "restore") {
            if (verificaSintaxe(nArgs, 2)) {
                // restore <file>
                restore(args.at(1),janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // CARREGAR E EXECUTAR COMANDOS A PARTIR DE UM FICHEIRO DE TEXTO
        if (args.at(0) == "load") {
            if (verificaSintaxe(nArgs, 2)) {
                // load <file>
                checkComandoUser(args.at(1), janela1, janela2);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // DESLOCAR A AREA DE VISUALIZAÇÃO
        if (args.at(0) == "slide") {
            if (verificaSintaxe(nArgs, 3)) {
                if ( !verificaDirecao(args.at(1),janela1) ) {
                    infoToUser(janela1);
                    continue;
                }
                // slide <direction> <linhas/colunas>
                deslocaAreaViz(args.at(1), stoi(args.at(2)), janela1);
                infoToUser(janela1);
                continue;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros\n";
                infoToUser(janela1);
                continue;
            }
        }
        // ENCERAR O SIMULADOR
        if (args.at(0) == "exit") {
            if (verificaSintaxe(nArgs, 1)){
                // exit
                return;
            } else {
                janela1 << term::move_to(0, 1) << "Erro! Numero errado de parametros";
                infoToUser(janela1);
                continue;
            }
        }
        // LISTAR OS COMANDOS POSSIVEIS
        if(args.at(0) == "help") {
            if(verificaSintaxe(nArgs, 1)){
                // help
                janela1 << term::move_to(0, 1) << "work in progress!" ;
            } else {
                janela1 << term::move_to(0, 1) << "erro! numero de argumentos invalido";
                infoToUser(janela1);
                continue;
            }
        }
//        escreve os argumentos no terminal
//        for (std::vector<std::string>::size_type i = 0; i != args.size(); ++i) {
//            std::cout << args.at(i) << std::endl;
//        }
    } while(true);
}
// abre o ficheiro comandos
void checkComandoUser(const string& nomeFicheiro, term::Window &janela1, term::Window &janela2) {
    string line;
    fstream myfile;
    myfile.open(nomeFicheiro, ios::in); // in = read mode, on = write mode
    if (myfile.is_open()) {
        janela1 << "Ficheiro aberto com sucesso!\n";
        while (getline(myfile, line)) {
            stringstream iss (line);
            string temp{};
            int nArgs = numArgs(iss, temp);
            vector<string> args = split(line);
            if ( args.at(0) == "animal") {
                if(verificaSintaxe(nArgs, 2)) {
                    criaAnimal(args.at(1)[0], janela1, janela2);
                    continue;
                }
                if(verificaSintaxe(nArgs, 4)) {
                    criaAnimal(args.at(1)[0], stoi(args.at(2)), stoi(args.at(3)),janela1, janela2);
                    continue;
                }
            }
            if ( args.at(0) == "kill") {
                killAnimal(int (stoi(args.at(1))), int (stoi(args.at(2))),janela1);
            }
            if ( args.at(0) == "killid") {
                killAnimal(stoi(args.at(1)),janela1);
            }
            if ( args.at(0) == "food") {
                if(verificaSintaxe(nArgs, 2)) {
                    placeAlimento(args.at(1)[0], janela1, janela2);
                    continue;
                }
                if(verificaSintaxe(nArgs, 4)) {
                    placeAlimento(args.at(1)[0], stoi(args.at(2)), stoi(args.at(3)), janela1, janela2);
                    continue;
                }
            }
        }
        myfile.close();
    }
    else {
        janela1 << "Erro a abrir o ficheiro!\n";
        return;
    }
}


/*
 // LER DO FICHEIRO
void checkComando() {
    fstream myfile;
    myfile.open("comandos.txt", ios::in); // read mode
    if (myfile.is_open()) {
        cout << "aberto\n";
        while (getline(myfile, line)) {
            cout << line << endl;
            break;
        }
        myfile.close();
    }
}
*/