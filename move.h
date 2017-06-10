#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "player.h"

void rotateSTOP(float &speed);
void rotateLEFT(float &speed);
void rotateRIGHT(float &speed);
void goSTRAIGHT(Player *player, Map* &mapa, colision_length colision_table[]);
void goBACK(Player *player, Map* &mapa, colision_length colision_table[]);

#endif // MOVE_H_INCLUDED
