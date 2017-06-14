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

void rotateGhostLEFT(Ghost *ghost) {
    ghost->rotation_temp = ghost->rotation.y;
    ghost->rotation_temp += (float)(ghost->rotation_speed*glfwGetTime());
    ghost->rotation_temp = (float)(ghost->rotation_temp - 2*PI*(ceil(ghost->rotation_temp/(2*PI))));
    ghost->rotation.y = ghost->rotation_temp;
}
void rotateGhostRIGHT(Ghost *ghost) {
    ghost->rotation_temp -= (float)(ghost->rotation_speed*glfwGetTime());
    ghost->rotation_temp = (float)(ghost->rotation_temp - 2*PI*(ceil(ghost->rotation_temp/(2*PI))));
    ghost->rotation.y = ghost->rotation_temp;
}
void goGhostSTRAIGHT(Ghost *ghost, Map* &mapa, colision_length colision_table[]) {
    ghost->position.x += cos(ghost->rotation.y)*ghost->speed*glfwGetTime(); // ruch x
    ghost->position.z -= sin(ghost->rotation.y)*ghost->speed*glfwGetTime(); // ruch z
    ghost->WallDetect(mapa, colision_table); // wykrycie kolizji
}
void goGhostBACK(Ghost *ghost, Map* &mapa, colision_length colision_table[]) {
    ghost->position.x -= cos(ghost->rotation.y)*ghost->speed*glfwGetTime(); // ruch x
    ghost->position.z += sin(ghost->rotation.y)*ghost->speed*glfwGetTime(); // ruch z
    ghost->WallDetect(mapa,colision_table); // wykrycie kolizji
}
