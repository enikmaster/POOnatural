#ifndef TRABALHOPRATICO_CONSTANTES_H
#define TRABALHOPRATICO_CONSTANTES_H
// valores iniciais dos animais
namespace constantes {
    extern int sCoelho;
    extern int vCoelho;
    extern int pCoelho;
    extern int sOvelha;
    extern int vOvelha;
    extern int pOvelha;
    extern int sLobo;
    extern int vLobo;
    extern int pLobo;
    extern int sCanguru;
    extern int vCanguru;
    extern int pCanguru;
    extern int sMacaco;
    extern int vMacaco;
    extern int pMacaco;
    extern int sHumano;
    extern int vHumano;
    extern int pHumano;
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
