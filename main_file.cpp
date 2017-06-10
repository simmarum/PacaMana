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
#include "struct_cosilion.h"
#include "allmodels.h"

#include "move.h"
#include "loaderOBJ.h"
#include <string>

#define szerokoscOkna 500
#define wysokoscOkna 500

// tekstury dla obiektow
#define twall "tekstury/wood.png"
#define tfloor "tekstury/floor.png"
#define tplayer "tekstury/pacman.png"

// definicja klawiszy (latwa zmiana sterowania w kodzie)
#define kup  GLFW_KEY_W
#define kdown  GLFW_KEY_S
#define kleft  GLFW_KEY_A
#define kright  GLFW_KEY_D
#define klook_back  GLFW_KEY_J

// asocjacja klawiszy z indeksami dla tablicy klawiszy...
#define nop 0
#define up  1
#define down  2
#define left  3
#define right  4
#define look_back 5

using namespace glm;

// tablica kolizji (aby nie trzymiac wymiarow w poszczegolnych obiektach tylko ogolnie dla danego typu obiektu
colision_length colision_table[MAX_MODEL_ON_MAP];

// potrzbne modele
Floor *podloga = new Floor(colision_table[mFLOR]);
Map *mapa = new Map(colision_table[mWALL]);
Player *player = new Player(mapa,colision_table[mPMAN]);


float aspect=1.0f; //Aktualny stosunek szerokości do wysokości okna
float speed_y=0; //Szybkość kątowa obrotu obiektu w radianach na sekundę wokół osi y
float camera_far = 1.3; // odleglosc kamery (promiec okregu po ktorym porusza sie kamera wokol PacMana)
float camera_angle = 0.4; // odleglosc camery nad PacManem w osi Y

// tablica dla kawiszy (aby pamietac jakie byly i bezproblemowo robic kombinajce klawiszy)
bool keys[32];

// definicja uchwytow na tekstury
GLuint texSciana;
GLuint texPodloga;
GLuint texPlayer;


//Procedura obsługi błędów
void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

//Procedura obługi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Obraz ma być generowany w oknie o tej rozdzielczości
    ///(u nas ma byc staly!)
    aspect=(float)szerokoscOkna/(float)wysokoscOkna; //Stosunek szerokości do wysokości okna
}

// funkcja ktora powoduje ruch w kazdym kierunku (po skosie dwa klawisze tez) ogolnie od klawiszy jest
void doMove(Map* &mapa,colision_length colision_table[]) {
    if (keys[up]) goSRTAIGHT(player,mapa,colision_table); // do przodu
    if (keys[down]) goBACK(player); // do tylu
    if (!keys[right]) rotateSTOP(speed_y); // zatrzymanie obrotu w prawo
    if (!keys[left]) rotateSTOP(speed_y);// zatrzymanie oborotu w lewo
    if (keys[right]) rotateRIGHT(speed_y); // obrot w prawo
    if (keys[left]) rotateLEFT(speed_y); // obrot w lewo

    if (keys[left] && keys[up]) { // po skosie gora/lewo
        rotateLEFT(speed_y);
        goSRTAIGHT(player,mapa,colision_table);
    }
    if (keys[left] && keys[down]) { // po skosie dol/lewo
        rotateRIGHT(speed_y);
        goBACK(player);
    }
    if (keys[right] && keys[up]) { // po skosie gora/prawo
        rotateRIGHT(speed_y);
        goSRTAIGHT(player,mapa,colision_table);
    }
    if (keys[right] && keys[down]) { // po skosie dol/prawo
        rotateLEFT(speed_y);
        goBACK(player);
    }
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        if(key == kleft) keys[left]=true;
        if(key == kright) keys[right]=true;
        if(key == kup) keys[up]=true;
        if(key == kdown) keys[down]=true;
        if(key == klook_back) keys[look_back]=true;
    }
printf("PLAYER: X=%f Y=%f Z=%f\n",player->position.x,player->position.y,player->position.z);
    if (action == GLFW_RELEASE) {
        if(key == kleft) keys[left]=false;
        if(key == kright) keys[right]=false;
        if(key == kup) keys[up]=false;
        if(key == kdown) keys[down]=false;
        if(key == klook_back) keys[look_back]=false;
    }
}

