#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

#define MAX_BULLETS 10

typedef struct{
    bool active;
    Vector2 position;
    Vector2 velocity;
} Bullet;

extern Bullet bullets[MAX_BULLETS];

Bullet createBullet(Vector2 position, Vector2 velocity);
void addBullet(Vector2 position, Vector2 velocity);
bool checkCollisionBullet(Bullet* bullet, Vector2 position, float radius);
void updateBullet(Bullet* bullet);
void drawBullet(Bullet bullet);

#endif // BULLET_H