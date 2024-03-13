#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#include "asteroid.h"

#define DELAY 0.5
#define NEARBLACK (Color){20, 20, 20, 255}

static bool debug = false;

static const int screenWidth = 600;
static const int screenHeight = 600;
const Vector2 screenSize = {screenWidth, screenHeight};
static float lastCreationTime = 0;

void updateDrawFrame();

int main(){
    srand(time(NULL));

    InitWindow(screenWidth, screenHeight, "Asteroid");

    while(!WindowShouldClose()){
        updateDrawFrame();
    }

    CloseWindow();
    return 0;
}

void updateDrawFrame(){

    if(IsKeyPressed(KEY_GRAVE)){
        debug = !debug;
    }

    for(int i = 0; i < MAX_ASTEROIDS; i++){
        updateAsteroid(&asteroids[i]);
    }

    if(lastCreationTime + DELAY < GetTime()){
        Vector2 pos = generateOffScreenPosition();
        Vector2 vel = calculateAsteroidTrajectory(pos);

        addAsteroid(pos, vel, GetRandomValue(ASTEROID_SMALL, ASTEROID_LARGE));
        lastCreationTime = GetTime();
    }

    BeginDrawing();

        ClearBackground(NEARBLACK);

        if(debug){
            for(int i = 0; i < MAX_ASTEROIDS; i++){
                Vector2 lineStart = asteroids[i].position;
                Vector2 lineEnd = Vector2Add(asteroids[i].position, asteroids[i].velocity);
                DrawLineV(lineStart, lineEnd, RED);
            }
        }

        for(int i = 0; i < MAX_ASTEROIDS; i++){
            drawAsteroid(&asteroids[i]);
        }

    EndDrawing();
}