#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "model.h"
#include "map.h"

class Ghost: public Model {
public:
    Ghost(Map* &mapa,colision_length &colision_length,int id);
    ~Ghost();
    void drawSolid(GLuint &tex,mat4 &V);
    void WallDetect(Map* &mapa, colision_length colision_table[], int id);

    float rotation_speed;

    std::vector< float > TEMPvertices2;
    std::vector< float > TEMPuvs2;
    std::vector< float > TEMPnormals2;
    unsigned int TEMPvCount2;
    vec3 position2;
    vec3 rotation2;
    vec3 scale2;
    float speed2;
    void doGhostMove(Map* &mapa, colision_length colision_table[]);
private:
    float rotation_temp;
    int ID;
    int oldPX;
    int oldPZ;
    int counter;
    int przemieszczenieID;
    void findPosition(Map* &mapa,int id);
    void drawSolid_1(GLuint &tex,mat4 &V);
    void drawSolid_2(GLuint &tex,mat4 &V);
};


#endif // GHOST_H_INCLUDED
