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
#include <string>
#include "constants.h"
#include "allmodels.h"

#include "move.h"
#include "loaderOBJ.h"
#include <string>

#define twall "tekstury/crate.png"
#define tfloor "tekstury/floor.png"
#define tplayer "tekstury/pacman.png"

#define kup  GLFW_KEY_W
#define kdown  GLFW_KEY_S
#define kleft  GLFW_KEY_A
#define kright  GLFW_KEY_D

#define up  0
#define down  1
#define left  2
#define right  3

using namespace glm;


Wall *sciana = new Wall();
Floor *podloga = new Floor();
Player *player = new Player();
Map *mapa = new Map();

float aspect=1.0f; //Aktualny stosunek szerokości do wysokości okna
float speed_zero= 0.0f;
float speed_y=0; //Szybkość kątowa obrotu obiektu w radianach na sekundę wokół osi y
float camera_speed=0.05;
float camera_far = 4;
vec3 camera = vec3(player->position.x-3.6,player->position.y+1.6,player->position.z-3.6);
vec3 look = vec3(0.0,0.0,0.0);

bool keys[32]= {false};

GLuint texSciana;
GLuint texPodloga;
GLuint texPlayer;


// Read our .obj file
std::vector< float > TEMPvertices;
std::vector< float > TEMPuvs;
std::vector< float > TEMPnormals; // Won't be used at the moment.
std::vector< float > TEMPcolor;
unsigned int TEMPvCount;

void wypiszvector(std::vector <float> name,char c[],int modulo)
{
    printf("\n%s\n",c);
    for(int i=0; i<name.size(); i++)
    {
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
void doMove()
{
    if (keys[left]) rotateLEFT(speed_y);
    if (!keys[left]) rotateSTOP(speed_y);
    if (keys[right]) rotateRIGHT(speed_y);
    if (!keys[right]) rotateSTOP(speed_y);
    if (keys[up]) goSRTAIGHT(player);
    if (keys[down]) goBACK(player);

    if (keys[left] && keys[up]){
        rotateLEFT(speed_y);
        goSRTAIGHT(player);
    }
    if (keys[left] && keys[down]){
        rotateLEFT(speed_y);
        goBACK(player);
    }
    if (keys[right] && keys[up]){
        rotateRIGHT(speed_y);
        goSRTAIGHT(player);
    }
    if (keys[right] && keys[down]){
        rotateRIGHT(speed_y);(speed_y);
        goBACK(player);
    }
}
//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS){
        if(key == kleft) keys[left]=true;
        if(key == kright) keys[right]=true;
        if(key == kup) keys[up]=true;
        if(key == kdown) keys[down]=true;
    }
    printf("CAMERA: X=%f Y=%f Z=%f\n",camera.x,camera.y,camera.z);
    printf("player: X=%f Y=%f Z=%f\n",player->position.x,player->position.y,player->position.z);

    if (action == GLFW_RELEASE)
    {
        if(key == kleft) keys[left]=false;
        if(key == kright) keys[right]=false;
        if(key == kup) keys[up]=false;
        if(key == kdown) keys[down]=false;
    }
}
void LetItBeLight()
{
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position0[] = { -2.0f, 2.0f, -2.0f, 1.0f };
    GLfloat position1[] = { -2.0f, 2.0f, 2.0f, 1.0f };
    GLfloat position2[] = { 2.0f, 2.0f, -2.0f, 1.0f };
    GLfloat position3[] = { 2.0f, 2.0f, 2.0f, 1.0f };
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position0);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);

    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT2, GL_POSITION, position2);

    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT3, GL_POSITION, position3);

}

void wczytajObraz(GLuint &tex, std::string path){
    std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazka
    unsigned width, height; //Zmienne do których wczytamy wymiary obrazka
    unsigned error = lodepng::decode(image, width, height, path);
    if(error != 0)
    {
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
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window)
{
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedurę obsługi zmiany rozdzielczości bufora ramki
    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury

    LetItBeLight(); // swiatlo

    glEnable(GL_DEPTH_TEST); //Włącz używanie budora głębokości

    /// - > Wczytaj obrazek - sciana
    wczytajObraz(texSciana,twall);

    /// - > Wczytaj obrazek - podloga
    wczytajObraz(texPodloga,tfloor);

   /// - > Wczytaj obrazek - player
    wczytajObraz(texPlayer,tplayer);

}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle_y)
{
    //************Tutaj umieszczaj kod rysujący obraz******************l

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyść bufor kolorów (czyli przygotuj "płótno" do rysowania)

    //***Przygotowanie do rysowania****
    mat4 P=perspective(50.0f*PI/180.0f,aspect,1.0f,50.0f); //Wylicz macierz rzutowania P
    mat4 V=lookAt( //Wylicz macierz widoku
               vec3(player->position.x-camera_far*cos(player->rotation.y),
                    player->position.y+1.0,
                    player->position.z+camera_far*sin(player->rotation.y)),
               vec3(player->position.x,player->position.y,player->position.z),
               vec3(0.0f,1.0f,0.0f));
    glMatrixMode(GL_PROJECTION); //Włącz tryb modyfikacji macierzy rzutowania
    glLoadMatrixf(value_ptr(P)); //Załaduj macierz rzutowania
    glMatrixMode(GL_MODELVIEW);  //Włącz tryb modyfikacji macierzy model-widok

    player->drawSolid(texPlayer,V);
    podloga->drawSolid(texPodloga,V);


    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}

int main(void)
{
	mapa->drawMapInConsole();
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
    glfwSetTime(0); //Wyzeruj timer

    //Główna pętla
    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
    {
        doMove();
        player->rotation.y+=speed_y*glfwGetTime(); //Oblicz przyrost kąta obrotu i zwiększ aktualny kąt
        glfwSetTime(0); //Wyzeruj timer
        drawScene(window,angle_y); //Wykonaj procedurę rysującą
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }
    //Usunięcie tekstury z pamięci karty graficznej – po głownej pętli
    glDeleteTextures(1,&texSciana);
    glDeleteTextures(1,&texPodloga);
    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
}