#include <stdio.h>
#include <cstdlib>

#include "player.h"
#include "loaderOBJ.h"


#define mPlayer "modeleBlend/pacman.obj"

using namespace glm;

Player::Player(Map* &mapa)
{
    bool res = loadOBJ(mPlayer, this->TEMPvertices, this->TEMPuvs, this->TEMPnormals,this->TEMPvCount);
    if(!res)
    {
        printf("Nie uda³o siê wczytaæ!");
        exit(1);
    }
    position = vec3(1.0,1.0,1.0);
    rotation = vec3(0.0,0.0,0.0);
    scale = vec3(1.0,1.0,1.0);
    speed = 2;
    findPosition(mapa);
}

Player::~Player()
{
    TEMPvertices.clear();
    TEMPuvs.clear();
    TEMPnormals.clear();
}

void Player::findPosition(Map* &mapa)
{
    for(int i=0; i<WYSOKOSC_MAPY; i++)
    {
        for(int j=0; j<SZEROKOSC_MAPY; j++)
        {
            if(mapa->mapa[i][j] == 4)
            {
                this->position = vec3((float)i,0.75,(float)j);
            }
        }
    }
}


void Player::drawSolid(GLuint &tex,mat4 &V)
{
    glEnable(GL_NORMALIZE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D,tex);

    mat4 M=mat4(1.0f);
    M=translate(M,this->position);
    M=rotate(M,this->rotation.x,vec3(1.0,0.0,0.0));
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

void Player::colisionDetect(Map* &mapa)
{
    int px = (int)this->position.x;
    int pz = (int)this->position.z;
printf("Kolizja: x: %d oraz z: %d\n",px,pz);
    if(mapa->mapa[px+1][pz]==3 && px+1>=0 && px+1<WYSOKOSC_MAPY && pz>=0 && pz <SZEROKOSC_MAPY)
    {
        printf("Sciana 1\n");
    }
    if(mapa->mapa[px+1][pz+1]==3 && px+1>=0 && px+1<WYSOKOSC_MAPY && pz+1>=0 && pz+1 <SZEROKOSC_MAPY)
    {
        printf("Sciana 2\n");
    }
    if(mapa->mapa[px][pz+1]==3 && px>=0 && px<WYSOKOSC_MAPY && pz+1>=0 && pz+1 <SZEROKOSC_MAPY)
    {
        printf("Sciana 3\n");
    }
    if(mapa->mapa[px-1][pz+1]==3 && px-1>=0 && px-1<WYSOKOSC_MAPY && pz+1>=0 && pz+1 <SZEROKOSC_MAPY)
    {
        printf("Sciana 4\n");
    }
    if(mapa->mapa[px-1][pz]==3 && px-1>=0 && px-1<WYSOKOSC_MAPY && pz>=0 && pz <SZEROKOSC_MAPY)
    {
        printf("Sciana 5\n");
    }
    if(mapa->mapa[px-1][pz-1]==3 && px-1>=0 && px-1<WYSOKOSC_MAPY && pz-1>=0 && pz-1 <SZEROKOSC_MAPY)
    {
        printf("Sciana 6\n");
    }
    if(mapa->mapa[px][pz-1]==3 && px>=0 && px<WYSOKOSC_MAPY && pz-1>=0 && pz-1 <SZEROKOSC_MAPY)
    {
        printf("Sciana 7\n");
    }
    if(mapa->mapa[px+1][pz-1]==3 && px+1>=0 && px+1<WYSOKOSC_MAPY && pz-1>=0 && pz-1 <SZEROKOSC_MAPY)
    {
        printf("Sciana 8\n");
    }

}

