#include "main.h"

int posX = 1366 / 2;
int posY = 768 / 2;
double lastPressedSpace = 0;

// -----------------------

int eggPositionX;
int eggPositionY;

// -----------------------

Image eggImg;
Image basketImg;
Image backgroundImg;
Image goalImg;
Image eggInBasket;
Image auraImg;

// -----------------------

Texture2D eggTexture;
Texture2D basketTexture;
Texture2D backgroundTexture;
Texture2D goalTexture;
Texture2D eggInBasketTexture;
Texture2D auraTexture;

// -----------------------

enum GAME_PLAY_STATE {
    EGG_PLAYING,
    EGG_GAME_OVER
};

enum EGG_PLAY_STATE {
    EGG_WAIT,
    EGG_JUMP,
    EGG_FALL,
    EGG_NEXT_LEVEL_TRANSITION,
    EGG_FAIL_TRANSITION
};

enum LEVEL_MOVEMENT_TYPE {
    MOVE_STATIC,
    MOVE_LEFT_RIGHT
};

enum EGG_PLAY_STATE CURRENT_EGG_STATE;
// -----------------------

int floorPositionY;
int levelHeight;
int jumpHeight;
int baseLevelY;

float gravity;
float velocityY;

// -----------------------

struct Level {
    Vector2 position;
    enum LEVEL_MOVEMENT_TYPE movementType;
};

struct Level gameLevels[150];
