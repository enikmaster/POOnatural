#ifndef TRABALHOPRATICO_CONSTANTES_H
#define TRABALHOPRATICO_CONSTANTES_H
// valores iniciais dos animais
namespace constantes {
    inline int sCoelho;
    inline int vCoelho;
    inline int pCoelho;
    inline int sOvelha;
    inline int vOvelha;
    inline int pOvelha;
    inline int sLobo;
    inline int vLobo;
    inline int pLobo;
    inline int sCanguru;
    inline int vCanguru;
    inline int pCanguru;
    inline int sMacaco;
    inline int vMacaco;
    inline int pMacaco;
    inline int sHumano;
    inline int vHumano;
    inline int pHumano;
}
class Constantes {
public:
    Constantes() {getFromFile();};
    //setters
    void setSCoelho(int valor) {constantes::sCoelho = valor;}
    void setVCoelho(int valor) {constantes::vCoelho = valor;}
    void setPCoelho(int valor) {constantes::pCoelho = valor;}
    void setSOvelha(int valor) {constantes::sOvelha = valor;}
    void setVOvelha(int valor) {constantes::vOvelha = valor;}
    void setPOvelha(int valor) {constantes::pOvelha = valor;}
    void setSLobo(int valor) {constantes::sLobo = valor;}
    void setVLobo(int valor) {constantes::vLobo = valor;}
    void setPLobo(int valor) {constantes::pLobo = valor;}
    void setSCanguru(int valor) {constantes::sCanguru = valor;}
    void setVCanguru(int valor) {constantes::vCanguru = valor;}
    void setPCanguru(int valor) {constantes::pCanguru = valor;}
    void setSMacaco(int valor) {constantes::sMacaco = valor;}
    void setVMacaco(int valor) {constantes::vMacaco = valor;}
    void setPMacaco(int valor) {constantes::pMacaco = valor;}
    void setSHumano(int valor) {constantes::sHumano = valor;}
    void setVHumano(int valor) {constantes::vHumano = valor;}
    void setPHumano(int valor) {constantes::pHumano = valor;}
    // actions
    void getFromFile();
};
#endif //TRABALHOPRATICO_CONSTANTES_H
