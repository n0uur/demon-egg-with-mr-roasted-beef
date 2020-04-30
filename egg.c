#include "egg.h"
#include "raymath.h"

void eggInit()
{
    //----------------------------

    // Loaded in CPU memory
    eggImg = LoadImage("resources/dozenegg/images/bigger_egg.png");
    basketImg = LoadImage("resources/dozenegg/images/basket_sm.png");
    backgroundImg = LoadImage("resources/dozenegg/images/egg_bg.png");
    goalImg = LoadImage("resources/dozenegg/images/goal.png");
    eggInBasket = LoadImage("resources/dozenegg/images/egg_in_basket.png");
    auraImg = LoadImage("resources/dozenegg/images/aura.png");

    // Image resize (if needed)
    ImageResize(&eggImg, 40, 48);
    ImageResize(&basketImg, 80, 30);

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
    jumpHeight = 220;
    baseLevelY = 650;

    eggPositionX = 1366 / 2;
    eggPositionY = baseLevelY;

    gravity = 15;
    velocityY = 0;

    currentEggLevel = 0;

    //----------------------------

    camera.target = (Vector2){eggPositionX, eggPositionY};
    camera.offset = (Vector2){1366 / 2, 768 / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //----------------------------

    for (int i = 0; i < 150; i++)
    {
        gameLevels[i].position = (Vector2){1366 / 2, baseLevelY -(1 + i) * levelHeight};
        TraceLog(LOG_INFO, "Loaded Level %d : %d", i + 1, baseLevelY -(1 + i) * levelHeight);
    }
}

void eggMain()
{
    //----------------------------
    //-- กล้อง
    //----------------------------
    if(CURRENT_EGG_STATE != EGG_FAIL_TRANSITION) // when fail camera will not follow egg
        UpdateCameraCustom(&camera, eggPositionY - levelHeight / 2, GetFrameTime(), 1366, 768);

    //----------------------------
    //-- ไข่
    //----------------------------
    if (CURRENT_EGG_STATE == EGG_WAIT)
    {
        eggPositionY = baseLevelY;

        if(currentEggLevel > 0)
            eggPositionX = LERP(eggPositionX, gameLevels[currentEggLevel - 1].position.x, 0.4);

        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
        {
            CURRENT_EGG_STATE = EGG_JUMP;
            velocityY = -3;
            positionYToGo = baseLevelY - jumpHeight - levelHeight;
            TraceLog(LOG_INFO, "jumping Highest point is : %d", positionYToGo);
        }
    }
    else if (CURRENT_EGG_STATE == EGG_JUMP)
    {
        velocityY -= gravity * GetFrameTime();
        eggPositionY += velocityY * abs(eggPositionY - positionYToGo) * 0.02;

        if (eggPositionY <= positionYToGo + 10)
        {
            CURRENT_EGG_STATE = EGG_FALL;
            velocityY = 0;
        }
    }
    else if (CURRENT_EGG_STATE == EGG_FALL)
    {
        velocityY += gravity * GetFrameTime() * 0.8;
        eggPositionY += velocityY;

        if (eggPositionY >= baseLevelY - levelHeight) // back to basket Y, check for next state
        {
            if(abs(gameLevels[currentEggLevel].position.x - eggPositionX) <= 35) {
                baseLevelY -= levelHeight;
                eggPositionY = baseLevelY;
                CURRENT_EGG_STATE = EGG_NEXT_LEVEL_TRANSITION;
            }
            else {
                CURRENT_EGG_STATE = EGG_FAIL_TRANSITION;
            }
        }
    }
    else if (CURRENT_EGG_STATE == EGG_NEXT_LEVEL_TRANSITION)
    {
        eggPositionY = baseLevelY;
        currentEggLevel++;
        CURRENT_EGG_STATE = EGG_WAIT;
    }
    else if (CURRENT_EGG_STATE == EGG_FAIL_TRANSITION)
    {
        baseLevelY += levelHeight;
        velocityY += gravity * GetFrameTime() * 0.8;
        eggPositionY += velocityY;

        if (IsKeyPressed(KEY_R))
        {
            eggInit();
        }
    }

    // DEBUG
    if (IsKeyDown(KEY_LEFT))
    {
        eggPositionX -= 3;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        eggPositionX += 3;
    }
    //----------------------------
    //-- ด่าน
    //----------------------------
    

    //----------------------------
    // -- แสดงผล
    //----------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(backgroundTexture, 0, 0, WHITE);

        BeginMode2D(camera);

            DrawTexture(eggTexture, eggPositionX - 40 / 2, eggPositionY - 48 / 2, WHITE);

            DrawTexture(basketTexture, 1366 / 2 - 80 / 2, 650 - 30 / 2 + 15, WHITE);

            for(int i = currentEggLevel - 2; i < currentEggLevel + 5; i++) {

                if(!(i >= 0 && i <= 150)) // avoiding overflow
                    continue;

                if(i == currentEggLevel - 1)
                    DrawTexture(basketTexture, gameLevels[i].position.x - 80 / 2, gameLevels[i].position.y - 30 / 2 + 15, RED);
                else
                    DrawTexture(basketTexture, gameLevels[i].position.x - 80 / 2, gameLevels[i].position.y - 30 / 2 + 15, WHITE);
            }

            //DrawRectangleRec((Rectangle){1366 / 2 - 100, floorPositionY + 20, 200, 10}, RED);

        EndMode2D();

    EndDrawing();
}

void UpdateCameraCustom(Camera2D *camera, int playerPositionY, float delta, int width, int height)
{
    static float minSpeed = 20;
    static float minEffectLength = 10;
    static float fractionSpeed = 1.2f;

    camera->offset = (Vector2){width / 2, height / 2};
    Vector2 diff = Vector2Subtract((Vector2){1366 / 2, playerPositionY}, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed * delta / length));
    }
}
