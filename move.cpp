#include <stdio.h>
#include <move.h>

void rotateSTOP(float &speed) {
    speed=0.0;
}
void rotateLEFT(float &speed) {
    speed=PI/2;
}
void rotateRIGHT(float &speed) {
    speed=-PI/2;
}
void goSRTAIGHT(Player *player,Map* &mapa,colision_length colision_table[]) {
    float oldX = player->position.x;
    float oldZ = player->position.z;
    player->position.x += cos(player->rotation.y)*player->speed*glfwGetTime();
    player->position.z -= sin(player->rotation.y)*player->speed*glfwGetTime();
    int col = player->colisionDetect(mapa,colision_table);
    printf("ZDERZENIE: = %d\n",col);
    if(((col & 1) == 1) || ((col & 16) == 16)) {
        player->position.x = oldX;
    } else if(((col & 2) == 2) || ((col & 128) == 128)) {
        player->position.x = oldX;
        player->position.z = oldZ;
    }
    if(((col & 4) == 4) || ((col & 64) == 64)) {
        player->position.z = oldZ;
    }



}
void goBACK(Player *player) {
    player->position.x -= cos(player->rotation.y)*player->speed*glfwGetTime();
    player->position.z += sin(player->rotation.y)*player->speed*glfwGetTime();
}
