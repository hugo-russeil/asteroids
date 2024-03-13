#include "raylib.h"
#include "raymath.h"

#include "bullet.h"

Bullet bullets[MAX_BULLETS] = {0}; // The bullets will be stored in an array for easy access and iterative operations

Bullet createBullet(Vector2 position, Vector2 velocity){
    Bullet bullet = {
        .active = true,
        .position = position,
        .velocity = velocity
    };
    return bullet;

}

void addBullet(Vector2 position, Vector2 velocity){
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bullets[i].active){
            continue; 
        }
        bullets[i] = createBullet(position, velocity);
        break;
    }
}

bool checkCollisionBullet(Bullet* bullet, Vector2 position, float radius){
    if(!bullet->active) return false;
    return CheckCollisionCircles(bullet->position, 2, position, radius);

}

void updateBullet(Bullet* bullet){ 
    if(!bullet->active) return; // If the bullet is not active, don't update it
    bullet->position = Vector2Add(bullet->position, bullet->velocity);
    if(bullet->position.x > GetScreenWidth() || bullet->position.x < 0 || bullet->position.y > GetScreenHeight() || bullet->position.y < 0){
        bullet->active = false; // Deactivate the bullet as soon as it goes off screen
    }
}

void drawBullet(Bullet bullet){
    if(!bullet.active) return;
    DrawCircleV(bullet.position, 2, WHITE);
}


