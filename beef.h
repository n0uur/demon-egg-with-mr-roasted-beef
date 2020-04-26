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
Image rawMeatImg[4];

// -----------------------

Texture2D table;
Texture2D pan;
Texture2D meatBowl;
Texture2D sauceBowl;
Texture2D rawMeat[4];

// -----------------------

struct beef {
    float posX;
    float posY;
    enum SIDE CURRENT_SIDE;
    enum STATE CURRENT_MEAT_STATE;
} beefArray[MEAT_COUNT];

int rectanglePosX[MEAT_COUNT];
int rectanglePosY[MEAT_COUNT];
int rectangleHeight[MEAT_COUNT];
int rectangleWidth[MEAT_COUNT];

int calcBeefArrayPosX[MEAT_COUNT] = {-400, -300, -400, -500};
int calcBeefArrayPosY[MEAT_COUNT] = {240, 200, 180, 180};
int calcRectanglePosX[MEAT_COUNT] = {18, 25, 15, 25};
int calcRectanglePosY[MEAT_COUNT] = {0, 0, -4, 0};
int calcRectangleHeight[MEAT_COUNT] = {-10, -5, -10, 0};
int calcRectangleWidth[MEAT_COUNT] = {-23, -26, -23, -35};

//-------------------------

Vector2 mPosition = { -100.0f, -100.0f };