#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float rotationSpeed;
}Player;

Player createPlayer(Vector2 position);
void inputPlayer(Player* player);
void movePlayer(Player* player);
void rotatePlayer(Player* player);
bool checkCollisionPlayer(Player* player, Vector2 position, float radius);
void shootPlayer(Player* player);
void updatePlayer(Player* player);
void drawPlayer(Player* player);


#endif // PLAYER_H