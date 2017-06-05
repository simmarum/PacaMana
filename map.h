#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "wall.h"
#include "constants.h"

class Map {
public:
    Map(colision_length &colision_length);
    ~Map();
    void drawSolid(GLuint &texWall, mat4 &V);
    void drawMapInConsole();
    std::vector< float > TEMPvertices;
    std::vector< float > TEMPuvs;
    std::vector< float > TEMPnormals;
    unsigned int TEMPvCount;

    int mapa[WYSOKOSC_MAPY][SZEROKOSC_MAPY];

private:
    void drawElem(GLuint &texWall,mat4 &V,vec3 &position);
    std::vector< Wall*> mapaScian;
    Wall *wall;
    int mapaOriginal[WYSOKOSC_MAPY][SZEROKOSC_MAPY] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 0 - puste
        {1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1}, // 1 - œciana normalna
        {1,1,1,0,1,1,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1}, // 2 - pozycja Pacmana
        {1,0,1,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,0,0,1}, // 3 - Swtorek
        {1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {1,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,1},
        {1,0,1,0,0,0,1,1,1,0,1,0,1,0,0,0,0,0,1,1,1,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,1,0,0,0,1},
        {1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,1,1},
        {1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1},
        {1,0,0,0,1,0,1,1,1,0,1,1,0,1,1,0,1,0,1,0,0,0,1},
        {1,0,3,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
};

#endif // MAP_H_INCLUDED
