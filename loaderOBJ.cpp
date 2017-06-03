/*
*   Autor: Mateusz Kruszyna
*/

#include <string>
#include "loaderOBJ.h"

bool loadOBJ( const char * path,
              std::vector < float > & out_vertices,
              std::vector < float > & out_uvs,
              std::vector < float > & out_normals,
              unsigned int &vCount
            )
{
    vCount = 0;
    std::vector < unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector < float > temp_vertices;
    std::vector < float > temp_uvs;
    std::vector < float > temp_normals;

    FILE * file = fopen(path, "r");
    if( file == NULL )
    {
        printf("Can't read file! %s\n",path);
        return false;
    }
    while( 1 )
    {

        char lineHeader[512];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        if ( strcmp( lineHeader, "v" ) == 0 )
        {
            float x;
            float y;
            float z;
            fscanf(file, "%f %f %f\n", &x, &y, &z );
            temp_vertices.push_back(x);
            temp_vertices.push_back(-z);
            temp_vertices.push_back(y);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 )
        {
            float uvx;
            float uvy;
            fscanf(file, "%f %f\n", &uvx, &uvy );
            temp_uvs.push_back(uvx);
            temp_uvs.push_back(1-uvy);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            float nx;
            float ny;
            float nz;
            fscanf(file, "%f %f %f\n", &nx, &ny, &nz );
            temp_normals.push_back(nx);
            temp_normals.push_back(-nz);
            temp_normals.push_back(ny);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9)
            {
                printf("Wrong file format! Try with another options! \n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    vCount = vertexIndices.size();
    for( unsigned int i=0; i<vertexIndices.size(); i++ )
    {
        unsigned int vertexIndex = 3*(vertexIndices[i]-1);
        float vertex = temp_vertices[ vertexIndex ];
        out_vertices.push_back(vertex);
        vertex = temp_vertices[ vertexIndex+1];
        out_vertices.push_back(vertex);
        vertex = temp_vertices[ vertexIndex+2 ];
        out_vertices.push_back(vertex);
    }
        for( unsigned int i=0; i<normalIndices.size(); i++ )
    {
        unsigned int normalIndex = 3*(normalIndices[i]-1);
        float normal = temp_normals[ normalIndex ];
        out_normals.push_back(normal);
        normal = temp_normals[ normalIndex+1 ];
        out_normals.push_back(normal);
        normal = temp_normals[ normalIndex+2 ];
        out_normals.push_back(normal);
    }
        for( unsigned int i=0; i<uvIndices.size(); i++ )
    {
        unsigned int uvIndex = 2*(uvIndices[i]-1);
        float uv = temp_uvs[ uvIndex ];
        out_uvs.push_back(uv);
        uv = temp_uvs[ uvIndex+1 ];
        out_uvs.push_back(uv);
    }
}
