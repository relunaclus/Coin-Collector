#include <iostream>
#include <raylib.h>
#include <string.h>
#include <player.hpp>
#include <upgrades.hpp>
#include <json-develop/single_include/nlohmann/json.hpp>
#include <fstream>
#include <memory.hpp>

using namespace std;

struct Coin{
    int x = GetRandomValue(0, 800);
    int y = GetRandomValue(0,600);
    int rad = 3;
    Color color = RED;
    int particleX = x;
    int particleY = y;
    int particleRad = rad/2;
};

int main () {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    Player player;
    Coin coin;
    Magnet mag;
    Growth gro;
    Speed spd;
    int scoreFontSize = 100;
    
    Color playercolors[4] = {BROWN, ORANGE, LIGHTGRAY, GOLD};

    enum GameState{
        Game,
        Shop 
    };

    GameState state = GameState::Game;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Coin Collector");
    SetTargetFPS(60);

    InitAudioDevice();

    Sound getCoin =  LoadSound("getCoin.wav"); 
    Sound getUpgrade = LoadSound("getUpgrade.wav");
    Texture2D magTex = LoadTexture("Magnet.png");
    Texture2D groTex = LoadTexture("Growth.png");
    Texture2D spdTex = LoadTexture("Speed.png");
    bool hasGameStarted = false;

    if (!hasGameStarted) {
                    json data = JSON::loadData();

                    player.points = data["Score"];
                    hasGameStarted = true;
                }

    while (WindowShouldClose() == false){

    // changing player colour based on points
    if(player.points <= 10){
    player.color = playercolors[0];
    }
    else if(player.points <= 20){
    player.color = playercolors[1];
    }
    else if(player.points<= 30){
    player.color = playercolors[2];
    }
    else{
     player.color = playercolors[3];
    }
        
    string moneyString = to_string((int)player.points);
    string magPriceString = to_string(mag.price);
    string groPriceString = to_string(gro.price);
    string spdPriceString = to_string(spd.price);
    

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
        if(CheckCollisionCircles({player.x, player.y}, player.effectiveRad, {coin.x, coin.y}, coin.rad)){
            coin.x = GetRandomValue(0, 800);
            coin.y = GetRandomValue(0, 600);
            player.points += player.gro;
            coin.rad += player.gro;
            player.rad = player.points + 5;
            player.effectiveRad = player.rad + player.mag;
            SetSoundVolume(getCoin, 1);
            PlaySound(getCoin);
        
            // makes coins not spawn too close to the player
            if(CheckCollisionCircles({player.x, player.y}, player.effectiveRad+player.range, {coin.x, coin.y}, coin.rad)){
                coin.x = GetRandomValue(0, SCREEN_WIDTH);
                coin.y = GetRandomValue(0, SCREEN_HEIGHT);
            }
        }

        // coins emit particles


        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawCircleLines(player.x, player.y, player.effectiveRad, WHITE);   
        DrawCircle(player.x, player.y, player.rad, player.color);
        DrawCircle(coin.x, coin.y, coin.rad, coin.color); 
        DrawText(moneyString.c_str(), SCREEN_WIDTH/2-scoreFontSize/2, 0, scoreFontSize, WHITE);
        EndDrawing();

        if(IsKeyPressed(KEY_E)){
            state = GameState::Shop;
        }
        break;
        
    case GameState::Shop:

    if(player.points >= (mag.price +1)){
        mag.color = RAYWHITE;
    }
    else{
        mag.color = GRAY;
        }

    if(player.points >= (gro.price +1)){
        gro.color = RAYWHITE;
    }
    else{
        gro.color = GRAY;
    }

    if(player.points >= (spd.price +1)){
        spd.color = RAYWHITE;
    }
    else{
        spd.color = GRAY;
    }



        if(IsKeyPressed(KEY_ONE) && player.points >= (mag.price + 1)){
            player.mag += 10;
            player.points -= mag.price;
            mag.inflation += 1;
            mag.price = mag.bPrice * mag.inflation;
            player.rad = player.points + 5;
            player.effectiveRad = player.rad + player.mag;
            if(player.rad >= 5){
                coin.rad = player.rad -2;
            }
            else{
                coin.rad = 3;
            }
            PlaySound(getUpgrade);
        }
        if(IsKeyPressed(KEY_TWO) && player.points >= (gro.price +1)){
            player.gro += 1;
            player.points -= gro.price;
            gro.inflation += 1;
            gro.price = gro.bPrice * gro.inflation * gro.inflation;
            player.rad = player.points +5;
            player.effectiveRad = player.rad + player.mag;
            if(player.rad >= 5){
                coin.rad = player.rad -2;
            }
            else{
                coin.rad = 3;
            }
            PlaySound(getUpgrade);
        }
        if(IsKeyPressed(KEY_THREE) && player.points >= (spd.price +1)){
            player.speedX += 1;
            player.speedY += 1;
            player.points -= spd.price;
            spd.inflation += 1;
            spd.price = spd.bPrice * spd.inflation * spd.inflation;
            player.rad = player.points +5;
            player.effectiveRad = player.rad + player.mag;
            if(player.rad >= 5){
                coin.rad = player.rad -2;
            }
            else{
                coin.rad = 3;
            }
            PlaySound(getUpgrade);
            
        }
        if(IsKeyPressed(KEY_R)){
            state = GameState::Game;
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawTexture(magTex, mag.x, mag.y, mag.color);
        DrawText(magPriceString.c_str(), mag.x+mag.scaleX/2, mag.y+mag.scaleY/2, 50, WHITE);
        DrawTexture(groTex, gro.x, gro.y, gro.color);   
        DrawText(groPriceString.c_str(), gro.x+gro.scaleX/2, gro.y+gro.scaleY/2, 50, WHITE);
        DrawTexture(spdTex, spd.x, spd.y, spd.color);
        DrawText(spdPriceString.c_str(), spd.x+spd.scaleX/2, spd.y + spd.scaleY/2, 50, WHITE);
        DrawText(moneyString.c_str(), SCREEN_WIDTH/2-scoreFontSize/2, 0, scoreFontSize, WHITE);
        EndDrawing();
    
        break;
    
    default:
        cout << "hi" << endl;
        break;
            
    }
}
UnloadSound(getCoin);
UnloadSound(getUpgrade);
UnloadTexture(magTex);
UnloadTexture(groTex);
UnloadTexture(spdTex);
JSON::AmendScoreJson(player.points);
    CloseWindow();
}