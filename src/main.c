#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"

#include "asteroid.h"
#include "player.h"
#include "bullet.h"

#define DELAY 0.5

static bool debug = false;

static const int screenWidth = 1200;
static const int screenHeight = 800;
const Vector2 screenSize = {screenWidth, screenHeight};
static float lastCreationTime = 0;

void updateDrawFrame();
Player player;

int main(){
    srand(time(NULL));

    player = createPlayer((Vector2){screenWidth/2, screenHeight/2});

    InitWindow(screenWidth, screenHeight, "Asteroids");

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
        if(asteroids[i].active && checkCollisionPlayer(&player, asteroids[i].position, 16 * asteroids[i].size)){ // Check for collision with player
            player = createPlayer((Vector2){screenWidth/2, screenHeight/2});
        }
        for(int j = 0; j < MAX_BULLETS; j++){
            if(bullets[j].active && checkCollisionBullet(&bullets[j], asteroids[i].position, 16 * asteroids[i].size)){
                destroyAsteroid(&asteroids[i]);
                bullets[j].active = false;
            }
        }

    }
    updatePlayer(&player);

    if(lastCreationTime + DELAY < GetTime()){
        Vector2 pos = generateOffScreenPosition();
        Vector2 vel = calculateAsteroidTrajectory(pos);

        addAsteroid(pos, vel, GetRandomValue(ASTEROID_SMALL, ASTEROID_LARGE));
        lastCreationTime = GetTime();
    }

    BeginDrawing();

        ClearBackground(BLACK);

        if(debug){
            Vector2 lineStart;
            Vector2 lineEnd;
            for(int i = 0; i < MAX_ASTEROIDS; i++){
                lineStart = asteroids[i].position;
                lineEnd = Vector2Add(asteroids[i].position, asteroids[i].velocity);
                DrawLineV(lineStart, lineEnd, RED);
                DrawPolyLines(asteroids[i].position, 4, 16 * asteroids[i].size, 0, YELLOW);
            }
            lineStart = player.position;
            lineEnd = Vector2Add(player.position, player.velocity);
            DrawLineV(lineStart, lineEnd, RED);
            
            Vector2 forwardDir = { cos(player.rotation), sin(player.rotation) };
            Vector2 forwardVecEnd = Vector2Add(player.position, Vector2Scale(forwardDir, 50)); // 50 is the length of the vector
            DrawLineV(player.position, forwardVecEnd, GREEN);
        }

        for(int i = 0; i < MAX_ASTEROIDS; i++){
            drawAsteroid(&asteroids[i]);
            drawPlayer(&player);
        }

        for(int i = 0; i < MAX_BULLETS; i++){
            updateBullet(&bullets[i]);
            drawBullet(bullets[i]);
        }

    EndDrawing();
}
