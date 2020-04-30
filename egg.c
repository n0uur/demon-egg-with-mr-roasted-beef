#include "egg.h"

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

    basketWidth = 100;
    basketHeight = 40;

    // Image resize (if needed)
    ImageResize(&eggImg, 40, 48);
    ImageResize(&basketImg, basketWidth, basketHeight);

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
    levelHeight = 300;
    jumpHeight = 150;
    baseLevelY = 650;

    lastLanding = 0;

    eggPositionX = 1366 / 2;
    eggPositionY = baseLevelY;

    gravity = 25;
    velocityY = 0;

    currentEggLevel = 0;

    lifePoint = 12;
    //----------------------------

    camera.target = (Vector2){eggPositionX, eggPositionY};
    camera.offset = (Vector2){1366 / 2, 768 / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //----------------------------

    for (int i = 0; i < 150; i++)
    {
        gameLevels[i].position = (Vector2){1366 / 2, baseLevelY -(1 + i) * levelHeight};
        if(i % 10 == 0) {
            gameLevels[i].movementType = MOVE_STATIC;
        }
        else if(i % 2 == 0) {
            gameLevels[i].movementType = MOVE_LEFT_TO_RIGHT;
        }
        else {
            gameLevels[i].movementType = MOVE_RIGHT_TO_LEFT;
        }
        gameLevels[i].movementSpeed = GetRandomValue(200, 400) + (100.0 * i / 30.0);
        // TraceLog(LOG_INFO, "Loaded Level %d : %d", i + 1, baseLevelY -(1 + i) * levelHeight);
    }
}

void eggMain()
{
    //----------------------------
    //-- ด่าน
    //----------------------------
    for(int i = currentEggLevel - 5; i < currentEggLevel + 10; i++) {

        if(!(i >= 0 && i <= 150)) // no overflow
            continue;

        struct Level *currentEditingLevel = &gameLevels[i];

        if(currentEditingLevel->position.x <= 300) {
            currentEditingLevel->movementType = MOVE_LEFT_TO_RIGHT;
        }
        else if(currentEditingLevel->position.x >= 1066) {
            currentEditingLevel->movementType = MOVE_RIGHT_TO_LEFT;
        }

        if(currentEditingLevel->movementType == MOVE_LEFT_TO_RIGHT) {
            currentEditingLevel->position.x += currentEditingLevel->movementSpeed * GetFrameTime();
        }
        else if(currentEditingLevel->movementType == MOVE_RIGHT_TO_LEFT) {
            currentEditingLevel->position.x -= currentEditingLevel->movementSpeed * GetFrameTime();
        }
    }

    //----------------------------
    //-- ไข่
    //----------------------------
    if (CURRENT_EGG_STATE == EGG_WAIT)
    {
        eggPositionY = baseLevelY;

        if(currentEggLevel > 0) { // ไข่ follow a basket
            if(GetTime() - lastLanding >= 0.3) // smooth follow when just landing at a basket
                eggPositionX = gameLevels[currentEggLevel - 1].position.x;
            else
                eggPositionX = LERP(eggPositionX, gameLevels[currentEggLevel - 1].position.x, 0.6);
        }

        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
        {
            CURRENT_EGG_STATE = EGG_JUMP;
            velocityY = -3;
            positionYToGo = baseLevelY - jumpHeight - levelHeight;
            // TraceLog(LOG_INFO, "jumping Highest point is : %d", positionYToGo);
        }

        if (IsKeyPressed(KEY_N))
        {
            baseLevelY -= levelHeight;
            eggPositionY = baseLevelY;
            currentEggLevel++;
            lastLanding = GetTime();
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
            if(abs(gameLevels[currentEggLevel].position.x - eggPositionX) <= basketWidth / 2) {
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
        lastLanding = GetTime();
        CURRENT_EGG_STATE = EGG_WAIT;
    }
    else if (CURRENT_EGG_STATE == EGG_FAIL_TRANSITION)
    {
        velocityY += gravity * GetFrameTime() * 0.8;
        eggPositionY += velocityY;

        if (IsKeyPressed(KEY_R))
        {
            lastLanding = GetTime();
            CURRENT_EGG_STATE = EGG_WAIT;
            // eggInit();
        }
    }

    if (IsKeyPressed(KEY_U)) {
        if (lifePoint != 12)
            lifePoint += 1;
    }
    else if (IsKeyPressed(KEY_D)) {
        if (lifePoint != 0)
                lifePoint -= 1;
    }       
    //----------------------------
    //-- กล้อง
    //----------------------------
    if(CURRENT_EGG_STATE != EGG_FAIL_TRANSITION) // when fail camera will not follow egg
        UpdateCameraCustom(&camera, eggPositionY - levelHeight / 2, GetFrameTime(), 1366, 768);

    //----------------------------
    // -- แสดงผล
    //----------------------------

    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(backgroundTexture, 0, 0, WHITE);

        BeginMode2D(camera);

            DrawTexture(eggTexture, eggPositionX - 40 / 2, eggPositionY - 48 / 2, WHITE);

            DrawTexture(basketTexture, 1366 / 2 - basketWidth / 2, 650 - basketHeight / 2 + 15, WHITE);

            for(int i = currentEggLevel - 2; i < currentEggLevel + 5; i++) {

                if(!(i >= 0 && i <= 150)) // avoiding overflow
                    continue;

                DrawTexture(basketTexture, gameLevels[i].position.x - basketWidth / 2, gameLevels[i].position.y - basketHeight / 2 + 15, WHITE);
            }

        EndMode2D();

        DrawRectangleRec((Rectangle){ 0, 0, 300 - basketWidth / 2, 768}, (Color) { 0, 0, 0, 0.6 * 255 });
        DrawRectangleRec((Rectangle){ 1066 + basketWidth / 2, 0, 300 - basketWidth / 2, 768}, (Color) { 0, 0, 0, 0.6 * 255 });

        DrawRectangleRec((Rectangle){ 255, 5, 155, 55}, (Color) {33, 32, 31, 0.6 * 255 });

        circlePosX = 270;
        circlePosY = 5;

            for (int i = 0; i < lifePoint; i++) {
                DrawCircle(circlePosX, circlePosY + 15, 10, (Color) {227, 221, 216, 0.8 * 255 });
                circlePosX += 25;
                if (i == 5) {
                    circlePosY += 25;
                    circlePosX = 270;
                }
            }
            for (int i = 0; i < lifePoint - 12; i++) {
                DrawCircle(circlePosX, circlePosY + 15, 10, (Color) {89, 87, 85, 1 * 255 });
                circlePosX += 25;
                if (i == 5) {
                    circlePosY += 25;
                    circlePosX = 270;
                }
            }

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
