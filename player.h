#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "model.h"
#include "map.h"

class Player: public Model {
public:
    Player(Map* &mapa,colision_length &colision_length);
    ~Player();
    void drawSolid(GLuint &tex,mat4 &V);
    void WallDetect(Map* &mapa,colision_length colision_table[]);

    std::vector< float > TEMPvertices2;
    std::vector< float > TEMPuvs2;
    std::vector< float > TEMPnormals2;
    unsigned int TEMPvCount2;
    vec3 position2;
    vec3 rotation2;
    vec3 scale2;
    float speed2;
private:
    float rotation_temp;
    void findPosition(Map* &mapa);
    void drawSolid_1(GLuint &tex,mat4 &V);
    void drawSolid_2(GLuint &tex,mat4 &V);
};

#endif // PLAYER_H_INCLUDED
