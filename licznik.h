#ifndef LICZNIK_H_INCLUDED
#define LICZNIK_H_INCLUDED


#include "model.h"

class Licznik: public Model {
public:
    Licznik(colision_length &colision_length);
    ~Licznik();
    void drawAll(GLuint &tex,mat4 &V,vec3 licznik_1_pos,vec3 licznik_2_pos,vec3 licznik_3_pos,int number_coin);
    void drawSolid(GLuint &tex,mat4 &V);
    void drawSolid_2(GLuint &tex,mat4 &V);
    void drawSolid_3(GLuint &tex,mat4 &V);
    bool zgory;
    vec3 rotation2;
    vec3 rotation3;
private:
    float end_rotationX1;
    float end_rotationX2;
    float end_rotationX3;
    float smooth_rotX;
};


#endif // LICZNIK_H_INCLUDED
