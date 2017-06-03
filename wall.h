#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "model.h"

class Wall: public Model
{
public:
    Wall();
    ~Wall();
    void drawSolid(GLuint tex);
};


#endif // WALL_H_INCLUDED
