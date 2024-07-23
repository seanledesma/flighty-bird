    //basic window
    #include "raylib.h"   
    
    #define screenWidth 1800
    #define screenHeight 1450

    int main(void) {    
        InitWindow(screenWidth, screenHeight, "move ball");

        Vector2 ballPos = { (float) screenWidth / 2, (float) screenHeight / 2 };

        SetTargetFPS(60);

        //main game loop here
        while(!WindowShouldClose()) {

            if (IsKeyDown(KEY_RIGHT))
                ballPos.x += 2.0f;
            if (IsKeyDown(KEY_LEFT))
                ballPos.x -= 2.0f;
            if (IsKeyDown(KEY_UP))
                ballPos.y -= 2.0f;  
            if (IsKeyDown(KEY_DOWN))
                ballPos.y += 2.0f;  

            BeginDrawing();
                ClearBackground(RAYWHITE);

                DrawCircleV(ballPos, 50, BLUE);
   
            EndDrawing();
        }

        CloseWindow();

        return 0;       
    }