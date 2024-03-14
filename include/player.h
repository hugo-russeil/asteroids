#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"

#include "gameEntity.h"

typedef struct {
    GameEntity base;
    float rotation;
    float rotationSpeed;
}Player;

extern Player player;

Player createPlayer(Vector2 position);
void inputPlayer(Player* player);
void movePlayer(Player* player);
void rotatePlayer(Player* player);
bool checkCollisionPlayer(Player* player, Vector2 position, float radius);
void shootPlayer(Player* player);
void updatePlayer(Player* player);
void drawPlayer(Player* player);


#endif // PLAYER_H