#include "player.h"
#include "bullet.h"

#include <stdlib.h>

Player createPlayer(Vector2 position){
    Player player = {
        .base.position = position,
        .base.velocity = (Vector2){1, 0},
        .base.hitbox = (Rectangle){position.x, position.y, 20, 20},
        .rotation = 0,
        .rotationSpeed = 0,
        .base.active = true
    };
    return player;
}

void inputPlayer(Player* player){
    if (IsKeyDown(KEY_UP)) {
        player->base.velocity = Vector2Add(player->base.velocity, Vector2Rotate((Vector2){5, 0}, player->rotation));
    } if (IsKeyDown(KEY_DOWN)) {
        player->base.velocity = Vector2Add(player->base.velocity, Vector2Rotate((Vector2){-5, 0}, player->rotation));
    } if (IsKeyDown(KEY_RIGHT)) {
        player->rotationSpeed = 0.03;
    } if (IsKeyDown(KEY_LEFT)) {
        player->rotationSpeed = -0.03;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        shootPlayer(player);
    }
    player->base.velocity = Vector2Scale(player->base.velocity, 0.99); // Gradually slow down the player by slightly scaling down the velocity each frame
    player->rotationSpeed *= 0.9; // Slow down the rotation speed by slightly scaling it down each frame
}

void movePlayer(Player* player){
    Vector2 newPosition = Vector2Add(player->base.position, Vector2Scale(player->base.velocity, GetFrameTime()));

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

    player->base.position = newPosition; // Apply the new position
}

void rotatePlayer(Player* player){
    player->rotation += player->rotationSpeed; // Apply the rotation
}

bool checkCollisionPlayer(Player* player, Vector2 position, float radius){
    return CheckCollisionCircles(player->base.position, 10, position, radius);
}

void shootPlayer(Player* player){
    addBullet(player->base.position, Vector2Rotate((Vector2){1200, 0}, player->rotation), true); // Add a bullet going the direction the player is facing
}

void updatePlayer(Player* player){
    inputPlayer(player);
    movePlayer(player);
    rotatePlayer(player);
    // Update the hitbox
    player->base.hitbox.x = player->base.position.x - 10;
    player->base.hitbox.y = player->base.position.y - 10;
}

void drawPlayer(Player* player){
    float rotation = (player->rotation) + 90 * PI / 180; // Adding 90 degrees (converted to radians) to the rotation to make the player face right
    DrawTriangleLines(
        Vector2Add(player->base.position, Vector2Rotate((Vector2){-10, 10}, rotation)),
        Vector2Add(player->base.position, Vector2Rotate((Vector2){0, -20}, rotation)),
        Vector2Add(player->base.position, Vector2Rotate((Vector2){10, 10}, rotation)),
        WHITE
    );
}
