#ifndef INC_03_LEARN_LOCAL_H
#define INC_03_LEARN_LOCAL_H

using namespace std;
class Local {
public:
    Local(int o, int lx, int ly) : ocupaId(o), localX(lx), localY(ly) {}
    ~Local() {}
    // getters
    int getOcupaId() const {return ocupaId;}
    int getLocalX() const {return localX;}
    int getLocalY() const {return localY;}
    // setters
    void setOcupaId(int newId) {this->ocupaId = newId;}
    void setLocalX(int newLocalX) {this->localX = newLocalX;}
    void setLocalY(int newLocalY) {this->localX = newLocalY;}
private:
    int ocupaId;
    int localX;
    int localY;
};

#endif //INC_03_LEARN_LOCAL_H
