#include "raylib.h"
#include "raymath.h"

#define CHOCOLATE CLITERAL(Color) { 118, 57, 16, 255 }  //For bg

#define MEAT_COUNT 10
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

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

void eggInit();
void eggMain();

void beefInit();
void beefMain();

// -----------------------

Image gameLogo;
Image beefSelect;
Image EggSelect;

Texture2D gameLogoTexture;
Texture2D beefSelectTexture;
Texture2D EggSelectTexture;

float beefSplashPositionX;
float beefSplashPositionY;
float eggSplashPositionX;
float eggSplashPositionY;

Music mainManuMusic;
bool isMainManuPlaying;

// -----------------------

double LERP(float start, float stop, float weight);