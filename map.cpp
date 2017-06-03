
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "map.h"

using namespace glm;

Map::Map()
{
    printf("Konstruktor mapy!");
}

void Map::drawMapInConsole(bool simple) {
    for(int row = 0; row < WYSOKOSC_MAPY; row++) {
        printf("\n");
        for(int col = 0; col < SZEROKOSC_MAPY; col++) {
            if(simple) {
                switch(mapa[row][col]) {
                case 4: {
                    printf(" X ");
                    break;
                } case 2: {
                    printf(" B ");
                    break;
                } case 1: {
                    printf(" # ");
                    break;
                } case 3: {
                    printf(" # ");
                    break;
                } default: {
                    printf("   ");
                    break;
                }
                }
            } else {
                printf(" %d ", mapa[row][col]);
            }
        }
    }
}

Map::~Map()
{
    TEMPvertices.clear();
    TEMPuvs.clear();
    TEMPnormals.clear();
    position = vec3(0.0,0.0,0.0);
    rotation = vec3(0.0,0.0,0.0);
    scale = vec3(1.0,1.0,1.0);
    speed = 0.0;
}

void Map::drawSolid(GLuint &tex,mat4 &V)
{
    vec3 positionTemp;
    int width = 15;
    int depth = 15;
    for(int i=0;i<width;i++){
        for(int j=0;j<depth;j++){
            positionTemp.x = (float)i;
            positionTemp.y = 0.0;
            positionTemp.z = (float)j;
            drawElem(tex,V,positionTemp);
        }
    }
}

void Map::drawElem(GLuint &tex,mat4 &V,vec3 &position){
glEnable(GL_NORMALIZE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D,tex);

    mat4 M=mat4(1.0f);
    M=translate(M,position);
    glLoadMatrixf(value_ptr(V*M));

    glVertexPointer(3,GL_FLOAT,0,&(this->TEMPvertices[0]));
    glNormalPointer(GL_FLOAT,sizeof(float)*3,&(this->TEMPnormals[0]));
    glTexCoordPointer(2,GL_FLOAT,0,&(this->TEMPuvs[0]));

    float ambient[] = {0,0,0,1};
    float emision[] = {0,0,0,1};
    float diffuse[] = {0.7,0.5,0.5,1};
    float specular[] = {0.5,0.5,0.5,1};
    float shininess = 50;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glDrawArrays(GL_TRIANGLES,0,this->TEMPvCount);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

