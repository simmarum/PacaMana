#include <stdio.h>
#include <cstdlib>

#include "player.h"
#include "loaderOBJ.h"


#define mPlayer "modeleBlend/pacman.obj"

using namespace glm;

Player::Player(Map* &mapa,colision_length &colision_length) {
    bool res = loadOBJ(mPlayer, this->TEMPvertices, this->TEMPuvs, this->TEMPnormals,this->TEMPvCount,colision_length);
    if(!res) {
        printf("Nie uda³o siê wczytaæ!");
        exit(1);
    }
    position = vec3(1.0,1.0,1.0);
    rotation = vec3(0.0,0.0,0.0);
    scale = vec3(1.0,1.0,1.0);
    speed = 2;
    findPosition(mapa);
}

Player::~Player() {
    TEMPvertices.clear();
    TEMPuvs.clear();
    TEMPnormals.clear();
}

void Player::findPosition(Map* &mapa) {
    for(int i=0; i<WYSOKOSC_MAPY; i++) {
        for(int j=0; j<SZEROKOSC_MAPY; j++) {
            if(mapa->mapa[i][j] == 3) {
                this->position = vec3((float)i,0.75,(float)j);
            }
        }
    }
}


void Player::drawSolid(GLuint &tex,mat4 &V) {
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

int Player::colisionDetect(Map* &mapa,colision_length colision_table[]) {

    int px = (int)(this->position.x+0.5f);
    int pz = (int)(this->position.z+0.5f);
    int wynik = 0;

    if(mapa->mapa[px+1][pz]==1 && px+1>=0 && px+1<WYSOKOSC_MAPY && pz>=0 && pz <SZEROKOSC_MAPY) {
        printf("Sciana 1\n");
        if(colision_table[mapa->mapa[px+1][pz]].toX + colision_table[2].toX
                >= fabs((px+1)-this->position.x)) {
            printf("Zderzenie sciana 1\n");
            wynik +=1;
        }
    }
    if(mapa->mapa[px+1][pz+1]==1 && px+1>=0 && px+1<WYSOKOSC_MAPY && pz+1>=0 && pz+1 <SZEROKOSC_MAPY) {
        printf("Sciana 2\n");
        if(colision_table[mapa->mapa[px+1][pz]].toX + colision_table[2].toX
                >= fabs((px+1)-this->position.x)
                && colision_table[mapa->mapa[px+1][pz]].toZ + colision_table[2].toZ
                >= fabs((pz+1)-this->position.z)) {
            printf("Zderzenie sciana 2\n");
            wynik +=2;
        }
    }
    if(mapa->mapa[px][pz+1]==1 && px>=0 && px<WYSOKOSC_MAPY && pz+1>=0 && pz+1 <SZEROKOSC_MAPY) {
        printf("Sciana 4\n");
        if(colision_table[mapa->mapa[px][pz+1]].toZ + colision_table[2].toZ
                >= fabs((pz+1)-this->position.z)) {
            printf("Zderzenie sciana 4\n");
            wynik +=4;
        }
    }
    if(mapa->mapa[px-1][pz+1]==1 && px-1>=0 && px-1<WYSOKOSC_MAPY && pz+1>=0 && pz+1 <SZEROKOSC_MAPY) {
        printf("Sciana 8\n");
        if(colision_table[mapa->mapa[px-1][pz+1]].toX + colision_table[2].toX
                >= fabs((px-1)-this->position.x)
                && colision_table[mapa->mapa[px-1][pz+1]].toZ + colision_table[2].toZ
                >= fabs((pz+1)-this->position.z)) {
            printf("Zderzenie sciana 8\n");
            wynik +=8;
        }
    }
    if(mapa->mapa[px-1][pz]==1 && px-1>=0 && px-1<WYSOKOSC_MAPY && pz>=0 && pz <SZEROKOSC_MAPY) {
        printf("Sciana 16\n");
        if(colision_table[mapa->mapa[px-1][pz]].toX + colision_table[2].toX
                >= fabs((px-1)-this->position.x)) {
            printf("Zderzenie sciana 16\n");
            wynik +=16;
        }
    }
    if(mapa->mapa[px-1][pz-1]==1 && px-1>=0 && px-1<WYSOKOSC_MAPY && pz-1>=0 && pz-1 <SZEROKOSC_MAPY) {
        printf("Sciana 32\n");
        if(colision_table[mapa->mapa[px-1][pz-1]].toX + colision_table[2].toX
                >= fabs((px-1)-this->position.x)
                && colision_table[mapa->mapa[px-1][pz-1]].toZ + colision_table[2].toZ
                >= fabs((pz-1)-this->position.z)) {
            printf("Zderzenie sciana 32\n");
            wynik +=32;
        }
    }
    if(mapa->mapa[px][pz-1]==1 && px>=0 && px<WYSOKOSC_MAPY && pz-1>=0 && pz-1 <SZEROKOSC_MAPY) {
        printf("Sciana 64\n");
        if(colision_table[mapa->mapa[px][pz-1]].toZ + colision_table[2].toZ
                >= fabs((pz-1)-this->position.z)) {
            printf("Zderzenie sciana 64\n");
            wynik +=64;
        }
    }
    if(mapa->mapa[px+1][pz-1]==1 && px+1>=0 && px+1<WYSOKOSC_MAPY && pz-1>=0 && pz-1 <SZEROKOSC_MAPY) {
        printf("Sciana 128\n");
        if(colision_table[mapa->mapa[px+1][pz-1]].toX + colision_table[2].toX
                >= fabs((px+1)-this->position.x)
                && colision_table[mapa->mapa[px+1][pz-1]].toZ + colision_table[2].toZ
                >= fabs((pz-1)-this->position.z)) {
            printf("Zderzenie sciana 128\n");
            wynik +=182;
        }
    }
    return wynik;
}

