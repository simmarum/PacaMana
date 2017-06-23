#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED

#include "model.h"

class Info: public Model {
public:
    Info(colision_length &colision_length);
    ~Info();
    void drawSolid(GLuint &tex,mat4 &V);
};


#endif // WALL_H_INCLUDED
