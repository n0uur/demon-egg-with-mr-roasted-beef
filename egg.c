#include "egg.h"
#include "raymath.h"

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

    CURRENT_EGG_STATE = EGG_WAIT;

    floorPositionY = 650;
    levelHeight = 400;
    jumpHeight = 60;
    baseLevelY = 650;

    eggPositionX = 1366 / 2;
    eggPositionY = baseLevelY;

    gravity = 15;
    velocityY = 0;

    //----------------------------

    camera.target = (Vector2) { eggPositionX, eggPositionY };
    camera.offset = (Vector2) { 1366/2, 768/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //----------------------------

    for(int i = 0; i < 150; i++) {
        gameLevels[i].position = (Vector2) { 1366/2, (1 + i) * levelHeight };
    }
}

void eggMain()
{
    //----------------------------
    //-- กล้อง
    //----------------------------
    UpdateCameraCustom(&camera, eggPositionY - levelHeight / 2, GetFrameTime(), 1366, 768);

    //----------------------------
    //-- ไข่
    //----------------------------

    if(CURRENT_EGG_STATE == EGG_WAIT) {
        // GRAVITY
        eggPositionY = baseLevelY;

        // Check for new state logic
        if (IsKeyDown(KEY_SPACE)) {
            CURRENT_EGG_STATE = EGG_JUMP;
            velocityY = 0;
        }
    }
    else if(CURRENT_EGG_STATE == EGG_JUMP) {
        // GRAVITY
        velocityY -= gravity * GetFrameTime();
        eggPositionY += velocityY * abs(eggPositionY - jumpHeight) * 0.05;

        // Check for new state logic
        if(eggPositionY <= jumpHeight) {
            CURRENT_EGG_STATE = EGG_FALL;
            velocityY = 0;
        }
    }
    else if(CURRENT_EGG_STATE == EGG_FALL) {
        // GRAVITY
        velocityY += gravity * GetFrameTime();
        eggPositionY += velocityY;

        // Check for new state logic
        if(eggPositionY >= baseLevelY) {
            CURRENT_EGG_STATE = EGG_WAIT;
            eggPositionY = baseLevelY;
        }
    }

    //----------------------------
    //-- ด่าน
    //----------------------------

    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

            DrawTexture(eggTexture, eggPositionX - 40/2, eggPositionY - 48/2, WHITE);

            DrawRectangleRec((Rectangle) { 1366/2 - 100, floorPositionY + 20, 200, 10 } , RED);

        EndMode2D();

    EndDrawing();
}

void UpdateCameraCustom(Camera2D *camera, int playerPositionY, float delta, int width, int height)
{
    static float minSpeed = 20;
    static float minEffectLength = 10;
    static float fractionSpeed = 1.2f;
    
    camera->offset = (Vector2){ width/2, height/2 };
    Vector2 diff = Vector2Subtract((Vector2) {1366/2, playerPositionY}, camera->target);
    float length = Vector2Length(diff);
    
    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*delta/length));
    }
}
