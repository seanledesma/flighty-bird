// raylib shapes example - bouncing ball

#include <raylib.h>

#define screenWidth 1800
#define screenHeight 1450

int main(void) {
    InitWindow(screenWidth, screenHeight, "bouncing ball");

    //Vector2 ballPosition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    Vector2 ballPosition = { GetScreenWidth() / (float) GetRandomValue(2, 10), GetScreenHeight() / (float) GetRandomValue(2, 10) };   
    Vector2 ballSpeed = { 10.0f, 12.0f };
    int ballRadius = 20;

    //bool pause = 0;
    int frameCounter = 0;

    SetTargetFPS(60);
    //main game loop here
    while(!WindowShouldClose()) {

        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        //check for collision
        if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius))
            ballSpeed.x *= -1.0f;
        if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius))
            ballSpeed.y *= -1.0f;

        frameCounter++; 

        BeginDrawing();
            ClearBackground(BLACK);  

            DrawCircleV(ballPosition, (float) ballRadius, WHITE);

            DrawFPS(10, 10);    

        EndDrawing();
    }

    CloseWindow();

    return 0;       
}