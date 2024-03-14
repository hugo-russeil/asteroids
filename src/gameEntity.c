#include "gameEntity.h"
#include "raylib.h"
#include "raymath.h"

bool checkCollision(GameEntity* entity1, GameEntity* entity2){
    if(!entity1->active || !entity2->active) return false;
    return CheckCollisionRecs(entity1->hitbox, entity2->hitbox);
}
