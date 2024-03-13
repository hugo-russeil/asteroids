#include "player.h"
#include "bullet.h"

#include <stdlib.h>

Player createPlayer(Vector2 position){
    Player player = {
        .position = position,
        .velocity = (Vector2){1, 0},
        .rotation = 0,
        .rotationSpeed = 0,
        .isDead = false
    };
    return player;
}

void inputPlayer(Player* player){
    if (IsKeyDown(KEY_UP)) {
        player->velocity = Vector2Add(player->velocity, Vector2Rotate((Vector2){0.1, 0}, player->rotation));
    } if (IsKeyDown(KEY_DOWN)) {
        player->velocity = Vector2Add(player->velocity, Vector2Rotate((Vector2){-0.1, 0}, player->rotation));
    } if (IsKeyDown(KEY_RIGHT)) {
        player->rotationSpeed = 0.001;
    } if (IsKeyDown(KEY_LEFT)) {
        player->rotationSpeed = -0.001;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        shootPlayer(player);
    }
    player->velocity = Vector2Scale(player->velocity, 0.9999);
    player->rotationSpeed *= 0.99;
}

void movePlayer(Player* player){
    Vector2 newPosition = Vector2Add(player->position, Vector2Scale(player->velocity, GetFrameTime()));

    // Check if the new position would be outside the screen
    if (newPosition.x < 0) {
        newPosition.x = 0;
    } else if (newPosition.x > GetScreenWidth()) {
        newPosition.x = GetScreenWidth(); // Cancels out any horizontal velocity that would take the player off the screen
    }

    if (newPosition.y < 0) {
        newPosition.y = 0;
    } else if (newPosition.y > GetScreenHeight()) {
        newPosition.y = GetScreenHeight(); // Cancels out any vertical velocity that would take the player off the screen
    }

    player->position = newPosition; // Apply the new position
}

void rotatePlayer(Player* player){
    player->rotation += player->rotationSpeed;
}

bool checkCollisionPlayer(Player* player, Vector2 position, float radius){
    return CheckCollisionCircles(player->position, 10, position, radius);
}

void shootPlayer(Player* player){
    addBullet(player->position, Vector2Rotate((Vector2){1, 0}, player->rotation));
}

void updatePlayer(Player* player){
    inputPlayer(player);
    movePlayer(player);
    rotatePlayer(player);
}

void drawPlayer(Player* player){
    float rotation = (player->rotation) + 90 * PI / 180;
    DrawTriangleLines(
        Vector2Add(player->position, Vector2Rotate((Vector2){-10, 10}, rotation)),
        Vector2Add(player->position, Vector2Rotate((Vector2){0, -20}, rotation)),
        Vector2Add(player->position, Vector2Rotate((Vector2){10, 10}, rotation)),
        WHITE  
    );
}
