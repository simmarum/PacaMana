/*
*   Autor: Mateusz Kruszyna
*/

#ifndef LOADEROBJ_H_INCLUDED
#define LOADEROBJ_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include "struct.h"
/*
* Funckja do wczytywanie formatu OBJ z blendera do OpenGL'a za pomoc¹ funckji 'gl_drawArray'.
* (Jeden model na plik!)
* Wa¿ne aby przy exporcie w blenderze zaznaczyæ tylko poni¿sze opcje:
*   -Apply Modifiers
*   -Write Normals
*   -Include UVs
*   -Triangulate Faces
**********************************
* Parametry funkcji:
*   - const char * path -> œciezka do pliku
*   - std::vector < float > & out_vertices -> wektor wierzcho³ków
*   - std::vector < float > & out_uvs -> wektor wektorów teksturowania
*   - std::vector < float > & out_normals -> wektor wektorów normalnych
*   - unsigned int &vCount -> liczba wierzcho³ków
*   - colision_length &colision_length -> struktura zawierająca wymiary do wspomagania wykrywania kolizji
*                       *> float toX -> wymiar na osi X (maxX - minX)/2
*                       *> float toZ -> wymiar na osi Z (maxZ - minZ)/2
*                       *> float radius -> wymiar po przekątnej (promien kola)
**********************************
* Do funkcji w OpenGL'u potrzeba wskaŸników na typ float, a vector<float>,
* mo¿na to obejœæ prost¹ sztuczk¹ (przyk³ad):
* -> float* wierzcholki = &out_vertices[0];
*/

bool loadOBJ(const char * path,
             std::vector < float > & out_vertices,
             std::vector < float > & out_uvs,
             std::vector < float > & out_normals,
             unsigned int &vCount,
             colision_length &colision_length
            );
void wypiszvector(std::vector <float> name,char c[],int modulo);

#endif // LOADEROBJ_H_INCLUDED
