#include "main.h"

#include <stdio.h>                  // Required for: fopen(), fclose(), fputc(), fwrite(), printf(), fprintf(), funopen()
#include <time.h>

void gameMain() {
    // Initialization
    //--------------------------------------------------------------------------------------

    const int screenWidth = 1366;
    const int screenHeight = 768;

    

    InitWindow(screenWidth, screenHeight, "ไข่ตัวร้ายกับนายเนื้อย่าง");

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
            eggMain();
        }
    }
    
    CloseWindow();

    UnloadFont(fontTTF);
}

void gameInit() {

    CURRENT_GAME_STATE = GAME_SELECT;

    SetTargetFPS(60);

    // fontTTF = LoadFontEx("resources/fonts/CSChatThaiUI.ttf", 32, 0, 3800);

    fontBM = LoadFont("resources/fonts/rsu_bitmap.fnt");

}

void gameSelectMain() {

    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextEx(fontBM, "สวัสดีโลก", (Vector2){ 20.0f, 100.0f }, 32, 2, LIGHTGRAY);

        // DrawText("Hi dad!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

}
