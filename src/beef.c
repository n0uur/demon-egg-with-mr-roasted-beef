#include "beef.h"

void beefInit() {

    //Load Image
    tableImage = LoadImage("resources/roastedbeef/14.png");
    panImage = LoadImage("resources/roastedbeef/27_2.png");
    meatBowlImage = LoadImage("resources/roastedbeef/29.png");
    sauceBowlImage = LoadImage("resources/roastedbeef/32.png");

    rawMeatImage[0] = LoadImage("resources/roastedbeef/meat/type1_r.png");
    rawMeatImage[1] = LoadImage("resources/roastedbeef/meat/type2_r.png");
    rawMeatImage[2] = LoadImage("resources/roastedbeef/meat/type3_r.png");
    rawMeatImage[3] = LoadImage("resources/roastedbeef/meat/type4_r.png");

    cookedMeatImage[0] = LoadImage("resources/roastedbeef/meat/type1_cooked.png");
    cookedMeatImage[1] = LoadImage("resources/roastedbeef/meat/type2_cooked.png");
    cookedMeatImage[2] = LoadImage("resources/roastedbeef/meat/type3_cooked.png");
    cookedMeatImage[3] = LoadImage("resources/roastedbeef/meat/type4_cooked.png");

    overCookedMeatImage[0] = LoadImage("resources/roastedbeef/meat/type1_over_cooked.png");
    overCookedMeatImage[1] = LoadImage("resources/roastedbeef/meat/type2_over_cooked.png");
    overCookedMeatImage[2] = LoadImage("resources/roastedbeef/meat/type3_over_cooked.png");
    overCookedMeatImage[3] = LoadImage("resources/roastedbeef/meat/type4_over_cooked.png");
    
    overCooked2MeatImage[0] = LoadImage("resources/roastedbeef/meat/type1_over_cooked_2.png");
    overCooked2MeatImage[1] = LoadImage("resources/roastedbeef/meat/type2_over_cooked_2.png");
    overCooked2MeatImage[2] = LoadImage("resources/roastedbeef/meat/type3_over_cooked_2.png");
    overCooked2MeatImage[3] = LoadImage("resources/roastedbeef/meat/type4_over_cooked_2.png");

    //Resize for new screen size
    ImageResize(&tableImage, 1366, 720);
    ImageResize(&panImage, 1000, 400);
    ImageResize(&meatBowlImage, 500, 300);
    ImageResize(&sauceBowlImage, 400, 200);

    //Load to Vram
    tableTexture = LoadTextureFromImage(tableImage);
    panTexture = LoadTextureFromImage(panImage);
    meatBowlTexture = LoadTextureFromImage(meatBowlImage);
    sauceBowlTexture = LoadTextureFromImage(sauceBowlImage);

    for(int i = 0; i < 4; i++) {
        ImageResize(&rawMeatImage[i], 140, 88);
        ImageResize(&cookedMeatImage[i], 140, 88);
        ImageResize(&overCookedMeatImage[i], 140, 88);
        ImageResize(&overCooked2MeatImage[i], 140, 88);

        rawMeatTexture[i] = LoadTextureFromImage(rawMeatImage[i]);
        cookedMeatTexture[i] = LoadTextureFromImage(cookedMeatImage[i]);
        overCookedMeatTexture[i] = LoadTextureFromImage(overCookedMeatImage[i]);
        overCooked2MeatTexture[i] = LoadTextureFromImage(overCooked2MeatImage[i]);

        UnloadImage(rawMeatImage[i]);
        UnloadImage(cookedMeatImage[i]);
        UnloadImage(overCookedMeatImage[i]);
        UnloadImage(overCooked2MeatImage[i]);
    }
    
    //Unload From RAM
    UnloadImage(tableImage);
    UnloadImage(panImage);
    UnloadImage(meatBowlImage);
    UnloadImage(sauceBowlImage);

    //----------------------------

    for(int i = 0; i < MEAT_COUNT; i++) {
        beefs[i].position.x = 270 + GetRandomValue(-120, 120);
        beefs[i].position.y = 650 + GetRandomValue(-50, 50);

        beefs[i].type = (GetRandomValue(0, 100) > 50) ? ((GetRandomValue(0, 100) > 50) ? BEEF_TYPE_1:BEEF_TYPE_2):((GetRandomValue(0, 100) > 50) ? BEEF_TYPE_3:BEEF_TYPE_4);
        
        beefs[i].currentSide = GetRandomValue(1, 2) == 1 ? FRONT : BACK;

        beefs[i].frontState = BEEF_SIDE_STATE_RAW;
        beefs[i].backState = BEEF_SIDE_STATE_RAW;

        beefs[i].frontGrilledTime = 0;
        beefs[i].backGrilledTime = 0;

        beefs[i].timeNeedToCooked = GetRandomValue(15, 30);
        beefs[i].timeNeedToOverCooked = beefs[i].timeNeedToCooked + GetRandomValue(5, 15);
        beefs[i].timeNeedToOverCooked2 = beefs[i].timeNeedToOverCooked + GetRandomValue(2, 8);
    }

    //----------------------------
}