// inicjalizacja swiatla na mapie
void LetItBeLight() {
    GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // otoczenia
    GLfloat diffuseLight[] = { 0.4f, 0.4f, 0.4, 1.0f }; // rozproszenia
    GLfloat specularLight[] = { 0.7f, 0.7f, 0.7f, 1.0f }; // odbicia
    GLfloat position0[] = { 2.0f, 2.0f, -2.0f, 1.0f }; // pozycja za pacmanem po prawej
    GLfloat position1[] = { -2.0, 2.0f, -2.0f, 1.0f }; // pozycja za pacmanem po lewej

    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
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
}

void wczytajObraz(GLuint &tex, std::string path) {
    std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazka
    unsigned width, height; //Zmienne do których wczytamy wymiary obrazka
    unsigned error = lodepng::decode(image, width, height, path);
    if(error != 0) {
        printf("%s\n",lodepng_error_text(error)); // wypisanie bledu jak cos nie pojdzie
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
void initOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedurę obsługi zmiany rozdzielczości bufora ramki
    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury

    LetItBeLight(); // swiatlo
    glEnable(GL_COLOR_MATERIAL); // wlaczenie kolorow w opengl
    glEnable(GL_DEPTH_TEST); //Włącz używanie budora głębokości

    /// - > Wczytaj obrazek - sciana
    wczytajObraz(texSciana,twall);

    /// - > Wczytaj obrazek - podloga
    wczytajObraz(texPodloga,tfloor);

    /// - > Wczytaj obrazek - player
    wczytajObraz(texPlayer,tplayer);

}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
    //************Tutaj umieszczaj kod rysujący obraz******************l

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyść bufor kolorów (czyli przygotuj "płótno" do rysowania)

    //***Przygotowanie do rysowania****
    mat4 P=perspective(35.0f*PI/180.0f,aspect,1.0f,30.0f); //Wylicz macierz rzutowania P
    mat4 V; // macierz widoku
    if(!keys[look_back]){ /// widok do przodu
    V=lookAt( //Wylicz macierz widoku
               vec3(player->position.x-camera_far*cos(player->rotation.y),
                    player->position.y+camera_angle,
                    player->position.z+camera_far*sin(player->rotation.y)),
               vec3(player->position.x+camera_far*cos(player->rotation.y),
                    player->position.y+0.3,
                    player->position.z-camera_far*sin(player->rotation.y)),
               vec3(0.0f,1.0f,0.0f));
    } else { /// widok do tylu
      V=lookAt( //Wylicz macierz widoku
               vec3(player->position.x+camera_far*cos(player->rotation.y),
                    player->position.y+camera_angle,
                    player->position.z-camera_far*sin(player->rotation.y)),
               vec3(player->position.x-camera_far*cos(player->rotation.y),
                    player->position.y+0.3,
                    player->position.z+camera_far*sin(player->rotation.y)),
               vec3(0.0f,1.0f,0.0f));
    }
    glMatrixMode(GL_PROJECTION); //Włącz tryb modyfikacji macierzy rzutowania
    glLoadMatrixf(value_ptr(P)); //Załaduj macierz rzutowania
    glMatrixMode(GL_MODELVIEW);  //Włącz tryb modyfikacji macierzy model-widok

    podloga->drawSolid(texPodloga,V);
    mapa->drawSolid(texSciana,V);
    player->drawSolid(texPlayer,V);


    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}

//usuwanie obiektow
void usunObiekty(){
delete player;
delete mapa;
delete podloga;
}

int main(void) {
    mapa->drawMapInConsole();

    GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

    glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

    if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(szerokoscOkna, wysokoscOkna, "Paca-Mana", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window) { //Jeżeli okna nie udało się utworzyć, to zamknij program
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
    glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    GLenum err;
    if ((err=glewInit()) != GLEW_OK) { //Zainicjuj bibliotekę GLEW
        fprintf(stderr, "Nie można zainicjować GLEW: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram(window); //Operacje inicjujące

    glfwSetTime(0); //Wyzeruj timer

    //Główna pętla
    while (!glfwWindowShouldClose(window)) { //Tak długo jak okno nie powinno zostać zamknięte
        doMove(mapa,colision_table);
        player->rotation.y+=speed_y*glfwGetTime(); //Oblicz przyrost kąta obrotu i zwiększ aktualny kąt
        glfwSetTime(0); //Wyzeruj timer
        drawScene(window); //Wykonaj procedurę rysującą
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }

    //Usuniecie obiektow
    usunObiekty();

    //Usunięcie tekstury z pamięci karty graficznej – po głownej pętli
    glDeleteTextures(1,&texSciana);
    glDeleteTextures(1,&texPodloga);
    glDeleteTextures(1,&texPlayer);
    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
}
