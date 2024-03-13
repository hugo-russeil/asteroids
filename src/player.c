#include "player.h"
#include "bullet.h"

Player createPlayer(Vector2 position){
    Player player = {
        .position = position,
        .velocity = (Vector2){1, 0},
        .rotation = 0,
        .rotationSpeed = 0
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
    player->position = Vector2Add(player->position, Vector2Scale(player->velocity, GetFrameTime()));
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
