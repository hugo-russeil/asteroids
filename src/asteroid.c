#include "asteroid.h"
#include "raylib.h"
#include "raymath.h"
#include "utils.h"

#include <stdlib.h>

static const int screenWidth = 1200;
static const int screenHeight = 800;

Asteroid asteroids[MAX_ASTEROIDS] = {0}; // The asteroids will be stored in an array for easy access and iterative operations

Asteroid createAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size){
    Asteroid asteroid = {
        .base.position = position,
        .base.velocity = velocity,
        .base.hitbox = (Rectangle){position.x, position.y, 32 * size, 32 * size},
        .base.active = true,
        .size = size,
        .rotation = GetRandomValue(0, 360),
        .rotationSpeed = GetRandomValue(ASTEROID_MIN_ROT_SPEED, ASTEROID_MAX_ROT_SPEED),
        .creationTime = GetTime()
    };
    return asteroid;
}

void addAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size){
    for(int i = 0; i < MAX_ASTEROIDS; i++){
        if(asteroids[i].base.active){
            continue; // Don't overwrite active asteroids
        }
        asteroids[i] = createAsteroid(position, velocity, size);
        break;
    }
}

Vector2 calculateAsteroidTrajectory(Vector2 position){
    Vector2 direction = Vector2Subtract((Vector2){GetRandomValue(0, screenWidth), GetRandomValue(0, screenHeight)}, position);   
    Vector2 normalizedDirection = Vector2Normalize(direction);
    return Vector2Scale(normalizedDirection, GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED));
}

void updateAsteroid(Asteroid* asteroid){
    if(!asteroid->base.active) return; // Don't update inactive asteroids
    if(asteroid->creationTime + ASTEROID_LIFESPAN < GetTime()){
        destroyAsteroid(asteroid); // Destroy the asteroid if it's been alive for too long (they must be off screen by now)
        return;
    }
    asteroid->base.position = Vector2Add(asteroid->base.position, Vector2Scale(asteroid->base.velocity, GetFrameTime()));
    asteroid->rotation += asteroid->rotationSpeed * GetFrameTime();
    //update the hitbox
    asteroid->base.hitbox.x = asteroid->base.position.x - 16 * asteroid->size;
    asteroid->base.hitbox.y = asteroid->base.position.y - 16 * asteroid->size;
}

int splitAsteroid(Asteroid* asteroid){
    int points = 40 / asteroid->size; // Shooting an asteroid earns the player points. Smaller asteroids are worth more points
    
    if(asteroid->size == ASTEROID_SMALL){
        destroyAsteroid(asteroid);
        return points;
    }
    // Split the asteroid into two smaller asteroids, going in slightly different directions
    Vector2 vel = Vector2Rotate(asteroid->base.velocity, ASTEROID_TRAJECTORY_ANGLE);
    addAsteroid(asteroid->base.position, vel, asteroid->size / 2);
    vel = Vector2Rotate(asteroid->base.velocity, -ASTEROID_TRAJECTORY_ANGLE);
    addAsteroid(asteroid->base.position, vel, asteroid->size / 2);
    destroyAsteroid(asteroid);
    return points;
}

void drawAsteroid(Asteroid* asteroid){
    if(!asteroid->base.active) return;
    DrawPolyLines(asteroid->base.position, 7, 16 * asteroid->size, asteroid->rotation, WHITE); // Draw a heptagon with a radius of 16 * asteroid->size
}

void destroyAsteroid(Asteroid* asteroid){
    asteroid->base.active = false; // Deactivate the asteroid so it will eventually be overwritten by a new one
}
