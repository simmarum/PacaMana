#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "model.h"

class Player: public Model
{
public:
    Player();
    ~Player();
    void drawSolid(GLuint &tex,mat4 &V);
};

#endif // PLAYER_H_INCLUDED
