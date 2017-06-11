#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "player.h"
#include "ghost.h"

void rotateLEFT(Player *player);
void rotateRIGHT(Player *player);
void goSTRAIGHT(Player *player, Map* &mapa, colision_length colision_table[],std::vector <glm::vec3> &coin_position);
void goBACK(Player *player, Map* &mapa, colision_length colision_table[],std::vector <glm::vec3> &coin_position);

void rotateGhostLEFT(Ghost *ghost);
void rotateGhostRIGHT(Ghost *ghost);
void goGhostSTRAIGHT(Ghost *ghost, Map* &mapa, colision_length colision_table[], int id);
void goGhostBACK(Ghost *ghost, Map* &mapa, colision_length colision_table[], int id);

#endif // MOVE_H_INCLUDED
