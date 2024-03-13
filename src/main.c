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
static float lastCreationTime = 0; // Used to keep track of the last time an asteroid was created

void updateDrawFrame();
Player player;

int main(){
    srand(time(NULL));

    player = createPlayer((Vector2){screenWidth/2, screenHeight/2}); // Create the player in the middle of the screen

    InitWindow(screenWidth, screenHeight, "Asteroids");

    while(!WindowShouldClose()){
        updateDrawFrame();
    }

    CloseWindow();
    return 0;
}

void updateDrawFrame(){

    if(IsKeyPressed(KEY_GRAVE)){
        debug = !debug; // Toggle debug mode
    }

    if(!player.isDead){
        

        for(int i = 0; i < MAX_ASTEROIDS; i++){
            updateAsteroid(&asteroids[i]); // Update each active asteroid in the array

            // Check for collisions
            if(asteroids[i].active && checkCollisionPlayer(&player, asteroids[i].position, 16 * asteroids[i].size)){ // Check for collision with player
                player.isDead = true; // Kill the player if there is a collision with an asteroid
            }
            for(int j = 0; j < MAX_BULLETS; j++){
                if(asteroids[i].active && bullets[j].active && checkCollisionBullet(&bullets[j], asteroids[i].position, 16 * asteroids[i].size)){
                    bullets[j].active = false;
                    splitAsteroid(&asteroids[i]); // Split the asteroid if it is shot
                }
            }

        }

        for(int i = 0; i < MAX_BULLETS; i++){
            updateBullet(&bullets[i]); // Update each active bullet in the array
        }

        updatePlayer(&player);

        if(lastCreationTime + DELAY < GetTime()){ // Create a new asteroid every DELAY seconds
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
                    if(!asteroids[i].active) continue; // Don't draw inactive asteroids
                    lineStart = asteroids[i].position;
                    lineEnd = Vector2Add(asteroids[i].position, asteroids[i].velocity);
                    DrawLineV(lineStart, lineEnd, RED); // Draw the velocity vector of the asteroid
                    DrawPolyLines(asteroids[i].position, 4, 16 * asteroids[i].size, 0, YELLOW); // Draw the hitbox of the asteroid
                }
                lineStart = player.position;
                lineEnd = Vector2Add(player.position, player.velocity);
                DrawLineV(lineStart, lineEnd, RED); // Draw the velocity vector of the player
                
                Vector2 forwardDir = { cos(player.rotation), sin(player.rotation) };
                Vector2 forwardVecEnd = Vector2Add(player.position, Vector2Scale(forwardDir, 50)); // 50 is the length of the vector
                DrawLineV(player.position, forwardVecEnd, GREEN); // Draw the forward vector of the player
            }

            for(int i = 0; i < MAX_ASTEROIDS; i++){
                drawAsteroid(&asteroids[i]); // Draw every active asteroid in the array
            }

            for(int i = 0; i < MAX_BULLETS; i++){
                drawBullet(bullets[i]); // Draw every active bullet in the array
            }

            drawPlayer(&player);

        EndDrawing();
    }
    else{ // If the player is dead, display a game over message
        BeginDrawing();
            ClearBackground(BLACK); 
            DrawText("Game Over", screenWidth/2 - MeasureText("Game Over", 40)/2, screenHeight/2 - 40, 40, WHITE);
        EndDrawing();
    }
}
