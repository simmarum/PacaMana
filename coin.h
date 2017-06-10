
#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "model.h"
#include "map.h"

class Coin: public Model {
public:
    Coin(colision_length &colision_length);
    ~Coin();
    void drawAll(GLuint &tex,mat4 &V,std::vector <glm::vec3> &coin_position);
    void drawSolid(GLuint &tex,mat4 &V);
private:
    float rotation_temp;
};
#endif // COIN_H_INCLUDED
