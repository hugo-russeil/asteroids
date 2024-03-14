#include "raylib.h"
#include "raymath.h"

#include "bullet.h"

Bullet bullets[MAX_BULLETS] = {0}; // The bullets will be stored in an array for easy access and iterative operations

Bullet createBullet(Vector2 position, Vector2 velocity, bool owner){
    Bullet bullet = {
        .base.position = position,
        .base.velocity = velocity,
        .base.hitbox = (Rectangle){position.x, position.y, 2, 2},
        .base.active = true,
        .owner = owner
    };
    return bullet;

}

void addBullet(Vector2 position, Vector2 velocity, bool owner){
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bullets[i].base.active){
            continue; 
        }
        bullets[i] = createBullet(position, velocity, owner);
        break;
    }
}

bool checkCollisionBullet(Bullet* bullet, Vector2 position, float radius){
    if(!bullet->base.active) return false;
    return CheckCollisionCircles(bullet->base.position, 2, position, radius);
}

void updateBullet(Bullet* bullet){ 
    if(!bullet->base.active) return; // If the bullet is not active, don't update it
    bullet->base.position = Vector2Add(bullet->base.position, Vector2Scale(bullet->base.velocity, GetFrameTime()));
    if(bullet->base.position.x > GetScreenWidth() || bullet->base.position.x < 0 || bullet->base.position.y > GetScreenHeight() || bullet->base.position.y < 0){
        bullet->base.active = false; // Deactivate the bullet as soon as it goes off screen
    }
    // Update the hitbox
    bullet->base.hitbox.x = bullet->base.position.x - 2;
    bullet->base.hitbox.y = bullet->base.position.y - 2;
}

void drawBullet(Bullet bullet){
    if(!bullet.base.active) return;
    DrawCircleV(bullet.base.position, 2, WHITE);
}
