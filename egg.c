#include "egg.h"

void eggInit()
{
    // Loaded in CPU memory
    eggImg = LoadImage("resources/dozenegg/images/egg.png");
    basketImg = LoadImage("resources/dozenegg/images/egg.png");
    backgroundImg;
    goalImg = LoadImage("resources/dozenegg/images/goal.png");
    eggInBasket = LoadImage("resources/dozenegg/images/egg_in_basket.png");
    auraImg = LoadImage("resources/dozenegg/images/aura.png");

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
    BeginDrawing();

        ClearBackground(BLACK);

    EndDrawing();
}
