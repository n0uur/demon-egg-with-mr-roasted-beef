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
    retryButtonImg = LoadImage("resources/dozenegg/images/Retrybutton.png");

    basketWidth = 100;
    basketHeight = 40;

    // Image resize (if needed)
    ImageResize(&eggImg, 40, 48);
    ImageResize(&basketImg, basketWidth, basketHeight);
    ImageResize(&retryButtonImg, 300, 200);

    // Image converted to texture
    eggTexture = LoadTextureFromImage(eggImg);
    basketTexture = LoadTextureFromImage(basketImg);
    backgroundTexture = LoadTextureFromImage(backgroundImg);
    goalTexture = LoadTextureFromImage(goalImg);
    eggInBasketTexture = LoadTextureFromImage(eggInBasket);
    auraTexture = LoadTextureFromImage(auraImg);
    retryButtonTexture = LoadTextureFromImage(retryButtonImg);

    // Unloaded Image
    UnloadImage(eggImg);
    UnloadImage(basketImg);
    UnloadImage(backgroundImg);
    UnloadImage(goalImg);
    UnloadImage(eggInBasket);
    UnloadImage(auraImg);
    UnloadImage(retryButtonImg);

    //----------------------------

    eggJumpSound = LoadSound("resources/dozenegg/sounds/jump.ogg");
    eggRespawnSound = LoadSound("resources/dozenegg/sounds/respawn.ogg");
    eggGameMusic = LoadMusicStream("resources/dozenegg/sounds/Cipher2.ogg");

    //----------------------------

    CURRENT_EGG_STATE = EGG_WAIT;

    floorPositionY = 650;
    levelHeight = 300;
    jumpHeight = 150;
    baseLevelY = 650;

    lastLanding = 0;
    lastFail = 0;

    eggPositionX = 1366 / 2;
    eggPositionY = baseLevelY;

    eggRotation = 0;
    nextRotation = 0;

    gravity = 18;
    velocityY = 0;

    currentEggLevel = 0;

    lifePoint = 12;

    score = 0;

    //----------------------------

    PlayMusicStream(eggGameMusic);

    //----------------------------

    auraScale = 0;
    auraOpacity = 0;

    //----------------------------

    sourceRec = (Rectangle) { 0.0f, 0.0f, eggTexture.width, eggTexture.height };

    //----------------------------

    camera.target = (Vector2){eggPositionX, eggPositionY};
    camera.offset = (Vector2){1366 / 2, 768 / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //----------------------------

    for (int i = 0; i < 160; i++)
    {
        gameLevels[i].position = (Vector2){1366 / 2, baseLevelY -(1 + i) * levelHeight};
        if(i % 10 == 0 && i != 0) {
            gameLevels[i].movementType = MOVE_STATIC;
        }
        else if(i % 2 == 0) {
            gameLevels[i].movementType = MOVE_LEFT_TO_RIGHT;
        }
        else {
            gameLevels[i].movementType = MOVE_RIGHT_TO_LEFT;
        }
        gameLevels[i].movementSpeed = i < 140 ? GetRandomValue(200, 400) + (100.0 * i / 30.0) : 1500;
        if(i == 144) {
            gameLevels[i].movementSpeed = 3000;
        }
        else if(i == 145) {
            gameLevels[i].movementType = MOVE_STATIC;
        }

        if(i > 2 && i < 50) {
            if(GetRandomValue(0, 100) < 15) { // 15%
                gameLevels[i].movementType = MOVE_STATIC;
                if(gameLevels[i - 1].movementType == MOVE_STATIC) { // previous level is static too
                    gameLevels[i].position.x = gameLevels[i - 1].position.x; // อยู่ตรงกันนะไอหนู ไม่งั้นพี่คงผ่านไม่ได้
                }
            }
        }
        // TraceLog(LOG_INFO, "Loaded Level %d : %d", i + 1, baseLevelY -(1 + i) * levelHeight);
    }
}

