#include "raylib.h"

// -----------------------

enum GAME_STATE {
    GAME_SELECT = 0, // หน้าเลือกเกม
    GAME_EGG, // ไข่กระโดด
    GAME_BEEF // ย่างเนื้อในตำนาน
};

enum GAME_STATE CURRENT_GAME_STATE;

// -----------------------

Font fontRSU;
Font fontBM;

// -----------------------

void gameInit();
void gameFini();

void gameMain();

// -----------------------

void gameSelectMain();

void eggMain();

void beefMain();

// -----------------------
