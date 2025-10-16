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
    int points = 5;
    float playerRad = points + 5;
    int magnetism = 0;
    float effectivePlayerRad = playerRad + magnetism;
    Color playerColor = BROWN;
    // coins
    int coinX = GetRandomValue(0, 800);
    int coinY = GetRandomValue(0, 600);
    int coinRad = 3;
    Color coinColor = RED;
    int growthSize = 1;
    int playerRange = playerRad/2;
    int scoreFontSize = 100;
    enum GameState{
        Game,
        Shop 
    };
    // shop
    int magnetX = SCREEN_WIDTH/5;
    int magnetY = SCREEN_HEIGHT/5;
    int magnetScaleX = 50;
    int magnetScaleY = 50;
    Color magnetColor = RED;
    int magBasePrice = 10;
    int magInflation = 1;
    int magPrice = magBasePrice * magInflation;
    int growthX = SCREEN_WIDTH/5*2;
    int growthY = SCREEN_HEIGHT/5;
    int growthScaleX = 50;
    int growthScaleY = 50;
    Color growthColor = GREEN;
    int groBasePrice = 20;
    int groInflation = 1;
    int groPrice = groBasePrice * groInflation;

    GameState state = GameState::Game;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Coin Collector");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){

    // changing player colour based on points
    if(points <= 10){
        playerColor = BROWN;
    }
    else if(points <= 20){
        playerColor = ORANGE;
    }
    else if(points<= 30){
        playerColor = LIGHTGRAY;
    }
    else{
        playerColor = GOLD;
    }
        
    string moneyString = to_string((int)points);
    string magPriceString = to_string(magPrice);
    string groPriceString = to_string(groPrice);
    

    switch (state){
    case GameState::Game:
    
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
        if(CheckCollisionCircles({playerX, playerY}, effectivePlayerRad, {coinX, coinY}, coinRad)){
            coinX = GetRandomValue(0, 800);
            coinY = GetRandomValue(0, 600);
            points += growthSize;
            coinRad += growthSize;
            playerRad = points + 5;
            effectivePlayerRad = playerRad + magnetism;
        
            // makes coins not spawn too close to the player
            if(CheckCollisionCircles({playerX, playerY}, effectivePlayerRad+playerRange, {coinX, coinY}, coinRad)){
                coinX = GetRandomValue(0, 800);
                coinY = GetRandomValue(0, 600);
            }
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawCircleLines(playerX, playerY, effectivePlayerRad, WHITE);   
        DrawCircle(playerX, playerY, playerRad, playerColor);
        DrawCircle(coinX, coinY, coinRad, coinColor); 
        DrawText(moneyString.c_str(), SCREEN_WIDTH/2-scoreFontSize/2, 0, scoreFontSize, WHITE);
        EndDrawing();

        if(IsKeyPressed(KEY_E)){
            state = GameState::Shop;
        }
        break;
        
    case GameState::Shop:

        if(IsKeyPressed(KEY_ONE) && points >= (magPrice + 1)){
            magnetism += 10;
            points -= magPrice;
            magInflation += 1;
            magPrice = magBasePrice * magInflation;
            playerRad = points + 5;
            effectivePlayerRad = playerRad + magnetism;
            if(playerRad >= 5){
                coinRad = playerRad -2;
            }
            else{
                coinRad = 3;
            }
        }
        if(IsKeyPressed(KEY_TWO) && points >= (groPrice +1)){
            growthSize += 1;
            points -= groPrice;
            groInflation += 1;
            groPrice = groBasePrice + 5* (groInflation*groInflation);
            playerRad = points +5;
            effectivePlayerRad = playerRad + magnetism;
            if(playerRad >= 5){
                coinRad = playerRad -2;
            }
            else{
                coinRad = 3;
            }
        }
        if(IsKeyPressed(KEY_R)){
            state = GameState::Game;
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawRectangle(magnetX, magnetY, magnetScaleX, magnetScaleY, magnetColor);
        DrawText(magPriceString.c_str(), magnetX+magnetScaleX/2, magnetY+magnetScaleY/2, 50, WHITE);
        DrawRectangle(growthX, growthY, growthScaleX, growthScaleY, growthColor);
        DrawText(groPriceString.c_str(), growthX+growthScaleX/2, growthY+growthScaleY/2, 50, WHITE);
        DrawText(moneyString.c_str(), SCREEN_WIDTH/2-scoreFontSize/2, 0, scoreFontSize, WHITE);
        EndDrawing();
            
        break;
    
    default:
        cout << "hi" << endl;
        break;
            
    }
}
    CloseWindow();
}