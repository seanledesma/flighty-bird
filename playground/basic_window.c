    //basic window
    #include "raylib.h" 

    #define screenWidth 1800
    #define screenHeight 1450

    int main(void) {
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