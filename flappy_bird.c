// flappy bird w Raylib!
#include "raylib.h"

#define screenWidth 1400
#define screenHeight 1050

// This is used for the initial size of blocks, I did it this way to have only one spot to change size, also wanted to play with const globals
const Vector2 SIZE = { (float) screenWidth / 12, (float) screenHeight / 2.5 };
const int OFFSET = 500;
const int GAP = 200;
const Vector2 STARTPOS = { screenWidth / 2.0f, 0 };
const Vector2 FLAPPYSTARTPOS = { (float) screenWidth / 6, (float) screenHeight / 4 };
int score = 0;
bool gameOver = false;
bool reset = false;

typedef struct Flappy {
    Vector2 position;
    float jump_height;
    int radius;
    bool falling;
    int lives;
} Flappy;

typedef struct Block {
    Vector2 position;
    Vector2 size;
} Block;

int main(void) {    
    InitWindow(screenWidth, screenHeight, "move ball");
    
    // having fun with structs
    Flappy flappy = { 
        .position = FLAPPYSTARTPOS,
        .jump_height = 30.0f,
        .radius = 50, 
        .falling = true,
        .lives = 3 };



    Block hi_blocks[4] = {
        [0].position = STARTPOS,
        [0].size = SIZE };

    Block lo_blocks[4] = {
        [0].position = hi_blocks[0].position.x, screenHeight - hi_blocks[0].size.y,
        [0].size = SIZE };


/*
    so lots going on here, but basically the high blocks y position starts at
    0, it's y size (hight) needs to be random for each one, then there needs to be a gap
    between the top and the lo block, so you place the lo block position at the hi blocks 
    size (not position, because y pos is 0 for hi blocks) plus the GAP, but then we usually have a gap at the bottom of the screen,
    so you need to make the y size (height) equal to the entire screenHeight minus the hi block size 
    plus the gap, so it reaches the bottom.

*/

    for (int i = 1; i < sizeof(hi_blocks) / sizeof(hi_blocks[0]); i++) {
        int stagger = GetRandomValue(150, 500);
        hi_blocks[i].position = (Vector2) { hi_blocks[i-1].position.x + OFFSET, 0 };
        hi_blocks[i].size = (Vector2) { hi_blocks[i-1].size.x, stagger };

        // I guess if I were just copying position to position I wouldn't need to cast to Vector2, but since I
        // need to add the offset, it complains unless I cast as Vector2
        
        lo_blocks[i].position = (Vector2) { lo_blocks[i-1].position.x + OFFSET, stagger + GAP };
        lo_blocks[i].size = (Vector2) { lo_blocks[i-1].size.x, screenHeight - (stagger + GAP) };
    }        

    // needed to make flappy jump correctly
    Vector2 temp_pos = { flappy.position.x, flappy.position.y };

    SetTargetFPS(60);

    //main game loop here
    while(!WindowShouldClose()) {


        if(flappy.lives <= 0) {
            gameOver = true;
        }

        if(!gameOver) {
            if (reset) {
                reset = false;  
                
                //decided that I want the score to keep going over all three attempts
                //score = 0;

                flappy.position = FLAPPYSTARTPOS;
                flappy.falling = true;

                hi_blocks[0].position = STARTPOS;
                hi_blocks[0].size = SIZE;

                lo_blocks[0].position = (Vector2) { hi_blocks[0].position.x, screenHeight - hi_blocks[0].size.y };
                lo_blocks[0].size = SIZE;

                for (int i = 1; i < sizeof(hi_blocks) / sizeof(hi_blocks[0]); i++) {
                    int stagger = GetRandomValue(150, 500);
                    hi_blocks[i].position = (Vector2) { hi_blocks[i-1].position.x + OFFSET, 0 };
                    hi_blocks[i].size = (Vector2) { hi_blocks[i-1].size.x, stagger };
                    
                    lo_blocks[i].position = (Vector2) { lo_blocks[i-1].position.x + OFFSET, stagger + GAP };
                    lo_blocks[i].size = (Vector2) { lo_blocks[i-1].size.x, screenHeight - (stagger + GAP) };
                }
            }

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

            //reset if flappy falls below the world or flies above
            if ((int) (flappy.position.y - flappy.radius) >= (int) screenHeight || (int) (flappy.position.y + flappy.radius) <= 0) {
                reset = true;
                flappy.lives--;
            }

            
            for (int i = 0; i < sizeof(hi_blocks) / sizeof(hi_blocks[0]); i++) {
                
                // this bit makes the blocks dissapear on the left, then reappear on the right
                if (hi_blocks[i].position.x > 0 - hi_blocks[i].size.x)
                    hi_blocks[i].position.x -= 2;
                else 
                    hi_blocks[i].position.x = hi_blocks[i-1].position.x + OFFSET;
                
                lo_blocks[i].position.x = hi_blocks[i].position.x;

                // staggering blocks to provide challenge
                if ((int) hi_blocks[i].position.x == screenWidth) {
                    int stagger = GetRandomValue(150, 700);
                    hi_blocks[i].size.y = stagger;
                
                    lo_blocks[i].position.y = stagger + GAP;
                    lo_blocks[i].size.y = screenHeight - (stagger + GAP);
                }
                

                // if flappy's backend is equal to the front end of a block (meaning flappy passed a block) update score
                // don't ask my why I'm multiplying radius by 3 cus IDK. 
                // BUG: sometimes adds more than one to score :(
                if ((int) (hi_blocks[i].position.x + SIZE.x) == (int) ((screenWidth / 4) - (3 * flappy.radius)))
                    score++;
            }
        }


        BeginDrawing();
            ClearBackground(BLACK);

            if(!gameOver) {

                DrawCircleV(flappy.position, flappy.radius, YELLOW);

                for (int i = 0; i < sizeof(hi_blocks) / sizeof(hi_blocks[0]); i++) {
                    DrawRectangleV(hi_blocks[i].position, hi_blocks[i].size, LIGHTGRAY);
                    DrawRectangleV(lo_blocks[i].position, lo_blocks[i].size, LIGHTGRAY);

                    // checking flappy + pipe collision
                    if (CheckCollisionCircleRec(flappy.position, flappy.radius, (Rectangle) {  hi_blocks[i].position.x, hi_blocks[i].position.y, hi_blocks[i].size.x, hi_blocks[i].size.y})) {
                        flappy.lives--;
                        reset = true;
                    }
                        
                    if (CheckCollisionCircleRec(flappy.position, flappy.radius, (Rectangle) {  lo_blocks[i].position.x, lo_blocks[i].position.y, lo_blocks[i].size.x, lo_blocks[i].size.y})) {
                        flappy.lives--;
                        reset = true;
                    }
                }

                // drawing a visual representation of remaining lives
                for (int i = 1; i <= flappy.lives; i++) {
                    // since 0 on x coords is left side, multiply i by 100 to space each life 100 apart
                    DrawCircleV((Vector2) { i * 100, screenHeight - 50 }, 20, YELLOW);
                }

                // draw score
                DrawText(TextFormat("Score: %d", score), screenWidth - 150, 50, 20, YELLOW);

                //debugging
                // DrawText(TextFormat("0 x pos: %d", (int) hi_blocks[0].position.x), 5, 30, 20, WHITE);
                // DrawText(TextFormat("1 x pos: %d", (int) hi_blocks[1].position.x), 5, 60, 20, WHITE);
                // DrawText(TextFormat("2 x pos: %d", (int) hi_blocks[2].position.x), 5, 90, 20, WHITE);
                // DrawText(TextFormat("3 x pos: %d", (int) hi_blocks[3].position.x), 5, 120, 20, WHITE);

                
            }else if(gameOver) {

                DrawRectangle(0, 0, screenWidth, screenHeight, RED);
                DrawText(TextFormat("SCORE: %d", score), screenWidth / 2, (screenHeight / 2) - 65, 50, YELLOW);
                DrawText("GAME OVER :'(", screenWidth / 2, screenHeight / 2, 40, BLACK);
                DrawText("Press Enter to play again", screenWidth / 2, (screenHeight / 2) + 50, 20, WHITE);
                DrawText("Press ESC to leave", screenWidth / 2, (screenHeight / 2) + 80, 20, WHITE);


                if (IsKeyPressed(KEY_ENTER)) {
                    reset = true;
                    gameOver = false;
                    flappy.lives = 3;
                }
                if (IsKeyPressed(KEY_ESCAPE)) 
                    WindowShouldClose();
        
            }

            
            DrawFPS(10, 10);
        EndDrawing();
    


    }

    CloseWindow();

    return 0;       
}