void eggMain()
{
    //----------------------------
    //-- ด่าน
    //----------------------------
    UpdateMusicStream(eggGameMusic);
    for(int i = currentEggLevel - 5; i < currentEggLevel + 10; i++) {

        if(i < 0 || i > 160) // no overflow
            continue;

        struct Level *currentEditingLevel = &gameLevels[i];

        if(currentEggLevel == i && i == 0) {
            continue;
        }

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
    //----------------------------.
    cameraTargetPositionY = eggPositionY;

    destRec = (Rectangle) { eggPositionX, eggPositionY, eggTexture.width, eggTexture.height };

    if (CURRENT_EGG_STATE == EGG_WAIT)
    {
        eggPositionY = baseLevelY;

        auraScale = LERP(auraScale, 2, 0.1);
        auraOpacity = LERP(auraOpacity, 0, 0.05);
        auraPosition.x = eggPositionX;

        updateRotation();

        if(currentEggLevel > 0) { // ไข่ follow a basket
            if(GetTime() - lastLanding >= 0.3) // smooth follow when just landing at a basket
                eggPositionX = gameLevels[currentEggLevel - 1].position.x;
            else
                eggPositionX = LERP(eggPositionX, gameLevels[currentEggLevel - 1].position.x, 0.6);
        }

        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
        {
            velocityY = -1.5;
            positionYToGo = baseLevelY - jumpHeight - levelHeight;
            // TraceLog(LOG_INFO, "jumping Highest point is : %d", positionYToGo);
            nextRotation += 360;
            PlaySound(eggJumpSound);

            CURRENT_EGG_STATE = EGG_JUMP;
        }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        CURRENT_GAME_STATE = GAME_SELECT;
        StopMusicStream(eggGameMusic);
    }
#if DEBUG
        if (IsKeyPressed(KEY_N))
        {
            baseLevelY -= levelHeight;
            eggPositionY = baseLevelY;
            currentEggLevel++;
            lastLanding = GetTime();

            score += (currentEggLevel <= 10 ? 10 : ((currentEggLevel/10)+1)*10);
        }
        if (IsKeyPressed(KEY_M))
        {
            for(int i = 0; i < 10; i++) {
                baseLevelY -= levelHeight;
                eggPositionY = baseLevelY;
                currentEggLevel++;
                lastLanding = GetTime();

                score += (currentEggLevel <= 10 ? 10 : ((currentEggLevel/10)+1)*10);
            }
        }
#endif
    }
    else if (CURRENT_EGG_STATE == EGG_JUMP)
    {
        updateRotation();

        velocityY -= gravity * GetFrameTime();
        eggPositionY += velocityY * abs(eggPositionY - positionYToGo) * 0.02;

        if (eggPositionY <= positionYToGo + 10)
        {
            CURRENT_EGG_STATE = EGG_FALL;
            resetGravity();
        }
    }
    else if (CURRENT_EGG_STATE == EGG_FALL)
    {
        updateRotation();

        updateGravity();

        if (eggPositionY >= baseLevelY - levelHeight) // back to basket Y, check for next state
        {
            if(abs(gameLevels[currentEggLevel].position.x - eggPositionX) <= basketWidth / 2) {
                baseLevelY -= levelHeight;
                eggPositionY = baseLevelY;
                CURRENT_EGG_STATE = EGG_NEXT_LEVEL;
            }
            else {
                lastFail = GetTime();
                CURRENT_EGG_STATE = EGG_FAIL;
            }
        }
    }
    else if (CURRENT_EGG_STATE == EGG_NEXT_LEVEL)
    {
        updateRotation();

        eggPositionY = baseLevelY;
        currentEggLevel++;
        lastLanding = GetTime();
        CURRENT_EGG_STATE = EGG_WAIT;
        score += (currentEggLevel <= 10 ? 10 : ((currentEggLevel/10)+1)*10); 
    }
    else if (CURRENT_EGG_STATE == EGG_FAIL)
    {
        updateGravity();

        if(lifePoint > 0) { // still have life point ! now we still dont have life point system
            CURRENT_EGG_STATE = EGG_FAIL_TO_WAIT;
        }
        else if (GetTime() - lastFail >= 1){ // no more point
            CURRENT_EGG_STATE = EGG_DIE;
        }
    }
    else if (CURRENT_EGG_STATE == EGG_FAIL_TO_WAIT) {

        cameraTargetPositionY = baseLevelY - 60;

        updateGravity();

        if(GetTime() - lastFail >= 2) {
            eggPositionX = gameLevels[currentEggLevel - 1].position.x;
            eggPositionY = baseLevelY - 60;

            auraPosition.x = eggPositionX;
            auraPosition.y = eggPositionY + 10;
            auraScale = 0;
            auraOpacity = 1;

            PlaySound(eggRespawnSound);

            resetGravity();
            lifePoint --;
            CURRENT_EGG_STATE = EGG_FAIL_TO_WAIT_2;
        }

#if DEBUG
        if (IsKeyPressed(KEY_R)) // reset
        {
            lastLanding = GetTime();
            CURRENT_EGG_STATE = EGG_WAIT;
            // eggInit();
        }
#endif
    }
    else if(CURRENT_EGG_STATE == EGG_FAIL_TO_WAIT_2) {
        updateGravity();
        eggPositionX = gameLevels[currentEggLevel - 1].position.x;

        auraScale = LERP(auraScale, 2, 0.1);
        auraOpacity = LERP(auraOpacity, 0, 0.05);
        auraPosition.x = eggPositionX;

        if (eggPositionY >= baseLevelY) {
            eggPositionY = baseLevelY;
            eggRotation = 0;
            nextRotation = 0;
            CURRENT_EGG_STATE = EGG_WAIT;
        }
    }
    else if(CURRENT_EGG_STATE == EGG_DIE) {
        updateGravity();
        if (IsKeyPressed(KEY_R)) {
            eggInit();
        }
    }

#if DEBUG

        if (IsKeyPressed(KEY_U)) {
            if (lifePoint != 12)
                lifePoint += 1;
        }
        else if (IsKeyPressed(KEY_D)) {
            if (lifePoint != 0)
                lifePoint -= 1;
        }

        if (IsKeyPressed(KEY_E))
            eggInit();
#endif

    //----------------------------
    //-- กล้อง
    //----------------------------
    if(CURRENT_EGG_STATE != EGG_FAIL && CURRENT_EGG_STATE != EGG_DIE) // when fail camera will not follow egg
        UpdateCameraCustom(&camera, cameraTargetPositionY - levelHeight / 2, GetFrameTime(), 1366, 768);

    //----------------------------
    // -- แสดงผล
    //----------------------------

    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(backgroundTexture, 0, 0, WHITE);

        BeginMode2D(camera);

            DrawText("USE <BACKSPACE> TO GIVEUP!", 450, -400, 20, WHITE);

            DrawText("YOU COME SO FAR!", 700, -2500, 20, WHITE);

            DrawText("WE HAVE A GIFT FOR YOU!\nIF YOU CAN REACH THE FINISH!", 400, -5750, 20, WHITE);

            DrawText("IT'S A CAKE!!", 400, -8750, 20, WHITE);

            DrawText("THERE IS NO CAKE! IT'S A LIE!! TRUST ME!!!", 400, -17750, 20, WHITE);

            DrawText("Please go back...", 400, -26750, 20, WHITE);

            DrawText("GO BACK! IT'S A LIE! THERE IS NO CAKE!!", 400, -38750, 20, WHITE);

            DrawTexturePro(eggTexture, sourceRec, destRec, (Vector2) { eggTexture.width / 2, eggTexture.height / 2 }, eggRotation, WHITE); // egg

            DrawTexture(basketTexture, 1366 / 2 - basketWidth / 2, 650 - basketHeight / 2 + 15, WHITE); // start basket

            DrawText("USE <SPACE> TO JUMP", 560, 700, 20, WHITE);

            DrawTextureEx(auraTexture, (Vector2) {auraPosition.x - auraScale * 27, auraPosition.y - auraScale * 27}, 0, auraScale, (Color) {255, 255, 255, auraOpacity * 255});

            for(int i = currentEggLevel - 2; i < currentEggLevel + 5; i++) {

                if(i < 0 || i > 145) // avoiding overflow
                    continue;
                DrawTexture(basketTexture, gameLevels[i].position.x - basketWidth / 2, gameLevels[i].position.y - basketHeight / 2 + 15, WHITE);

#if DEBUG

                    DrawText(FormatText("Level: %d Speed : %d", i + 1, gameLevels[i].movementSpeed), gameLevels[i].position.x - 100, gameLevels[i].position.y + 60, 20, BLACK);
                    DrawText(FormatText("X: %.2f Y : %.2f", gameLevels[i].position.x, gameLevels[i].position.y), gameLevels[i].position.x - 100, gameLevels[i].position.y + 85, 20, BLACK);
                
#endif

            }

        EndMode2D();

        DrawRectangleRec((Rectangle){ 0, 0, 300 - basketWidth / 2, 768}, (Color) { 0, 0, 0, 0.8 * 255 });
        DrawRectangleRec((Rectangle){ 1066 + basketWidth / 2, 0, 300 - basketWidth / 2, 768}, (Color) { 0, 0, 0, 0.8 * 255 });

        DrawRectangleRounded((Rectangle){ 1116 - 195, 5, 185, 55}, 0.3, 0, (Color) {33, 32, 31, 0.6 * 255 });
        DrawText(FormatText("Score : %d", score), 1116 - 185, 20, 25, RAYWHITE);

        if (CURRENT_EGG_STATE == EGG_DIE) {
            DrawRectangleRounded((Rectangle){ 380, 200, 600, 400}, 0.3, 0, (Color) {33, 32, 31, 0.9 * 255 });
            DrawText(FormatText("You Failed!\nYour score: %d\nPress <R> to RETRY", score), 430, 260, 50, RAYWHITE);
        }
        //DrawTexture(exitButtonTexture, 1136, 608, WHITE);

        circlePosX = 270;
        circlePosY = 5;

        //----------------------------
        // -- Life Point
        //----------------------------
        DrawRectangleRounded((Rectangle){ 255, 5, 155, 55}, 0.3, 0, (Color) {33, 32, 31, 0.6 * 255 }); // แผงไข่

        for (int i = 0; i < 12; i++) { // ไข่
            if (i >= 6) {
                circlePosY = 30;
                circlePosX = 270 + ((i - 6) * 25);
            }
            else {
                circlePosY = 5;
                circlePosX = 270 + (i * 25);
            }

            DrawCircle(circlePosX, circlePosY + 15, 10, (Color) {255, 255, 255, (lifePoint > i ? 1 : 0.3) * 255 });
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

void resetGravity() {
    velocityY = 0;
}

void updateGravity() {
    velocityY += gravity * GetFrameTime() * 0.8;
    eggPositionY += velocityY;
}

void updateRotation() {
    eggRotation = LERP(eggRotation, nextRotation, 4 * GetFrameTime());
}
