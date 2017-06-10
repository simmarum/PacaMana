#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED

#include "model.h"

class Floor: public Model {
public:
    Floor(colision_length &colision_length);
    ~Floor();
    void drawSolid(GLuint &tex,mat4 &V);
};

#endif // FLOOR_H_INCLUDED
