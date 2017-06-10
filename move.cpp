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
void goSTRAIGHT(Player *player, Map* &mapa, colision_length colision_table[],std::vector <glm::vec3> &coin_position) {
    player->position.x += cos(player->rotation.y)*player->speed*glfwGetTime(); // ruch x
    player->position.z -= sin(player->rotation.y)*player->speed*glfwGetTime(); // ruch z
    player->WallDetect(mapa,colision_table); // wykrycie kolizji
    player->CoinDetect(colision_table,coin_position);
}
void goBACK(Player *player, Map* &mapa, colision_length colision_table[],std::vector <glm::vec3> &coin_position) {
    player->position.x -= cos(player->rotation.y)*player->speed*glfwGetTime(); // ruch x
    player->position.z += sin(player->rotation.y)*player->speed*glfwGetTime(); // ruch z
    player->WallDetect(mapa,colision_table); // wykrycie kolizji
    player->CoinDetect(colision_table,coin_position);
}
