#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

#include "gameEntity.h"

#define MAX_BULLETS 10

typedef struct{
    GameEntity base;
    bool owner; // The owner of the bullet, true for player, false for enemy
} Bullet;

extern Bullet bullets[MAX_BULLETS];

Bullet createBullet(Vector2 position, Vector2 velocity, bool owner);
void addBullet(Vector2 position, Vector2 velocity, bool owner);
bool checkCollisionBullet(Bullet* bullet, Vector2 position, float radius);
void updateBullet(Bullet* bullet);
void drawBullet(Bullet bullet);

#endif // BULLET_H