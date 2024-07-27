// flappy bird w Raylib!
#include "raylib.h"   

#define screenWidth 1800
#define screenHeight 1450

// This is used for the initial size of blocks, I did it this way to have only one spot to change size, also wanted to play with const globals
const Vector2 SIZE = { (float) screenWidth / 12, (float) screenHeight / 2.5 };
const int OFFSET = 500;

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

    for (int i = 1; i < sizeof(hi_blocks) / sizeof(hi_blocks[0]); i++) {
        hi_blocks[i].position = (Vector2) { hi_blocks[i-1].position.x + OFFSET, hi_blocks[i-1].position.y};
        hi_blocks[i].size = hi_blocks[i-1].size;
    }

    Block lo_blocks[4] = {
        [0].position = hi_blocks[0].position.x, screenHeight - hi_blocks[0].size.y,
        [0].size = SIZE };
    
    for (int i = 1; i < sizeof(lo_blocks) / sizeof(lo_blocks[0]); i++) {
        // I guess if I were just copying position to position I wouldn't need to cast to Vector2, but since I
        // need to add the offset, it complains unless I cast as Vector2
        lo_blocks[i].position = (Vector2) { lo_blocks[i-1].position.x + OFFSET, lo_blocks[i-1].position.y};
        lo_blocks[i].size = lo_blocks[i-1].size;
    }
        

    Vector2 temp_pos = { flappy.position.x, flappy.position.y };


    SetTargetFPS(60);

    //main game loop here
    while(!WindowShouldClose()) {

        // make Flappy jump
        if (IsKeyPressed(KEY_SPACE)) {
            temp_pos = flappy.position;
            flappy.falling = false;
        }

        // tricky bit of code to smoothly transition flappy up in a jump, then back down
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

        // this bit makes the blocks dissapear on the left, then reappear on the right
        for (int i = 0; i < sizeof(hi_blocks) / sizeof(hi_blocks[0]); i++) {
            if (hi_blocks[i].position.x > 0 - hi_blocks[i].size.x)
                hi_blocks[i].position.x -= 2;
            else 
                hi_blocks[i].position.x = screenWidth;
            
            lo_blocks[i].position.x = hi_blocks[i].position.x;
        }




        BeginDrawing();
            ClearBackground(BLACK);

            DrawCircleV(flappy.position, flappy.radius, YELLOW);
            //DrawRectangle(flappy.position.x, flappy.position.y, 170, 40, BLACK);
            
            // DrawRectangleV(hi_blocks[0].position, hi_blocks[0].size, GRAY);
            // DrawRectangleV(lo_blocks[0].position, lo_blocks[0].size, GRAY);


            for (int i = 0; i < sizeof(hi_blocks) / sizeof(hi_blocks[0]); i++) {
                DrawRectangleV(hi_blocks[i].position, hi_blocks[i].size, LIGHTGRAY);
                DrawRectangleV(lo_blocks[i].position, lo_blocks[i].size, LIGHTGRAY);


                if (CheckCollisionCircleRec(flappy.position, flappy.radius, (Rectangle) {  hi_blocks[i].position.x, hi_blocks[i].position.y, hi_blocks[i].size.x, hi_blocks[i].size.y}))
                    DrawText("HIT", screenWidth / 2, screenHeight / 2, 40, WHITE);

                if (CheckCollisionCircleRec(flappy.position, flappy.radius, (Rectangle) {  lo_blocks[i].position.x, lo_blocks[i].position.y, lo_blocks[i].size.x, lo_blocks[i].size.y}))
                    DrawText("HIT", screenWidth / 2, screenHeight / 2, 40, WHITE);
            }

            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;       
}