/*
*   Autor: Mateusz Kruszyna
*/

#ifndef LOADEROBJ_H_INCLUDED
#define LOADEROBJ_H_INCLUDED

#include <vector>
/*
* Funckja do wczytywanie formatu OBJ z blendera do OpenGL'a za pomocą funckji 'gl_drawArray'.
* (Jeden model na plik!)
* Ważne aby przy exporcie w blenderze zaznaczyć tylko poniższe opcje:
*   -Apply Modifiers
*   -Write Normals
*   -Include UVs
*   -Triangulate Faces
**********************************
* Parametry funkcji:
*   - const char * path -> ściezka do pliku
*   - std::vector < float > & out_vertices -> wektor wierzchołków
*   - std::vector < float > & out_uvs -> wektor wektorów teksturowania
*   - std::vector < float > & out_normals -> wektor wektorów normalnych
*   - unsigned int &vCount -> liczba wierzchołków
**********************************
* Do funkcji w OpenGL'u potrzeba wskaźników na typ float, a vector<float>,
* można to obejść prostą sztuczką (przykład):
* -> &out_vertices[0];
*/

bool loadOBJ( const char * path,
              std::vector < float > & out_vertices,
              std::vector < float > & out_uvs,
              std::vector < float > & out_normals,
              unsigned int &vCount
            );

#endif // LOADEROBJ_H_INCLUDED
