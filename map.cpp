
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>


#include "map.h"
#include "wall.h"

using namespace glm;

Map::Map()
{
    for(int i=0; i<WYSOKOSC_MAPY; i++)
    {
        for(int j=0; j<SZEROKOSC_MAPY; j++)
        {
            mapa[i][j]=mapaOriginal[i][j];
        }
    }
    mapaScian.clear();
    vec3 tempPosition;
    for(int i=0; i<WYSOKOSC_MAPY; i++)
    {
        for(int j=0; j<SZEROKOSC_MAPY; j++)
        {
            if(this->mapa[i][j] == 1)
            {
                Wall *wall = new Wall();
                wall->position = vec3((float)i,1.0,(float)j);
                mapaScian.push_back(wall);
            }
            if(this->mapa[i][j] == 3)
            {
                Wall *wall1 = new Wall();
                wall1->position = vec3((float)i,1.0,(float)j);
                mapaScian.push_back(wall1);
                Wall *wall2 = new Wall();
                wall2->position = vec3((float)i,2.0,(float)j);
                mapaScian.push_back(wall2);
                Wall *wall3 = new Wall();
                wall3->position = vec3((float)i,3.0,(float)j);
                mapaScian.push_back(wall3);
            }
        }
    }
}

void Map::drawMapInConsole()
{
    for(int row = 0; row < WYSOKOSC_MAPY; row++)
    {
        printf("\n");
        for(int col = 0; col < SZEROKOSC_MAPY; col++)
        {
            printf("%d ", mapa[row][col]);
        }
    }
}

Map::~Map()
{
    TEMPvertices.clear();
    TEMPuvs.clear();
    TEMPnormals.clear();
}

void Map::drawSolid(GLuint &texWall,mat4 &V)
{

    for(int i=0; i<mapaScian.size(); i++)
    {
        mapaScian[i]->drawSolid(texWall,V);
    }
}

void Map::drawElem(GLuint &tex,mat4 &V,vec3 &position)
{
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


