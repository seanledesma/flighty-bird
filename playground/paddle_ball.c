// bouncing ball with a user-controlled paddle

#include <raylib.h>

#define screenWidth 1800
#define screenHeight 1450
#define paddleWidth screenWidth / 10
#define paddleHeight 20

typedef struct Paddle {
    Vector2 position;
    Vector2 size;
}Paddle;

typedef struct Ball {
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    int radius;
}Ball;


int main(void) {
    InitWindow(screenWidth, screenHeight, "bouncing ball");

    //Vector2 ballPosition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    Ball ball = {0};
    ball.position = (Vector2) { GetScreenWidth() / (float) GetRandomValue(2, 10), GetScreenHeight() / (float) GetRandomValue(2, 10) };   
    ball.speed = (Vector2) { 10.0f, 12.0f };
    ball.radius = 20;
    Ball ball_copy = ball;

    //Vector2 paddlePosition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    Paddle paddle = {0};
    paddle.position = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    paddle.size = (Vector2){ paddleWidth, paddleHeight };
    Paddle paddle_copy = paddle;

    //bool pause = 0;
    int frameCounter = 0;

    SetTargetFPS(60);
    //main game loop here
    while(!WindowShouldClose()) {
        // ball keeps moving in same direction
        ball.position.x += ball.speed.x;
        ball.position.y += ball.speed.y;
        // move paddle left or right
        if (IsKeyDown(KEY_RIGHT))
            paddle.position.x += 8.0f;
        if (IsKeyDown(KEY_LEFT))
            paddle.position.x -= 8.0f;

        // create copy of ball to check for collision better
        // ball_copy = ball;
        // ball_copy.position.x += ball.speed.x;
        // ball_copy.position.y += ball.speed.y;
        //Vector2 next_move = { ball.position.x + ball.speed.x, ball.position.y + ball.speed.y };

        //check for collision with walls
        if ((ball.position.x >= (GetScreenWidth() - ball.radius)) || (ball.position.x <= ball.radius))
            ball.speed.x *= -1.0f;
        if ((ball.position.y >= (GetScreenHeight() - ball.radius)) || (ball.position.y <= ball.radius))
            ball.speed.y *= -1.0f;

        //paddle_copy = paddle;

        
        // check for collision with paddle
        if (CheckCollisionCircleRec(ball.position, ball.radius, (Rectangle){paddle.position.x - paddle.size.x / 2, 
        paddle.position.y - paddle.size.y / 2, paddle.size.x, paddle.size.y})) {
            //  ball.speed.x *= -1.0f;
            ball.speed.y *= -1.0f;
            // if (ball.speed.y < 0)
            //     ball.speed.y *= -1.0f;
        }


        frameCounter++; 

        BeginDrawing();
            ClearBackground(BLACK);  

            DrawCircleV(ball.position, (float) ball.radius, WHITE);

            //DrawRectangle(paddle.position.x, paddle.position.y, paddle.size.x, paddle.size.y, WHITE);
            DrawRectangleV(paddle.position, paddle.size, WHITE);

            //DrawCircleV(paddlePosition, (float) ballRadius * 2, WHITE);

            DrawFPS(10, 10);    

        EndDrawing();
    }

    CloseWindow();

    return 0;       
}