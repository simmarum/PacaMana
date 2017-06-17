
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>


#include "map.h"
#include "wall.h"

using namespace glm;

Map::Map(colision_length &colision_length,std::vector <glm::vec3> &coin_position) {
    for(int i=0; i<WYSOKOSC_MAPY; i++) {
        for(int j=0; j<SZEROKOSC_MAPY; j++) {
            if(mapa[i][j]>=MAX_MODEL_ON_MAP) {
                fprintf(stderr,"Na mapie sa nie znane wartosci!\nX: %d Y:%d\nWartosc: %d",i,j,mapa[i][j]);
                exit(EXIT_FAILURE);
            }
            if(mapa[i][j] == mCOIN) {
                coin_position.push_back(vec3((float)i,0.75f,(float)j));
            }
        }
    }
    wall = new Wall(colision_length);
}

void Map::drawMapInConsole(bool simple) {
    for(int row = 0; row < WYSOKOSC_MAPY; row++) {
        printf("\n");
        for(int col = 0; col < SZEROKOSC_MAPY; col++) {
            if(simple) {
                switch(mapa[row][col]) {
                case mFLOR: {
                    printf("   ");
                    break;
                }
                case mPMAN: {
                    printf(" P ");
                    break;
                }
                case mWALL: {
                    printf(" # ");
                    break;
                }
                case mCOIN: {
                    printf(" O ");
                    break;
                }
                case mGHO1: {
                    printf(" 1 ");
                    break;
                }
                case mGHO2: {
                    printf(" 2 ");
                    break;
                }
                case mGHO3: {
                    printf(" 3 ");
                    break;
                }
                case mGHO4: {
                    printf(" 4 ");
                    break;
                }
                default: {
                    printf(" ? ");
                    break;
                }
                }
            } else {
                printf(" %d ", mapa[row][col]);
            }
        }
        printf("\n");
    }
}

Map::~Map() {
    TEMPvertices.clear();
    TEMPuvs.clear();
    TEMPnormals.clear();
}

void Map::drawSolid(GLuint &texWall,mat4 &V) {
    for(int i=0; i<WYSOKOSC_MAPY; i++) {
        for(int j=0; j<SZEROKOSC_MAPY; j++) {
            if(this->mapa[i][j] == 1) {
                wall->position = vec3((float)i,1.0,(float)j);
                wall->drawSolid(texWall,V);
                if(i==0 || j==0 || i==WYSOKOSC_MAPY-1 || j==SZEROKOSC_MAPY-1) { // rysowanie na okolo wyzszych scian
                    wall->position = vec3((float)i,2.0,(float)j);
                    wall->drawSolid(texWall,V);
                }
            }
        }
    }
}


