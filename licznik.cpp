#include <stdio.h>
#include <cstdlib>

#include "licznik.h"
#include "loaderOBJ.h"

#define mLicznik "modeleBlend/licznik.obj"

using namespace glm;

Licznik::Licznik(colision_length &colision_length) {
    bool res = loadOBJ(mLicznik, this->TEMPvertices, this->TEMPuvs, this->TEMPnormals,this->TEMPvCount,colision_length);
    if(!res) {
        fprintf(stderr,"Nie udało się wczytać!");
        exit(1);
    }
    position = vec3(1.0,1.0,1.0);
    rotation = vec3(0.0,0.0,0.0);
    rotation2 = vec3(0.0,0.0,0.0);
    scale = vec3(0.5,0.5,0.5);
    speed = 0.0;
    zgory = false;
    smooth_rotX = 2.0f;
}

Licznik::~Licznik() {
    TEMPvertices.clear();
    TEMPuvs.clear();
    TEMPnormals.clear();
}

void Licznik::drawAll(GLuint &tex,mat4 &V,vec3 licznik_1_pos,vec3 licznik_2_pos,int number_coin) {
    int d=9,j=9;
    if(number_coin > 99) {
        d=9;
        j=9;
    } else {
        j=number_coin%10;
        d=number_coin/10;
    }
    this->position = licznik_1_pos;
    if(this->zgory) this->end_rotationX1 = (j-2)*(36.0f*PI/180.0f);
    else this->end_rotationX1 = j*(36.0f*PI/180.0f);
    float add_rot = (this->end_rotationX1-this->rotation.x)/this->smooth_rotX;
   // printf("END: %f %f %f %f %f %f\n",(this->end_rotationX1-this->rotation.x),this->smooth_rotX,add_rot,this->end_rotationX1,this->rotation.x,fabs(this->rotation.x + add_rot - this->end_rotationX1));
    if(fabs(this->rotation.x + add_rot - this->end_rotationX1)>0.01) this->rotation.x += add_rot;
    printf("R1: %f\n",this->rotation.x);
    drawSolid(tex,V);
    this->position = licznik_2_pos;
    if(this->zgory) this->end_rotationX2 = (d-2)*(36.0f*PI/180.0f);
    else  this->end_rotationX2 = d*(36.0f*PI/180.0f);
    add_rot = (this->end_rotationX2-this->rotation2.x)/this->smooth_rotX;
    if(fabs(this->rotation2.x + add_rot - this->end_rotationX2)>0.01) this->rotation2.x += add_rot;
    //this->rotation.x = this->rotation2.x;
    printf("R2: %f\n",this->rotation2.x);
    drawSolid_2(tex,V);
}

void Licznik::drawSolid(GLuint &tex,mat4 &V) {
    glEnable(GL_NORMALIZE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D,tex);
    glShadeModel(GL_SMOOTH);
    mat4 M=mat4(1.0f);
    M=translate(M,this->position);
    M=rotate(M,this->rotation.y,vec3(0.0f,1.0f,0.0f));
    M=rotate(M,this->rotation.z,vec3(0.0f,0.0f,1.0f));
    M=rotate(M,this->rotation.x,vec3(1.0f,0.0f,0.0f));
    M=glm::scale(M,this->scale);
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

void Licznik::drawSolid_2(GLuint &tex,mat4 &V) {
    glEnable(GL_NORMALIZE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D,tex);
    glShadeModel(GL_SMOOTH);
    mat4 M=mat4(1.0f);
    M=translate(M,this->position);
    M=rotate(M,this->rotation.y,vec3(0.0f,1.0f,0.0f));
    M=rotate(M,this->rotation.z,vec3(0.0f,0.0f,1.0f));
    M=rotate(M,this->rotation2.x,vec3(1.0f,0.0f,0.0f));
    M=glm::scale(M,this->scale);
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
