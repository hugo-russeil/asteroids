#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"
#include "raymath.h"

#define ASTEROID_LIFESPAN 10
#define ASTEROID_MIN_ROT_SPEED -240
#define ASTEROID_MAX_ROT_SPEED 240
#define ASTEROID_MIN_SPEED 100
#define ASTEROID_MAX_SPEED 300
#define ASTEROID_TRAJECTORY_ANGLE 30.0 * DEG2RAD
#define MAX_ASTEROIDS 64

typedef enum asteroidSize {
    ASTEROID_SMALL = 1,
    ASTEROID_MEDIUM = 2,
    ASTEROID_LARGE = 4,
} AsteroidSize;

typedef struct asteroid {
    bool active;
    AsteroidSize size;
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float rotationSpeed;
    float creationTime;
} Asteroid;

extern Asteroid asteroids[MAX_ASTEROIDS];

Asteroid createAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
void addAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
Vector2 generateOffScreenPosition();
Vector2 calculateAsteroidTrajectory(Vector2 position);
void updateAsteroid(Asteroid* asteroid);
void drawAsteroid(Asteroid* asteroid);
void destroyAsteroid(Asteroid* asteroid);

#endif // ASTEROID_H