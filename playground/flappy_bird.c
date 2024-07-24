    //basic window
    #include "raylib.h"   
    
    #define screenWidth 1800
    #define screenHeight 1450

    int main(void) {    
        InitWindow(screenWidth, screenHeight, "move ball");

        Vector2 ballPos = { (float) screenWidth / 6, (float) screenHeight / 4 };
        Vector2 temp_pos = { ballPos.x, ballPos.y };

        float spot = 0;

        bool falling = true;

        SetTargetFPS(60);

        //main game loop here
        while(!WindowShouldClose()) {

            // if (IsKeyDown(KEY_D))
            //     ballPos.x += 8.0f;
            // if (IsKeyDown(KEY_LEFT))
            //     ballPos.x -= 8.0f;
            // if (IsKeyDown(KEY_UP))
            //     ballPos.y -= 2.0f;  
            // if (IsKeyDown(KEY_DOWN))
            //     ballPos.y += 2.0f;  
            

            // if (IsKeyPressed(KEY_SPACE)){
            //     falling = false;
            //     if (ballPos.y == temp_pos.y)
            //         temp_pos.y -= 60.0f;
            //     else if (ballPos.y > temp_pos.y)
            //         ballPos.y--;
                
            // }else if ()
            //     ballPos.y++;
            //     //ballPos.y -= 40.0f;


            if (IsKeyPressed(KEY_SPACE)) {
                temp_pos = ballPos;
                //spot = ballPos.y;
                falling = false;
            }


            if (!falling) {
                if (ballPos.y == temp_pos.y)
                    temp_pos.y -= 20.0f;
                else if (ballPos.y == temp_pos.y + 2)
                    falling = true;
                else if (ballPos.y > temp_pos.y)
                    ballPos.y -= 2;
                // for (int i = 0; i < 40; i++) {
                //     ballPos.y--;
                // }
                
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