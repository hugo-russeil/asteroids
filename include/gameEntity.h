#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "raylib.h"

typedef struct{
    Vector2 position;
    Vector2 velocity;
    Rectangle hitbox;
    bool active;
}GameEntity;

bool checkCollision(GameEntity* entity1, GameEntity* entity2);

#endif // GAME_ENTITY_H