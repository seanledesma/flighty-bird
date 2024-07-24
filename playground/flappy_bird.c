    // flappy bird w Raylib!
    #include "raylib.h"   
    
    #define screenWidth 1800
    #define screenHeight 1450

    int main(void) {    
        InitWindow(screenWidth, screenHeight, "move ball");

        Vector2 ballPos = { (float) screenWidth / 6, (float) screenHeight / 4 };
        Vector2 temp_pos = { ballPos.x, ballPos.y };

        bool falling = true;

        SetTargetFPS(60);

        //main game loop here
        while(!WindowShouldClose()) {


            if (IsKeyPressed(KEY_SPACE)) {
                temp_pos = ballPos;
                falling = false;
            }


            if (!falling) {
                if (ballPos.y == temp_pos.y)
                    temp_pos.y -= 20.0f;
                else if (ballPos.y == temp_pos.y + 2)
                    falling = true;
                else if (ballPos.y > temp_pos.y)
                    ballPos.y -= 2;                
            }else {
                ballPos.y += 2;
            }


            BeginDrawing();
                ClearBackground(BLACK);

                DrawCircleV(ballPos, 50, YELLOW);
                //DrawRectangle(ballPos.x, ballPos.y, 170, 40, BLACK);
   
            EndDrawing();
        }

        CloseWindow();

        return 0;       
    }