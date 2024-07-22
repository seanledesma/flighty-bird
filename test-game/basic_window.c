    //basic window
    #include "raylib.h"   

    int main(void) {
        const int screenWidth = 800;
        const int screenHeight = 450;

        InitWindow(screenWidth, screenHeight, "raylib basic window :)");

        SetTargetFPS(60);

        //main game loop here
        while(!WindowShouldClose()) {
            BeginDrawing();
                ClearBackground(RAYWHITE);

                DrawText("congrats! our first window!", 190, 200, 20, LIGHTGRAY);
   
            EndDrawing();
        }

        CloseWindow();

        return 0;       
    }