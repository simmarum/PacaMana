#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "player.h"

void rotateLEFT(Player *player);
void rotateRIGHT(Player *player);
void goSTRAIGHT(Player *player, Map* &mapa, colision_length colision_table[],std::vector <glm::vec3> &coin_position);
void goBACK(Player *player, Map* &mapa, colision_length colision_table[],std::vector <glm::vec3> &coin_position);

#endif // MOVE_H_INCLUDED
