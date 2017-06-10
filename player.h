#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "model.h"
#include "map.h"

class Player: public Model {
public:
    Player(Map* &mapa,colision_length &colision_length);
    ~Player();
    void drawSolid(GLuint &tex,mat4 &V);
    void colisionDetect(Map* &mapa,colision_length colision_table[]);
private:
    void findPosition(Map* &mapa);

};

#endif // PLAYER_H_INCLUDED
