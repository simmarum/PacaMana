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
        { mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL}, //  mFLOR - puste
        { mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL}, //  mWALL - œciana normalna
        { mWALL, mWALL, mWALL, mCOIN, mWALL, mWALL, mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mWALL, mWALL}, // 2 - pozycja Pacmana
        { mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL}, // 3 - Swtorek
        { mWALL, mCOIN, mWALL, mWALL, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mWALL},
        { mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mWALL, mFLOR, mFLOR, mWALL, mCOIN, mWALL, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL},
        { mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mWALL, mWALL, mCOIN, mWALL, mFLOR, mFLOR, mWALL, mCOIN, mCOIN, mCOIN, mCOIN, mWALL, mWALL, mWALL, mCOIN, mWALL},
        { mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mGHO4, mGHO3, mWALL, mCOIN, mWALL, mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL},
        { mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mGHO1, mGHO2, mWALL, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mWALL, mWALL},
        { mWALL, mWALL, mWALL, mWALL, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mWALL, mWALL, mWALL, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL},
        { mWALL, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL},
        { mWALL, mCOIN, mWALL, mWALL, mWALL, mCOIN, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL},
        { mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mWALL, mWALL},
        { mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mWALL, mWALL, mCOIN, mWALL, mWALL, mCOIN, mWALL, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL},
        { mWALL, mCOIN, mPMAN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mWALL},
        { mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mCOIN, mCOIN, mWALL, mCOIN, mWALL},
        { mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL}
    };
/*
 // TESTOWA MAPA DLA LATWOSCI DZIALANIA
    int mapa[WYSOKOSC_MAPY][SZEROKOSC_MAPY] = {
        { mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL}, //  mFLOR - puste
        { mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL}, //  mWALL - œciana normalna
        { mWALL, mWALL, mWALL, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL}, // 2 - pozycja Pacmana
        { mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL}, // 3 - Swtorek
        { mWALL, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mCOIN, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mCOIN, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL},
        { mWALL, mCOIN, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL},
        { mWALL, mCOIN, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL},
        { mWALL, mCOIN, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mWALL, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mCOIN, mPMAN, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL},
        { mWALL, mFLOR, mFLOR, mWALL, mWALL, mFLOR, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mWALL, mWALL},
        { mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mWALL, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL},
        { mWALL, mGHO4, mGHO3, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mGHO1, mGHO2, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mFLOR, mFLOR, mWALL, mFLOR, mWALL},
        { mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL, mWALL}
    };*/


private:
    Wall *wall;
};

#endif // MAP_H_INCLUDED
