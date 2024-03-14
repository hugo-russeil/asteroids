#include "score.h"

#include "raylib.h"

int score = 0;

void updateScore(int value){
    score += value;
}

void drawScore(){
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
}
