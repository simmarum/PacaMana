/*

Niniejszy program jest wolnym oprogramowaniem; mo¿esz go
rozprowadzaæ dalej i / lub modyfikowaæ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - wed³ug wersji 2 tej Licencji lub(wed³ug twojego
wyboru) którejœ z póŸniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej¹, i¿ bêdzie on
u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyœlnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŒLONYCH
ZASTOSOWAÑ.W celu uzyskania bli¿szych informacji siêgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoœci¹ wraz z niniejszym programem otrzyma³eœ te¿ egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeœli nie - napisz do Free Software Foundation, Inc., 59 Temple
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
#include "struct.h"
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
#define tcoin "tekstury/coin.png"

// definicja klawiszy (latwa zmiana sterowania w kodzie)

#define kup  GLFW_KEY_W
#define kdown  GLFW_KEY_S
#define kleft  GLFW_KEY_A
#define kright  GLFW_KEY_D
#define klook_back  GLFW_KEY_J

#define K_CAMERA_PACMAN GLFW_KEY_1
#define K_CAMERA_UP GLFW_KEY_2

#define KEY_SECOND true
#define K_UP_SECOND GLFW_KEY_UP
#define K_DOWN_SECOND GLFW_KEY_DOWN
#define K_RIGHT_SECOND GLFW_KEY_RIGHT
#define K_LEFT_SECOND GLFW_KEY_LEFT

// asocjacja klawiszy z indeksami dla tablicy klawiszy...
#define nop 0
#define up  1
#define down  2
#define left  3
#define right  4
#define look_back 5

bool CAMERA_PACMAN = true;

using namespace glm;



// tablica kolizji (aby nie trzymiac wymiarow w poszczegolnych obiektach tylko ogolnie dla danego typu obiektu
colision_length colision_table[MAX_MODEL_ON_MAP];
std::vector <glm::vec3> coin_position;
// potrzbne modele
Floor *podloga = new Floor(colision_table[mFLOR]);
Map *mapa = new Map(colision_table[mWALL],coin_position);
Player *player = new Player(mapa, colision_table[mPMAN]);
Coin *coin = new Coin(colision_table[mCOIN]);

float aspect=1.0f; //Aktualny stosunek szerokoœci do wysokoœci okna
float speed_y=0; //Szybkoœæ k¹towa obrotu obiektu w radianach na sekundê wokó³ osi y
float camera_far = 1.3; // odleglosc kamery (promiec okregu po ktorym porusza sie kamera wokol PacMana)
float camera_angle = 0.4; // odleglosc camery nad PacManem w osi Y

// tablica dla kawiszy (aby pamietac jakie byly i bezproblemowo robic kombinajce klawiszy)
bool keys[32];

// definicja uchwytow na tekstury
GLuint texSciana;
GLuint texPodloga;
GLuint texPlayer;
GLuint texCoin;

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
    if(keys[up]) goSTRAIGHT(player,mapa,colision_table);  // do przodu
    if(keys[down]) goBACK(player, mapa, colision_table);  // do tylu
    if(!keys[right]) rotateSTOP(speed_y);  // zatrzymanie obrotu w prawo
    if(!keys[left]) rotateSTOP(speed_y); // zatrzymanie oborotu w lewo
    if(keys[right]) rotateRIGHT(speed_y);  // obrot w prawo
    if(keys[left]) rotateLEFT(speed_y);  // obrot w lewo
    if(keys[left] && keys[up]) {  // po skosie gora/lewo
        rotateLEFT(speed_y);
        goSTRAIGHT(player,mapa,colision_table);
    }
    if(keys[left] && keys[down]) {  // po skosie dol/lewo
        rotateRIGHT(speed_y);
        goBACK(player, mapa, colision_table);
    }
    if(keys[right] && keys[up]) {  // po skosie gora/prawo
        rotateRIGHT(speed_y);
        goSTRAIGHT(player,mapa,colision_table);
    }
    if(keys[right] && keys[down]) {  // po skosie dol/prawo
        rotateLEFT(speed_y);
        goBACK(player, mapa, colision_table);
    }
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        if(key == kleft) keys[left] = true;
        if(key == kright) keys[right] = true;
        if(key == kup) keys[up] = true;
        if(key == kdown) keys[down] = true;
        if(key == klook_back) keys[look_back] = true;
        if(key == K_CAMERA_PACMAN) CAMERA_PACMAN = true;
        if(key == K_CAMERA_UP) CAMERA_PACMAN = false;
        if(KEY_SECOND) {
            if(key == K_LEFT_SECOND) keys[left] = true;
            if(key == K_RIGHT_SECOND) keys[right] = true;
            if(key == K_UP_SECOND) keys[up] = true;
            if(key == K_DOWN_SECOND) keys[down] = true;
        }
    }
    if(action == GLFW_RELEASE) {
        if(key == kleft) keys[left] = false;
        if(key == kright) keys[right] = false;
        if(key == kup) keys[up] = false;
        if(key == kdown) keys[down] = false;
        if(key == klook_back) keys[look_back] = false;
        if(KEY_SECOND) {
            if(key == K_LEFT_SECOND) keys[left] = false;
            if(key == K_RIGHT_SECOND) keys[right] = false;
            if(key == K_UP_SECOND) keys[up] = false;
            if(key == K_DOWN_SECOND) keys[down] = false;
        }
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
    //Import do pamiêci karty graficznej
    glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
    //Bilinear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
}

//Procedura inicjuj¹ca
void initOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który nale¿y wykonaæ raz, na pocz¹tku programu************
    glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedurê obs³ugi zmiany rozdzielczoœci bufora ramki
    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurê obs³ugi klawiatury
    LetItBeLight(); // swiatlo
    glEnable(GL_COLOR_MATERIAL); // wlaczenie kolorow w opengl
    glEnable(GL_DEPTH_TEST); //W³¹cz u¿ywanie budora g³êbokoœci
    /// - > Wczytaj obrazek - sciana
    wczytajObraz(texSciana,twall);
    /// - > Wczytaj obrazek - podloga
    wczytajObraz(texPodloga,tfloor);
    /// - > Wczytaj obrazek - player
    wczytajObraz(texPlayer,tplayer);
    /// -> Wczytaj obrazek - coin
    wczytajObraz(texCoin, tcoin);
}

//Procedura rysuj¹ca zawartoœæ sceny
void drawScene(GLFWwindow* window) {
    //************Tutaj umieszczaj kod rysuj¹cy obraz******************l
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyœæ bufor kolorów (czyli przygotuj "p³ótno" do rysowania)
    //***Przygotowanie do rysowania****
    mat4 P=perspective(35.0f*PI/180.0f,aspect,1.0f,30.0f); //Wylicz macierz rzutowania P
    mat4 V; // macierz widoku
    if(CAMERA_PACMAN && !keys[look_back]) { /// widok do przodu
        V=lookAt( //Wylicz macierz widoku
              vec3(player->position.x-camera_far*cos(player->rotation.y),
                   player->position.y+camera_angle,
                   player->position.z+camera_far*sin(player->rotation.y)),
              vec3(player->position.x+camera_far*cos(player->rotation.y),
                   player->position.y+0.3,
                   player->position.z-camera_far*sin(player->rotation.y)),
              vec3(0.0f,1.0f,0.0f));
    } else if(!CAMERA_PACMAN) { /// widok z góry
        V=lookAt(
              vec3(player->position.x - camera_far*cos(player->rotation.y),
                   player->position.y + 10,
                   player->position.z + camera_far*sin(player->rotation.y)),
              vec3(player->position.x,
                   player->position.y,
                   player->position.z),
              vec3(0.0f,1.0f,0.0f));
    } else { /// widok do tyłu
        V=lookAt( //Wylicz macierz widoku
              vec3(player->position.x+camera_far*cos(player->rotation.y),
                   player->position.y+camera_angle,
                   player->position.z-camera_far*sin(player->rotation.y)),
              vec3(player->position.x-camera_far*cos(player->rotation.y),
                   player->position.y+0.3,
                   player->position.z+camera_far*sin(player->rotation.y)),
              vec3(0.0f,1.0f,0.0f));
    }
    glMatrixMode(GL_PROJECTION); //W³¹cz tryb modyfikacji macierzy rzutowania
    glLoadMatrixf(value_ptr(P)); //Za³aduj macierz rzutowania
    glMatrixMode(GL_MODELVIEW);  //W³¹cz tryb modyfikacji macierzy model-widok
    podloga->drawSolid(texPodloga,V);
    mapa->drawSolid(texSciana,V);
    player->drawSolid(texPlayer,V);
    coin->drawAll(texCoin,V,coin_position);
    glfwSwapBuffers(window); //Przerzuæ tylny bufor na przedni
}

//usuwanie obiektow
void usunObiekty() {
    delete player;
    delete mapa;
    delete podloga;
    delete coin;
}

int main(void) {
    mapa->drawMapInConsole(true);
    GLFWwindow* window; //WskaŸnik na obiekt reprezentuj¹cy okno
    glfwSetErrorCallback(error_callback);//Zarejestruj procedurê obs³ugi b³êdów
    if(!glfwInit()) {  //Zainicjuj bibliotekê GLFW
        fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(szerokoscOkna, wysokoscOkna, "Paca-Mana", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.
    if(!window) {  //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
    glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora
    GLenum err;
    if((err=glewInit()) != GLEW_OK) {  //Zainicjuj bibliotekê GLEW
        fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    initOpenGLProgram(window); //Operacje inicjuj¹ce
    glfwSetTime(0); //Wyzeruj timer
    //G³ówna pêtla
    while(!glfwWindowShouldClose(window)) {  //Tak d³ugo jak okno nie powinno zostaæ zamkniête
        doMove(mapa, colision_table);
        player->rotation.y+=speed_y*glfwGetTime() - (float)2*PI*(floor(speed_y*glfwGetTime()/(2*PI))); //Oblicz przyrost k¹ta obrotu i zwiêksz aktualny k¹t
        glfwSetTime(0); //Wyzeruj timer
        drawScene(window); //Wykonaj procedurê rysuj¹c¹
        glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
    }
    //Usuniecie obiektow
    usunObiekty();
    //Usuniêcie tekstury z pamiêci karty graficznej – po g³ownej pêtli
    glDeleteTextures(1,&texSciana);
    glDeleteTextures(1,&texPodloga);
    glDeleteTextures(1,&texPlayer);
    glDeleteTextures(1,&texCoin);
    glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
    exit(EXIT_SUCCESS);
}

