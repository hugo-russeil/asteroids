#include "asteroid.h"
#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>

static const int screenWidth = 600;
static const int screenHeight = 600;

Asteroid asteroids[MAX_ASTEROIDS] = {0};

Asteroid createAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size){
    Asteroid asteroid = {
        .active = true,
        .size = size,
        .position = position,
        .velocity = velocity,
        .rotation = GetRandomValue(0, 360),
        .rotationSpeed = GetRandomValue(ASTEROID_MIN_ROT_SPEED, ASTEROID_MAX_ROT_SPEED),
        .creationTime = GetTime()
    };
    return asteroid;
}

void addAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size){
    for(int i = 0; i < MAX_ASTEROIDS; i++){
            if(asteroids[i].active){
                continue;
            }
            asteroids[i] = createAsteroid(position, velocity, size);
            break;
        }
}

Vector2 generateOffScreenPosition(){
    int side = GetRandomValue(0, 3);
    int x = 0;
    int y = 0;
    switch(side){
        case 0:
            x = GetRandomValue(0, screenWidth);
            y = 0;
            break;
        case 1:
            x = screenWidth;
            y = GetRandomValue(0, screenHeight);
            break;
        case 2:
            x = GetRandomValue(0, screenWidth);
            y = screenHeight;
            break;
        case 3:
            x = 0;
            y = GetRandomValue(0, screenHeight);
            break;
    }
    return (Vector2){x, y};
}

Vector2 calculateAsteroidTrajectory(Vector2 position){
    Vector2 direction = Vector2Subtract((Vector2){GetRandomValue(0, screenWidth), GetRandomValue(0, screenHeight)}, position);   
    Vector2 normalizedDirection = Vector2Normalize(direction);
    return Vector2Scale(normalizedDirection, GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED));
}

void updateAsteroid(Asteroid* asteroid){
    if(!asteroid->active) return;
    if(asteroid->creationTime + ASTEROID_LIFESPAN < GetTime()){
        destroyAsteroid(asteroid);
        return;
    }
    asteroid->position = Vector2Add(asteroid->position, Vector2Scale(asteroid->velocity, GetFrameTime()));
    asteroid->rotation += asteroid->rotationSpeed * GetFrameTime();
}

void drawAsteroid(Asteroid* asteroid){
    if(!asteroid->active) return;
    DrawPolyLines(asteroid->position, 3, 16 * asteroid->size, asteroid->rotation, WHITE);
}

void destroyAsteroid(Asteroid* asteroid){
    asteroid->active = false;
}