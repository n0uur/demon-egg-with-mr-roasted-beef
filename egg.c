#include "egg.h"

void jump(int *positionX);

void eggInit()
{
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
}

void eggMain()
{

    if (IsKeyDown(KEY_LEFT))
        posX -= 5;
    else if (IsKeyDown(KEY_RIGHT))
        posX += 5;

    if (IsKeyDown(KEY_UP))
        posY -= 5;

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawTexture(eggTexture, posX, posY, WHITE);

    EndDrawing();
}

void jump(int *positionX)
{
}