#include <iostream>
#include <raylib.h>


using namespace std;

int main () {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    // player
    int playerX = 400;
    int playerY = 300;
    float playerRad = 5;
    Color playerColor = ORANGE;
    // coins
    int coinX = GetRandomValue(0, 800);
    int coinY = GetRandomValue(0, 600);
    int coinRad = GetRandomValue(3, 7);
    Color coinColor = RED;
    
   

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Coin Collector");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
    
   
    
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle(playerX, playerY, playerRad, playerColor);
            DrawCircle(coinX, coinY, coinRad, coinColor);
        EndDrawing();
    }

    CloseWindow();
}