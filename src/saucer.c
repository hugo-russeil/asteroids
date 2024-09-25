#include "saucer.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "utils.h"
#include "bullet.h"

Saucer saucers[MAX_SAUCERS] = {0};

Saucer createSaucer(Vector2 position){
    Saucer saucer = {
        .base.position = position,
        .base.velocity = (Vector2){0, 0},
        .base.hitbox = (Rectangle){position.x - 20, position.y - 10, 40, 20},
        .cooldown = 5, // saucers won't shoot for 5 seconds to let the player get ready
        .base.active = true
    };
    return saucer;
}

void addSaucer(Vector2 position){
    for(int i = 0; i < MAX_SAUCERS; i++){
        if(saucers[i].base.active){
            continue;
        }
        saucers[i] = createSaucer(position);
        break;
    }
}

#include <stdlib.h> // For rand() and RAND_MAX

void shootSaucer(Saucer* saucer){
    if(!saucer->base.active) return; // if the saucer is not active, return

    // Calculate the direction towards the player
    Vector2 direction = Vector2Normalize(Vector2Subtract(player.base.position, saucer->base.position));

    // Generate a small random angle offset (e.g., between -5 and 5 degrees)
    float angleOffset = ((rand() % 11) - 5) * (PI / 180.0f); // Convert degrees to radians

    // Apply the angle offset to the direction vector
    float cosAngle = cosf(angleOffset);
    float sinAngle = sinf(angleOffset);
    Vector2 offsetDirection = {
            direction.x * cosAngle - direction.y * sinAngle,
            direction.x * sinAngle + direction.y * cosAngle
    };

    // Shoot the bullet with the offset direction
    addBullet(saucer->base.position, Vector2Scale(offsetDirection, 1200), false);
}

void updateSaucer(Saucer* saucer){
    if(!saucer->base.active) return; // if the saucer is not active, return
    Vector2 direction = Vector2Normalize(Vector2Subtract(player.base.position, saucer->base.position)); // Saucer moves towards the player
    if(saucer->cooldown <= 0){
        shootSaucer(saucer);
        saucer->cooldown = 5; // Apply cooldown as to not destroy the player instantly
    }
    saucer->cooldown -= GetFrameTime();
    saucer->base.velocity = Vector2Scale(direction, SAUCER_SPEED);
    saucer->base.position = Vector2Add(saucer->base.position, Vector2Scale(saucer->base.velocity, GetFrameTime()));
    saucer->base.hitbox.x = saucer->base.position.x - 20;
    saucer->base.hitbox.y = saucer->base.position.y - 10;
}

// There is probably a better way to do this, but idk 
void drawSaucer(Saucer saucer){
    if(saucer.base.active){
        // Draw the base of the saucer as an elongated hexagon
        DrawLineV((Vector2){saucer.base.position.x - 20, saucer.base.position.y},
                  (Vector2){saucer.base.position.x - 15, saucer.base.position.y + 3}, WHITE);
        DrawLineV((Vector2){saucer.base.position.x - 15, saucer.base.position.y + 3},
                  (Vector2){saucer.base.position.x + 15, saucer.base.position.y + 3}, WHITE);
        DrawLineV((Vector2){saucer.base.position.x + 15, saucer.base.position.y + 3},
                  (Vector2){saucer.base.position.x + 20, saucer.base.position.y}, WHITE);
        DrawLineV((Vector2){saucer.base.position.x + 20, saucer.base.position.y},
                  (Vector2){saucer.base.position.x + 15, saucer.base.position.y - 3}, WHITE);
        DrawLineV((Vector2){saucer.base.position.x + 15, saucer.base.position.y - 3},
                  (Vector2){saucer.base.position.x - 15, saucer.base.position.y - 3}, WHITE);
        DrawLineV((Vector2){saucer.base.position.x - 15, saucer.base.position.y - 3},
                  (Vector2){saucer.base.position.x - 20, saucer.base.position.y}, WHITE);

        // Draw the cockpit as a trapezoid
        DrawLineV((Vector2){saucer.base.position.x - 15, saucer.base.position.y - 3},
                  (Vector2){saucer.base.position.x - 7, saucer.base.position.y - 10}, WHITE);
        DrawLineV((Vector2){saucer.base.position.x - 7, saucer.base.position.y - 10},
                  (Vector2){saucer.base.position.x + 7, saucer.base.position.y - 10}, WHITE);
        DrawLineV((Vector2){saucer.base.position.x + 7, saucer.base.position.y - 10},
                  (Vector2){saucer.base.position.x + 15, saucer.base.position.y - 3}, WHITE);

        // Draw the landing gears as small lines at the bottom of the saucer
        DrawLineV((Vector2){saucer.base.position.x - 10, saucer.base.position.y + 3},
                  (Vector2){saucer.base.position.x - 12, saucer.base.position.y + 8}, WHITE);
        DrawLineV((Vector2){saucer.base.position.x + 10, saucer.base.position.y + 3},
                  (Vector2){saucer.base.position.x + 12, saucer.base.position.y + 8}, WHITE);
    }
}

void destroySaucer(Saucer* saucer){
    saucer->base.active = false;
}
