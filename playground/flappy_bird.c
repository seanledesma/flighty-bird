// flappy bird w Raylib!
#include "raylib.h"   

#define screenWidth 1800
#define screenHeight 1450

// This is used for the initial size of blocks, I did it this way to have only one spot to change size, also wanted to play with const globals
const Vector2 SIZE = { (float) screenWidth / 12, (float) screenHeight / 2.5 };

typedef struct Flappy {
    Vector2 position;
    float jump_height;
    int radius;
    bool falling;
} Flappy;

typedef struct Block {
    Vector2 position;
    Vector2 size;
} Block;

int main(void) {    
    InitWindow(screenWidth, screenHeight, "move ball");
    
    // having fun with structs
    Flappy flappy = { 
        .position = (float) screenWidth / 6, (float) screenHeight / 4,
        .jump_height = 30.0f,
        .radius = 50, 
        .falling = true };



    Block hi_blocks[4] = {
        [0].position = (float) screenWidth / 2, 0,
        [0].size = SIZE };

    Block lo_blocks[4] = {
        [0].position = hi_blocks[0].position.x, screenHeight - hi_blocks[0].size.y,
        [0].size = SIZE };
        

    Vector2 temp_pos = { flappy.position.x, flappy.position.y };

    //bool flappy.falling = true;

    SetTargetFPS(60);

    //main game loop here
    while(!WindowShouldClose()) {


        if (IsKeyPressed(KEY_SPACE)) {
            temp_pos = flappy.position;
            flappy.falling = false;
        }


        if (!flappy.falling) {
            if (flappy.position.y == temp_pos.y)
                temp_pos.y -= 20.0f;
            else if (flappy.position.y == temp_pos.y + 2)
                flappy.falling = true;
            else if (flappy.position.y > temp_pos.y)
                flappy.position.y -= 2;                
        }else {
            flappy.position.y += 2;
        }

        // this bit makes the block dissapear on the left, then reappear on the right
        if (hi_blocks[0].position.x > 0 - hi_blocks[0].size.x)
            hi_blocks[0].position.x -= 2;
        else 
            hi_blocks[0].position.x = screenWidth;
        
        lo_blocks[0].position.x = hi_blocks[0].position.x;

        if (CheckCollisionCircleRec(flappy.position, flappy.radius, (Rectangle) {hi_blocks[0].position.x - hi_blocks[0].size.x / 2, 
        hi_blocks[0].position.y - hi_blocks[0].size.y / 2, hi_blocks[0].size.x, hi_blocks[0].size.y}))
            DrawText("HIT", screenWidth / 2, screenHeight / 2, 40, WHITE);

        BeginDrawing();
            ClearBackground(BLACK);

            DrawCircleV(flappy.position, flappy.radius, YELLOW);
            //DrawRectangle(flappy.position.x, flappy.position.y, 170, 40, BLACK);
            DrawRectangleV(hi_blocks[0].position, hi_blocks[0].size, GRAY);
            DrawRectangleV(lo_blocks[0].position, lo_blocks[0].size, GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;       
}