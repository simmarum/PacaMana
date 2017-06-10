
#include <stdio.h>
#include <cstdlib>

#include "coin.h"
#include "loaderOBJ.h"

#define mCoinModel "modeleBlend/coin.obj"

using namespace glm;

Coin::Coin(colision_length &colision_length) {
    bool res = loadOBJ(mCoinModel, this->TEMPvertices, this->TEMPuvs, this->TEMPnormals,this->TEMPvCount,colision_length);
    if(!res) {
        printf("Nie udało się wczytać!");
        exit(1);
    }
    position = vec3(1.0,1.0,1.0);
    rotation = vec3(0.0,0.0,0.0);
    scale = vec3(1.0,1.0,1.0);
    speed = 1;
    rotation_temp = rotation.y;
}

Coin::~Coin() {
    TEMPvertices.clear();
    TEMPuvs.clear();
    TEMPnormals.clear();
}


void Coin::drawAll(GLuint &tex,mat4 &V,std::vector <glm::vec3> &coin_position){
    for (int i=0;i<coin_position.size();i++){
        this->position = coin_position[i];
        drawSolid(tex,V);
    }
}
void Coin::drawSolid(GLuint &tex,mat4 &V) {
    glEnable(GL_NORMALIZE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D,tex);

    mat4 M=mat4(1.0f);
    M=translate(M,this->position);
    this->rotation_temp += (float) (glfwGetTime()*speed);
    this->rotation_temp = (float) (this->rotation_temp - 2*PI*(ceil(this->rotation_temp/(2*PI))));
    this->rotation.y = this->rotation_temp;
    M=rotate(M,this->rotation.y,vec3(0.0,1.0,0.0));
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
