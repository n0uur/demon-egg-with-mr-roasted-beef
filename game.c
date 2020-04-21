#include "main.h"

void gameInit() {
    CURRENT_GAME_STATE = GAME_SELECT;
}

void gameMain() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1366;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "ไข่ตัวร้ายกับนายเนื้อย่าง");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if(CURRENT_GAME_STATE == GAME_SELECT) {
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | เลือกเกมที่ต้องการเล่น");
            gameSelectMain();
        }
        else if(CURRENT_GAME_STATE == GAME_EGG) {
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | ไข่ซ่า บ้าพลัง");
            eggMain();
        }
        else if(CURRENT_GAME_STATE == GAME_BEEF) {
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | นายเนื้อย่างตัวร้าย");
            eggMain();
        }
    }
    
    CloseWindow();
}

void gameSelectMain() {

}
