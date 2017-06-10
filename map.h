#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "wall.h"
#include "constants.h"

class Map {

public:
    Map(colision_length &colision_length,std::vector <glm::vec3> &coin_position);
    ~Map();

    void drawSolid(GLuint &texWall, mat4 &V);
    void drawMapInConsole(bool simple);

    std::vector< float > TEMPvertices;
    std::vector< float > TEMPuvs;
    std::vector< float > TEMPnormals;

    unsigned int TEMPvCount;

    int mapa[WYSOKOSC_MAPY][SZEROKOSC_MAPY] = {
        {mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL}, //  mFLOR - puste
        { mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL}, //  mWALL - œciana normalna
        { mWALL, mWALL, mWALL, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL}, // 2 - pozycja Pacmana
        { mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL}, // 3 - Swtorek
        { mWALL, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL},
        { mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL},
        { mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL},
        { mWALL, mWALL, mWALL, mWALL, mWALL, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mWALL, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL},
        { mWALL, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL},
        { mWALL, mFLOR, mCOIN, mFLOR, mWALL, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL},
        { mWALL, mCOIN, mPMAN, mCOIN, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mFLOR, mCOIN, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL}
    };

private:
    void drawElem(GLuint &texWall,mat4 &V,vec3 &position);
    Wall *wall;
};

#endif // MAP_H_INCLUDED
