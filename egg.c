#include "egg.h"

void eggInit()
{
    // Loaded in CPU memory
    Image eggImg = LoadImage("resources/dozenegg/images/egg.png");
    Image basketImg = LoadImage("resources/dozenegg/images/egg.png");
    Image backgroundImg;
    Image goalImg = LoadImage("resources/dozenegg/images/goal.png");
    Image eggInBasket = LoadImage("resources/dozenegg/images/egg_in_basket.png");
    Image auraImg = LoadImage("resources/dozenegg/images/aura.png");

    // Image converted to texture
    Texture2D eggTexture = LoadTextureFromImage(eggImg);
    Texture2D basketTexture = LoadTextureFromImage(basketImg);
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);
    Texture2D goalTexture = LoadTextureFromImage(goalImg);
    Texture2D eggInBasketTexture = LoadTextureFromImage(eggInBasket);
    Texture2D auraTexture = LoadTextureFromImage(auraImg);

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
}
