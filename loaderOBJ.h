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
**********************************
* Do funkcji w OpenGL'u potrzeba wskaŸników na typ float, a vector<float>,
* mo¿na to obejœæ prost¹ sztuczk¹ (przyk³ad):
* -> float* wierzcholki = &out_vertices[0];
*/

bool loadOBJ( const char * path,
              std::vector < float > & out_vertices,
              std::vector < float > & out_uvs,
              std::vector < float > & out_normals,
              unsigned int &vCount
            );

#endif // LOADEROBJ_H_INCLUDED
