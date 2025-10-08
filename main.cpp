#include <iostream>
#include <raylib.h>
#include <string.h>


using namespace std;

int main () {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    // player
    int playerX = 400;
    int playerY = 300;
    int playerSpeedX = 4;
    int playerSpeedY = 4;
    float playerRad = 5;
    Color playerColor = BROWN;
    // coins
    int coinX = GetRandomValue(0, 800);
    int coinY = GetRandomValue(0, 600);
    int coinRad = 3;
    Color coinColor = RED;
    int growthSize = 1;
    int playerRange = playerRad/2;
    int scoreFontSize = 100;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Coin Collector");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        
        // player movement
        if(IsKeyDown(KEY_W) && playerY > 0){
            playerY -= playerSpeedY;
        }
        if (IsKeyDown(KEY_S) && playerY < SCREEN_HEIGHT){
            playerY += playerSpeedY;
        }
        if (IsKeyDown(KEY_A) && playerX > 0){
            playerX -= playerSpeedX;
        }
        if(IsKeyDown(KEY_D) && playerX < SCREEN_WIDTH){
            playerX += playerSpeedX;
        }

        // collision
        if(CheckCollisionCircles({playerX, playerY}, playerRad, {coinX, coinY}, coinRad)){
            coinX = GetRandomValue(0, 800);
            coinY = GetRandomValue(0, 600);
            playerRad += growthSize;
            coinRad += growthSize;

            if(CheckCollisionCircles({playerX, playerY}, playerRad+playerRange, {coinX, coinY}, coinRad)){
                coinX = GetRandomValue(0, 800);
                coinY = GetRandomValue(0, 600);
            }
        }

        // changing player colour based on radius
        if(playerRad <= 10){
            playerColor = BROWN;
        }
        else if(playerRad <= 20){
            playerColor = ORANGE;
        }
        else if(playerRad <= 30){
            playerColor = LIGHTGRAY;
        }
        else{
            playerColor = GOLD;
        }

        string moneyString = to_string((int)playerRad);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle(playerX, playerY, playerRad, playerColor);
            DrawCircle(coinX, coinY, coinRad, coinColor);
            DrawText(moneyString.c_str(), SCREEN_WIDTH/2-scoreFontSize/2, 0, scoreFontSize, WHITE);
        EndDrawing();
    }

    CloseWindow();
}