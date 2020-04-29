#include "egg.h"
#include <math.h>

void eggInit()
{
    //----------------------------

    // Loaded in CPU memory
    eggImg = LoadImage("resources/dozenegg/images/bigger_egg.png");
    basketImg = LoadImage("resources/dozenegg/images/egg.png");
    backgroundImg;
    goalImg = LoadImage("resources/dozenegg/images/goal.png");
    eggInBasket = LoadImage("resources/dozenegg/images/egg_in_basket.png");
    auraImg = LoadImage("resources/dozenegg/images/aura.png");

    // Image resize (if needed)
    ImageResize(&eggImg, 40, 48);

    // Image converted to texture
    eggTexture = LoadTextureFromImage(eggImg);
    basketTexture = LoadTextureFromImage(basketImg);
    backgroundTexture = LoadTextureFromImage(backgroundImg);
    goalTexture = LoadTextureFromImage(goalImg);
    eggInBasketTexture = LoadTextureFromImage(eggInBasket);
    auraTexture = LoadTextureFromImage(auraImg);

    // Unloaded Image
    UnloadImage(eggImg);
    UnloadImage(basketImg);
    UnloadImage(backgroundImg);
    UnloadImage(goalImg);
    UnloadImage(eggInBasket);
    UnloadImage(auraImg);

    //----------------------------

    int posX = 1366 / 2;
    int posY = 768 / 2;

    CURRENT_EGG_STATE = EGG_WAIT;

    floorPositionY = 720;
    levelHeight = 400;
    jumpHeight = 60;
    baseLevelY = 730;

    gravity = 15;
    velocityY = 0;

    //----------------------------

    for(int i = 0; i < 150; i++) {

    }
}

void eggMain()
{
    //----------------------------
    //-- ไข่
    //----------------------------

    if(CURRENT_EGG_STATE == EGG_WAIT) {
        // GRAVITY
        posY = baseLevelY;

        // Check for new state logic
        if (IsKeyDown(KEY_UP)) {
            CURRENT_EGG_STATE = EGG_JUMP;
            velocityY = 0;
        }
    }
    else if(CURRENT_EGG_STATE == EGG_JUMP) {
        // GRAVITY
        velocityY -= gravity * GetFrameTime();
        posY += velocityY * abs(posY - jumpHeight) * 0.05;

        // Check for new state logic
        if(posY <= jumpHeight) {
            CURRENT_EGG_STATE = EGG_FALL;
            velocityY = 0;
        }
    }
    else if(CURRENT_EGG_STATE == EGG_FALL) {
        // GRAVITY
        velocityY += gravity * GetFrameTime();
        posY += velocityY;

        // Check for new state logic
        if(posY >= baseLevelY) {
            CURRENT_EGG_STATE = EGG_WAIT;
            posY = baseLevelY;
        }
    }

    //----------------------------
    //-- ด่าน
    //----------------------------

    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(eggTexture, posX, posY, WHITE);

    EndDrawing();
}

void resetGravity() {
    gravity = 15;
}