void beefMain() {

#if GAME_DEBUG
    if(IsKeyPressed(KEY_R)) {
        for(int i = 0; i < MEAT_COUNT; i++) {
            beefs[i].position.x = 270 + GetRandomValue(-120, 120);
            beefs[i].position.y = 650 + GetRandomValue(-50, 50);

            beefs[i].type = (GetRandomValue(0, 100) > 50) ? ((GetRandomValue(0, 100) > 50) ? BEEF_TYPE_1:BEEF_TYPE_2):((GetRandomValue(0, 100) > 50) ? BEEF_TYPE_3:BEEF_TYPE_4);
            
            beefs[i].currentSide = GetRandomValue(1, 2) == 1 ? FRONT : BACK;

            beefs[i].frontState = BEEF_SIDE_STATE_RAW;
            beefs[i].backState = BEEF_SIDE_STATE_RAW;

            beefs[i].frontGrilledTime = 0;
            beefs[i].backGrilledTime = 0;

            beefs[i].timeNeedToCooked = GetRandomValue(15, 30);
            beefs[i].timeNeedToOverCooked = beefs[i].timeNeedToCooked + GetRandomValue(5, 15);
            beefs[i].timeNeedToOverCooked2 = beefs[i].timeNeedToOverCooked + GetRandomValue(2, 8);
        }
    }
#endif

    BeginDrawing();

        ClearBackground(CHOCOLATE);

        DrawTexture(tableTexture, 0, 80, WHITE);
        DrawTexture(panTexture, 1366/2 - panTexture.width / 2 + 100, 768/2 - panTexture.height/2 - 30, WHITE);
        DrawEllipseLines(1366 / 2 + 100, 768 / 2 - 50, 320, 110, WHITE); // เตา
        DrawTexture(meatBowlTexture, 1366 / 2 - meatBowlTexture.width / 2 - 400, 768/2 - meatBowlTexture.height/2 + 240, WHITE);
        DrawTexture(sauceBowlTexture, 1366 / 2 - sauceBowlTexture.width / 2 + 400, 768/2 - sauceBowlTexture.height/2 + 280, WHITE);
        DrawEllipseLines(1366 / 2 + 400, 768 / 2 - -300, 120, 50, WHITE); // น้ำจิ้ม

        for(int i = 0; i < MEAT_COUNT; i++) {
            
            if(beefs[i].state == BEEF_STATE_ATE)
                continue;

            Color overlayColor = beefs[i].currentSide == FRONT ? (beefs[i].frontState == BEEF_SIDE_STATE_UNEATABLE ? BLACK : WHITE):beefs[i].backState == BEEF_SIDE_STATE_UNEATABLE ? BLACK : WHITE;
            Texture2D textureToDraw = rawMeatTexture[beefs[i].type];
            if(beefs[i].currentSide == FRONT) {
                if(beefs[i].frontState == BEEF_SIDE_STATE_COOKED) {
                    textureToDraw = cookedMeatTexture[beefs[i].type];
                }
                else if(beefs[i].frontState == BEEF_SIDE_STATE_OVER_COOKED) {
                    textureToDraw = overCookedMeatTexture[beefs[i].type];
                }
                else if(beefs[i].frontState == BEEF_SIDE_STATE_OVER_COOKED_2) {
                    textureToDraw = overCooked2MeatTexture[beefs[i].type];
                }
            }
            else {
                if(beefs[i].backState == BEEF_SIDE_STATE_COOKED) {
                    textureToDraw = cookedMeatTexture[beefs[i].type];
                }
                else if(beefs[i].backState == BEEF_SIDE_STATE_OVER_COOKED) {
                    textureToDraw = overCookedMeatTexture[beefs[i].type];
                }
                else if(beefs[i].backState == BEEF_SIDE_STATE_OVER_COOKED_2) {
                    textureToDraw = overCooked2MeatTexture[beefs[i].type];
                }
            }
            DrawTextureRec(textureToDraw, (Rectangle) {0, 0, rawMeatTexture[beefs[i].type].width * (beefs[i].currentSide == FRONT ? 1:-1), rawMeatTexture[beefs[i].type].height}, (Vector2) {beefs[i].position.x - 70, beefs[i].position.y - 44}, overlayColor);
            // DrawTexture(rawMeatTexture[beefs[i].type], beefs[i].position.x - 70, beefs[i].position.y - 44, WHITE);
#if GAME_DEBUG
            DrawText(TextFormat("TYPE : %s", beefs[i].currentSide == FRONT ? "FRONT":"BACK"), beefs[i].position.x - 70, beefs[i].position.y - 44, 20, RED);
#endif
        }
            
        
    EndDrawing();
}
