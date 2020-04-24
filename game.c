#include "main.h"

#include <stdio.h>                  // Required for: fopen(), fclose(), fputc(), fwrite(), printf(), fprintf(), funopen()
#include <time.h>

void gameInit() {

    const int screenWidth = 1366;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "ไข่ตัวร้ายกับนายเนื้อย่าง");

    CURRENT_GAME_STATE = GAME_SELECT;

    SetTargetFPS(60);

    fontRSU = LoadFont("resources/fonts/CSChatThaiUI.ttf");
    fontBM = LoadFont("resources/fonts/rsu_bitmap.fnt");
    
}

void gameMain() {

    gameInit();

    while (!WindowShouldClose())
    {
        if(CURRENT_GAME_STATE == GAME_SELECT) {
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | เลือกเกมที่ต้องการเล่น");
            gameSelectMain();
        }
        else if(CURRENT_GAME_STATE == GAME_EGG) {
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | ไข่ตัวร้าย");
            eggMain();
        }
        else if(CURRENT_GAME_STATE == GAME_BEEF) {
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | นายเนื้อย่าง");
            beefMain();
        }
    }

}

void gameSelectMain() {

    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextEx(fontBM, "สวัสดีโลก", (Vector2){ 20.0f, 100.0f }, 32, 2, LIGHTGRAY);

        if(IsKeyPressed(66))CURRENT_GAME_STATE = GAME_BEEF; //Press B to run beef game
        // DrawText("Hi dad!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

}

void gameFini() {

    UnloadFont(fontRSU);
    UnloadFont(fontBM);

    CloseWindow();

}
