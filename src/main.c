#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"

#include "utils.h"
#include "asteroid.h"
#include "player.h"
#include "bullet.h"
#include "score.h"
#include "saucer.h"

#define DELAY 2

static bool debug = false;

static const int screenWidth = 1200;
static const int screenHeight = 800;
const Vector2 screenSize = {screenWidth, screenHeight};
static float lastCreationTime = 0; // Used to keep track of the last time an asteroid was created

void updateDrawFrame();
Player player;

int main(){

    SetTargetFPS(144);

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

    if(player.base.active){
        

        for(int i = 0; i < MAX_ASTEROIDS; i++){
            updateAsteroid(&asteroids[i]); // Update each active asteroid in the array

            // Check for collisions
            if(asteroids[i].base.active && checkCollision(&player.base, &asteroids[i].base)){ // Check for collision with player
                player.base.active = false; // Kill the player if there is a collision with an asteroid
            }
            for(int j = 0; j < MAX_SAUCERS; j++){
                if(!saucers[j].base.active) continue; // Don't check for collision if the saucer is inactive
                if(checkCollision(&saucers[j].base, &asteroids[i].base)){
                    saucers[j].base.active = false; // Destroy the saucer if it collides with an asteroid
                    splitAsteroid(&asteroids[i]); // Split the asteroid if it collides with a saucer
                }

                if(checkCollision(&player.base, &saucers[j].base)){
                    player.base.active = false; // Kill the player if there is a collision with a saucer
                }
            }
            for(int j = 0; j < MAX_BULLETS; j++){
                if(!asteroids[i].base.active || !bullets[j].base.active) continue; // Don't check for collision if the asteroid or bullet is inactive
                if(checkCollision(&bullets[j].base, &asteroids[i].base)){
                    bullets[j].base.active = false;
                    updateScore(40 / asteroids[i].size); // Update the score if an asteroid is shot
                    splitAsteroid(&asteroids[i]); // Split the asteroid if it is shot and update the score accordingly
                }
            }

        }

        for(int i = 0; i < MAX_BULLETS; i++){
            updateBullet(&bullets[i]); // Update each active bullet in the array

            for(int j = 0; j < MAX_SAUCERS; j++){
                if(!saucers[j].base.active || !bullets[i].base.active) continue; // Don't check for collision if the saucer or bullet is inactive
                if(bullets[i].owner && checkCollision(&bullets[i].base, &saucers[j].base)){
                    bullets[i].base.active = false;
                    saucers[j].base.active = false;
                    updateScore(100); // Update the score if a saucer is shot
                }
            }
            if(!bullets[i].owner && checkCollision(&player.base, &bullets[i].base)){
                player.base.active = false;
            }
        }

        updatePlayer(&player);

        if(lastCreationTime + DELAY < GetTime()){ // Create a new asteroid every DELAY seconds
            Vector2 pos = generateOffScreenPosition();
            Vector2 vel = calculateAsteroidTrajectory(pos);
            AsteroidSize size;

            switch(GetRandomValue(1, 3)){
                case 1:
                    size = ASTEROID_SMALL;
                    break;
                case 2:
                    size = ASTEROID_MEDIUM;
                    break;
                case 3:
                    size = ASTEROID_LARGE;
                    break;
            }

            addAsteroid(pos, vel, size);
            addSaucer(generateOffScreenPosition()); // Add a saucer every time an asteroid is added
            lastCreationTime = GetTime();
        }

        BeginDrawing();

            ClearBackground(BLACK);

            if(debug){
                drawHitboxes(); // Draw the hitboxes of the player, asteroids and saucers
                drawVelocities(); // Draw the velocities of the player, asteroids and saucers
                DrawText(TextFormat("FPS: %i", GetFPS()), 10, 40, 20, WHITE); // Display the current FPS
            }

            drawScore();
            
            for(int i = 0; i < MAX_ASTEROIDS; i++){
                drawAsteroid(&asteroids[i]); // Draw every active asteroid in the array
            }

            for(int i = 0; i < MAX_BULLETS; i++){
                drawBullet(bullets[i]); // Draw every active bullet in the array
            }

            for(int i = 0; i < MAX_SAUCERS; i++){
                updateSaucer(&saucers[i]);
                drawSaucer(saucers[i]);
            }

            drawPlayer(&player);

        EndDrawing();
    }
    else{ // If the player is dead, display a game over message
        BeginDrawing();
            ClearBackground(BLACK); 
            DrawText("Game Over", screenWidth/2 - MeasureText("Game Over", 40)/2, screenHeight/2 - 40, 40, WHITE);
            DrawText(TextFormat("Final Score: %i", score), screenWidth/2 - MeasureText(TextFormat("Final Score: %i", score), 20)/2, screenHeight/2, 20, WHITE);
        EndDrawing();
    }
}
