#include "main.h"

// -----------------------

enum SIDE {
    LEFT = 0,
    RIGHT
};

enum STATE {
    RAW = 0,
    COOKED,
    OVER_COOKED
};

// -----------------------

int times = 0;

// -----------------------

Image tableImg;
Image panImg;
Image meatBowlImg;
Image sauceBowlImg;
Image rawMeat1Img;
Image rawMeat2Img;
Image rawMeat3Img;
Image rawMeat4Img;

// -----------------------

Texture2D table;
Texture2D pan;
Texture2D meatBowl;
Texture2D sauceBowl;
Texture2D rawMeat1;
Texture2D rawMeat2;
Texture2D rawMeat3;
Texture2D rawMeat4;

// -----------------------

struct beef {
    float posX;
    float posY;
    enum SIDE CURRENT_SIDE;
    enum STATE CURRENT_MEAT_STATE;
} beefArray[MEAT_COUNT];

int rectanglePosX[10];
int rectanglePosY[10];
int rectangleHeight[10];
int rectangleWidth[10];

//-------------------------

Vector2 mPosition = { -100.0f, -100.0f };