#include <stdio.h>
#include <move.h>

void rotateLEFT(Player *player) {
    player->rotation.y+=player->rotation_speed*glfwGetTime() - (float)2*PI*(floor(player->rotation_speed*glfwGetTime()/(2*PI))); //Oblicz przyrost k¹ta obrotu i zwiêksz aktualny k¹t
}
void rotateRIGHT(Player *player) {
    player->rotation.y+=(-player->rotation_speed)*glfwGetTime() - (float)2*PI*(floor((-player->rotation_speed)*glfwGetTime()/(2*PI))); //Oblicz przyrost k¹ta obrotu i zwiêksz aktualny k¹t
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
