#ifndef SAUCER_H
#define SAUCER_H

#include "raylib.h"

#include "gameEntity.h"

#define MAX_SAUCERS 2
#define SAUCER_SPEED 100

typedef struct{
    GameEntity base;
    float cooldown;
}Saucer;

extern Saucer saucers[MAX_SAUCERS];

Saucer createSaucer(Vector2 position);
void addSaucer(Vector2 position);
void updateSaucer(Saucer* saucer);
void drawSaucer(Saucer saucer);
void shootSaucer(Saucer* saucer);
void destroySaucer(Saucer* saucer);


#endif // SAUCER_H
