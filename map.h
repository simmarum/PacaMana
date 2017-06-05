#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "wall.h"
#include "constants.h"

class Map
{
public:
    Map();
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

         int mapaOriginal[WYSOKOSC_MAPY][SZEROKOSC_MAPY] =
    {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // 0 - puste
        {3,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,3}, // 1 - œciana normalna
        {3,1,1,0,1,1,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,3}, // 2 - wyjœcie dla stworków
        {3,0,1,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,0,0,3}, // 3 - œciana zewnêtrzna
        {3,0,1,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,3}, // 4 - pozycja Pacmana
        {3,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,3},
        {3,0,1,0,0,0,1,1,1,0,1,0,1,0,0,0,0,0,1,1,1,0,3},
        {3,0,1,0,1,0,1,0,2,0,1,0,1,1,0,1,1,0,1,0,0,0,3},
        {3,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,1,3},
        {3,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,3},
        {3,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,3},
        {3,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,3},
        {3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,3},
        {3,0,0,0,1,0,1,1,1,0,1,1,0,1,1,0,1,0,1,0,0,0,3},
        {3,4,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,3},
        {3,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
    };
};

#endif // MAP_H_INCLUDED
