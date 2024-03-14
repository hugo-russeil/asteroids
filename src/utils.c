#include "utils.h"
#include "raylib.h"
#include "raymath.h"

#include "gameEntity.h"
#include "player.h"
#include "asteroid.h"
#include "saucer.h"


static const int screenWidth = 1200;
static const int screenHeight = 800;

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

void drawHitboxes(){
    for(int i = 0; i < MAX_ASTEROIDS; i++){
        if(asteroids[i].base.active){
            DrawRectangleLines(asteroids[i].base.hitbox.x, asteroids[i].base.hitbox.y, asteroids[i].base.hitbox.width, asteroids[i].base.hitbox.height, RED);
        }
    }
    for(int i = 0; i < MAX_SAUCERS; i++){
        if(saucers[i].base.active){
            DrawRectangleLines(saucers[i].base.hitbox.x, saucers[i].base.hitbox.y, saucers[i].base.hitbox.width, saucers[i].base.hitbox.height, GREEN);
        }
    }
    DrawRectangleLines(player.base.hitbox.x, player.base.hitbox.y, player.base.hitbox.width, player.base.hitbox.height, BLUE);
}

void drawVelocities(){
    Vector2 lineStart;
    Vector2 lineEnd;
    for(int i = 0; i < MAX_ASTEROIDS; i++){
        if(!asteroids[i].base.active) continue; // Don't draw inactive asteroids
        lineStart = asteroids[i].base.position;
        lineEnd = Vector2Add(asteroids[i].base.position, asteroids[i].base.velocity);
        DrawLineV(lineStart, lineEnd, RED); // Draw the velocity vector of the asteroid
    }

    for(int i = 0; i < MAX_SAUCERS; i++){
        if(!saucers[i].base.active) continue; // Don't draw inactive saucers
        lineStart = saucers[i].base.position;
        lineEnd = Vector2Add(saucers[i].base.position, saucers[i].base.velocity);
        DrawLineV(lineStart, lineEnd, RED); // Draw the velocity vector of the saucer
    }
    
    lineStart = player.base.position;
    lineEnd = Vector2Add(player.base.position, player.base.velocity);
    DrawLineV(lineStart, lineEnd, RED); // Draw the velocity vector of the player
    
    Vector2 forwardDir = { cos(player.rotation), sin(player.rotation) };
    Vector2 forwardVecEnd = Vector2Add(player.base.position, Vector2Scale(forwardDir, 50)); // 50 is the length of the vector
    DrawLineV(player.base.position, forwardVecEnd, GREEN); // Draw the forward vector of the player
}
