/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <lodepng.h>
#include "constants.h"
#include "allmodels.h"


#include "loaderOBJ.h"
#include <string>

#define twall "tekstury/test.png"
using namespace glm;

float aspect=1.0f; //Aktualny stosunek szerokości do wysokości okna
float speed_x=0; //Szybkość kątowa obrotu obiektu w radianach na sekundę wokół osi x
float speed_y=0; //Szybkość kątowa obrotu obiektu w radianach na sekundę wokół osi y
GLuint tex;
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

Wall *sciana = new Wall();
// Read our .obj file
std::vector< float > TEMPvertices;
std::vector< float > TEMPuvs;
std::vector< float > TEMPnormals; // Won't be used at the moment.
std::vector< float > TEMPcolor;
unsigned int TEMPvCount;

void wypiszvector(std::vector <float> name,char c[],int modulo){
    printf("\n%s\n",c);
for(int i=0;i<name.size();i++){
        if(i%modulo == 0) printf("\n");
        if(i%(modulo*modulo)==0) printf("%d\n",i/(modulo*modulo));
    printf("%f\t",name[i]);
}
}

//Procedura obsługi błędów
void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

//Procedura obługi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); //Obraz ma być generowany w oknie o tej rozdzielczości
    aspect=(float)width/(float)height; //Stosunek szerokości do wysokości okna
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_LEFT) speed_y=PI/2;
        if (key == GLFW_KEY_RIGHT) speed_y=-PI/2;
        if (key == GLFW_KEY_UP) speed_x=PI/2;
        if (key == GLFW_KEY_DOWN) speed_x=-PI/2;
    }

    if (action == GLFW_RELEASE)
    {
        if (key == GLFW_KEY_LEFT) speed_y=0;
        if (key == GLFW_KEY_RIGHT) speed_y=0;
        if (key == GLFW_KEY_UP) speed_x=0;
        if (key == GLFW_KEY_DOWN) speed_x=0;
    }
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window)
{
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedurę obsługi zmiany rozdzielczości bufora ramki
    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury

    glClearColor(0,0,0,1); //Ustaw kolor czyszczenia ekranu
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING); //Włącz tryb cieniowania
    glEnable(GL_LIGHT0); //Włącz zerowe źródło światła
    glEnable(GL_DEPTH_TEST); //Włącz używanie budora głębokości
    //glEnable(GL_COLOR_MATERIAL); //Włącz śledzenie kolorów przez materiał

    //Wczytanie i import obrazka – w initOpenGLProgram
    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazka
    unsigned width, height; //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, twall);
    if(error != 0) {
            printf("%s\n",lodepng_error_text(error));
            exit(1);
    }

    //Import do pamięci karty graficznej
    glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

    //Bilinear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

  //  bool res = loadOBJ("modeleBlend/wall.obj", TEMPvertices, TEMPuvs, TEMPnormals,TEMPvCount);
	//if(!res) {
  //      printf("Nie udało się wczytać!");
//	}
	printf("koniec\n");
    wypiszvector(TEMPvertices,"verticies",3);
    wypiszvector(TEMPuvs,"uvs",2);
    wypiszvector(TEMPnormals,"normal",3);

}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window,float angle_x,float angle_y)
{
    //************Tutaj umieszczaj kod rysujący obraz******************l

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyść bufor kolorów (czyli przygotuj "płótno" do rysowania)

    //***Przygotowanie do rysowania****
    mat4 P=perspective(50.0f*PI/180.0f,aspect,1.0f,50.0f); //Wylicz macierz rzutowania P
    mat4 V=lookAt( //Wylicz macierz widoku
               vec3(0.0f,0.0f,-5.0f),
               vec3(0.0f,0.0f,0.0f),
               vec3(0.0f,1.0f,0.0f));
    glMatrixMode(GL_PROJECTION); //Włącz tryb modyfikacji macierzy rzutowania
    glLoadMatrixf(value_ptr(P)); //Załaduj macierz rzutowania
    glMatrixMode(GL_MODELVIEW);  //Włącz tryb modyfikacji macierzy model-widok

    /// TEST WCZYTYWANIA Z OBJ



    //Rysowanie kostki
    //1. Wyliczenie i załadowanie macierzy modelu
    mat4 M=mat4(1.0f);
    M=rotate(M,angle_x,vec3(1.0f,0.0f,0.0f));
    M=rotate(M,angle_y,vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M));

    sciana->drawSolid(tex);


    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}

int main(void)
{
    GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

    glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

    if (!glfwInit())   //Zainicjuj bibliotekę GLFW
    {
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
    glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    GLenum err;
    if ((err=glewInit()) != GLEW_OK)   //Zainicjuj bibliotekę GLEW
    {
        fprintf(stderr, "Nie można zainicjować GLEW: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram(window); //Operacje inicjujące


    float angle_x=0.0f; //Aktualny kąt obrotu obiektu wokół osi x
    float angle_y=0.0f; //Aktualny kąt obrotu obiektu wokół osi y
    glfwSetTime(0); //Wyzeruj timer

    //Główna pętla
    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
    {
        angle_x+=speed_x*glfwGetTime(); //Oblicz przyrost kąta obrotu i zwiększ aktualny kąt
        angle_y+=speed_y*glfwGetTime(); //Oblicz przyrost kąta obrotu i zwiększ aktualny kąt
        glfwSetTime(0); //Wyzeruj timer
        drawScene(window,angle_x,angle_y); //Wykonaj procedurę rysującą
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }
    //Usunięcie tekstury z pamięci karty graficznej – po głownej pętli
    glDeleteTextures(1,&tex);
    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
}
