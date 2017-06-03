#include <move.h>

void rotateSTOP(float &speed){
speed=0.0;
}
void rotateLEFT(float &speed){
speed=PI/2;
}
void rotateRIGHT(float &speed){
speed=-PI/2;
}
void goSRTAIGHT(Player *player){
player->position.x += cos(player->rotation.y)*player->speed*glfwGetTime();
            player->position.z -= sin(player->rotation.y)*player->speed*glfwGetTime();
}
void goBACK(Player *player){
 player->position.x -= cos(player->rotation.y)*player->speed*glfwGetTime();
            player->position.z += sin(player->rotation.y)*player->speed*glfwGetTime();
}
