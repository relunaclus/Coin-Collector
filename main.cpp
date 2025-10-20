#include <iostream>
#include <raylib.h>
#include <string.h>

using namespace std;

struct Player {
    int x = 400;
    int y = 300;
    int speedX = 4;
    int speedY = 4;
    int points = 5;
    float rad = points + 5;
    int mag = 0;
    float effectiveRad = rad + mag;
    int range = rad/2;
    Color color = BROWN;
};

int main () {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    Player player;
    // coins
    int coinX = GetRandomValue(0, 800);
    int coinY = GetRandomValue(0, 600);
    int coinRad = 3;
    Color coinColor = RED;
    int growthSize = 1;

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
    if(player.points <= 10){
        player.color= BROWN;
    }
    else if(player.points <= 20){
        player.color = ORANGE;
    }
    else if(player.points<= 30){
        player.color = LIGHTGRAY;
    }
    else{
        player.color = GOLD;
    }
        
    string moneyString = to_string((int)player.points);
    string magPriceString = to_string(magPrice);
    string groPriceString = to_string(groPrice);
    

    switch (state){
    case GameState::Game:
    
        // player movement
        if(IsKeyDown(KEY_W) && player.y > 0){
            player.y -= player.speedY;
        }
        if (IsKeyDown(KEY_S) && player.y < SCREEN_HEIGHT){
            player.y += player.speedY;
        }
        if (IsKeyDown(KEY_A) && player.x > 0){
            player.x -= player.speedX;
        }
        if(IsKeyDown(KEY_D) && player.x < SCREEN_WIDTH){
            player.x += player.speedX;
        }

        // collision
        if(CheckCollisionCircles({player.x, player.y}, player.effectiveRad, {coinX, coinY}, coinRad)){
            coinX = GetRandomValue(0, 800);
            coinY = GetRandomValue(0, 600);
            player.points += growthSize;
            coinRad += growthSize;
            player.rad = player.points + 5;
            player.effectiveRad = player.rad + player.mag;
        
            // makes coins not spawn too close to the player
            if(CheckCollisionCircles({player.x, player.y}, player.effectiveRad+player.range, {coinX, coinY}, coinRad)){
                coinX = GetRandomValue(0, 800);
                coinY = GetRandomValue(0, 600);
            }
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawCircleLines(player.x, player.y, player.effectiveRad, WHITE);   
        DrawCircle(player.x, player.y, player.rad, player.color);
        DrawCircle(coinX, coinY, coinRad, coinColor); 
        DrawText(moneyString.c_str(), SCREEN_WIDTH/2-scoreFontSize/2, 0, scoreFontSize, WHITE);
        EndDrawing();

        if(IsKeyPressed(KEY_E)){
            state = GameState::Shop;
        }
        break;
        
    case GameState::Shop:

        if(IsKeyPressed(KEY_ONE) && player.points >= (magPrice + 1)){
            player.mag += 10;
            player.points -= magPrice;
            magInflation += 1;
            magPrice = magBasePrice * magInflation;
            player.rad = player.points + 5;
            player.effectiveRad = player.rad + player.mag;
            if(player.rad >= 5){
                coinRad = player.rad -2;
            }
            else{
                coinRad = 3;
            }
        }
        if(IsKeyPressed(KEY_TWO) && player.points >= (groPrice +1)){
            growthSize += 1;
            player.points -= groPrice;
            groInflation += 1;
            groPrice = groBasePrice + 5* (groInflation*groInflation);
            player.rad = player.points +5;
            player.effectiveRad = player.rad + player.mag;
            if(player.rad >= 5){
                coinRad = player.rad -2;
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
