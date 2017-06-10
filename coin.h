
#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "model.h"
#include "map.h"

class Coin: public Model {
public:
    Coin(Map* &mapa,colision_length &colision_length);
    ~Coin();
    void drawSolid(GLuint &tex,mat4 &V);
private:
    void findPosition(Map* &mapa);

};

#endif // COIN_H_INCLUDED
