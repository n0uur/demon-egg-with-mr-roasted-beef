#include "main.h"

// -----------------------

int eggPositionX;
int eggPositionY;
float eggRotation;
float nextRotation;

void updateRotation();

int cameraTargetPositionY;

int lifePoint;
int score;

// -----------------------

float auraOpacity;
float auraScale;
Vector2 auraPosition;

// -----------------------

Image eggImg;
Image basketImg;
Image backgroundImg;
Image goalImg;
Image eggInBasket;
Image auraImg;
Image exitButtonImg;

// -----------------------

Texture2D eggTexture;
Texture2D basketTexture;
Texture2D backgroundTexture;
Texture2D goalTexture;
Texture2D eggInBasketTexture;
Texture2D auraTexture;
Texture2D exitButtonTexture;

// -----------------------

enum GAME_PLAY_STATE {
    EGG_PLAYING,
    EGG_GAME_OVER
};

enum EGG_PLAY_STATE {
    EGG_WAIT,
    EGG_JUMP,
    EGG_FALL,
    EGG_NEXT_LEVEL,
    EGG_FAIL,
    EGG_FAIL_TO_WAIT,
    EGG_FAIL_TO_WAIT_2,
};

enum LEVEL_MOVEMENT_TYPE {
    MOVE_STATIC,
    MOVE_LEFT_TO_RIGHT,
    MOVE_RIGHT_TO_LEFT
};

enum EGG_PLAY_STATE CURRENT_EGG_STATE;

// -----------------------

Camera2D camera;

void UpdateCameraCustom(Camera2D *camera, int playerPositionY, float delta, int width, int height);

// -----------------------

int floorPositionY;
int levelHeight;
int jumpHeight;
int baseLevelY;

float gravity;
float velocityY;

void resetGravity();
void updateGravity();

float lastLanding;
float lastFail;

// -----------------------

struct Level {
    Vector2 position;
    enum LEVEL_MOVEMENT_TYPE movementType;
    int movementSpeed; /* pixel/seconds */
};

struct Level gameLevels[160];

int currentEggLevel;
int positionYToGo;

int basketWidth;
int basketHeight;

int circlePosX;
int circlePosY;

Rectangle sourceRec;
Rectangle destRec;