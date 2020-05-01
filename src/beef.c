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

    generateMeat();

    //----------------------------

    mousePosition = GetMousePosition();
    lastMousePosition = mousePosition;

    isDragging = false;
    draggingMeatIndex = -1;
}

void beefMain() {

#if GAME_DEBUG
    if(IsKeyPressed(KEY_R)) {
        generateMeat();
    }
#endif

    //----------------------------
    //-- ความสุก
    //----------------------------
    for(int i = 0; i < MEAT_COUNT; i++) {
        if(isDragging && draggingMeatIndex == i)
            continue;

        if(!isMeatInGrill(beefs[i]))
            continue;

        struct BEEF *editingBeef = &beefs[i];

        if(editingBeef->currentSide == FRONT) {
            editingBeef->frontGrilledTime += GetFrameTime() / 2.0;
            editingBeef->backGrilledTime += GetFrameTime();
        }
        else {
            editingBeef->frontGrilledTime += GetFrameTime();
            editingBeef->backGrilledTime += GetFrameTime() / 2.0;
        }

        if(editingBeef->frontGrilledTime >= editingBeef->timeNeedToUneatable) {
            editingBeef->frontState = BEEF_SIDE_STATE_UNEATABLE;
        }
        else if(editingBeef->frontGrilledTime >= editingBeef->timeNeedToOverCooked2) {
            editingBeef->frontState = BEEF_SIDE_STATE_OVER_COOKED_2;
        }
        else if(editingBeef->frontGrilledTime >= editingBeef->timeNeedToOverCooked) {
            editingBeef->frontState = BEEF_SIDE_STATE_OVER_COOKED;
        }
        else if(editingBeef->frontGrilledTime >= editingBeef->timeNeedToCooked) {
            editingBeef->frontState = BEEF_SIDE_STATE_COOKED;
        }

        if(editingBeef->backGrilledTime >= editingBeef->timeNeedToUneatable) {
            editingBeef->backState = BEEF_SIDE_STATE_UNEATABLE;
        }
        else if(editingBeef->backGrilledTime >= editingBeef->timeNeedToOverCooked2) {
            editingBeef->backState = BEEF_SIDE_STATE_OVER_COOKED_2;
        }
        else if(editingBeef->backGrilledTime >= editingBeef->timeNeedToOverCooked) {
            editingBeef->backState = BEEF_SIDE_STATE_OVER_COOKED;
        }
        else if(editingBeef->backGrilledTime >= editingBeef->timeNeedToCooked) {
            editingBeef->backState = BEEF_SIDE_STATE_COOKED;
        }
    }

    //----------------------------
    //-- ลากเนื้อ
    //----------------------------

    mousePosition = GetMousePosition();

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        // flip
        beefs[draggingMeatIndex].currentSide = beefs[draggingMeatIndex].currentSide == FRONT ? BACK:FRONT;
        // dont forget to play sound and effect when put to tao fai

        isDragging = false;
        draggingMeatIndex = -1;
    }

    if(isDragging && draggingMeatIndex != -1) {
        beefs[draggingMeatIndex].position.x += mousePosition.x - lastMousePosition.x;
        beefs[draggingMeatIndex].position.y += mousePosition.y - lastMousePosition.y;
    }
    else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        for(int i = 0; i < MEAT_COUNT; i++) {
            if(CheckCollisionPointRec(mousePosition, (Rectangle) { beefs[i].position.x - 70, beefs[i].position.y - 44, 140, 88 })) {
                isDragging = true;
                draggingMeatIndex = i;
            }
        }
    }

    lastMousePosition = mousePosition;

    BeginDrawing();

        ClearBackground(CHOCOLATE);

        DrawTexture(tableTexture, 0, 80, WHITE);
        DrawTexture(panTexture, 1366/2 - panTexture.width / 2 + 100, 768/2 - panTexture.height/2 - 30, WHITE);
        
        DrawTexture(meatBowlTexture, 1366 / 2 - meatBowlTexture.width / 2 - 400, 768/2 - meatBowlTexture.height/2 + 240, WHITE);
        DrawTexture(sauceBowlTexture, 1366 / 2 - sauceBowlTexture.width / 2 + 400, 768/2 - sauceBowlTexture.height/2 + 280, WHITE);

#if GAME_DEBUG
        DrawEllipseLines(1366 / 2 + 100, 768 / 2 - 50, 320, 110, RED); // เตา
        DrawEllipseLines(1366 / 2 + 400, 768 / 2 - -300, 120, 50, RED); // น้ำจิ้ม
#endif

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
            DrawRectangleLines(beefs[i].position.x - 70, beefs[i].position.y - 44, 140, 88, (Color) {0, 255, 0, 255});

            DrawText(
                TextFormat("TYPE : %s\nGRILL : %s\nSAUCE : %s\nFRONT : %.2f\nBACK : %.2f\n%.2f %.2f %.2f %.2f",
                    beefs[i].currentSide == FRONT ? "FRONT":"BACK",
                    isMeatInGrill(beefs[i]) ? "IN":"OUT",
                    isMeatInSauceBowl(beefs[i]) ? "IN":"OUT",
                    beefs[i].frontGrilledTime,
                    beefs[i].backGrilledTime,
                    beefs[i].timeNeedToCooked,
                    beefs[i].timeNeedToOverCooked,
                    beefs[i].timeNeedToOverCooked2,
                    beefs[i].timeNeedToUneatable
                ),
                beefs[i].position.x - 60,
                beefs[i].position.y - 42,
                8,
                GREEN
            );
#endif
        }
        
    EndDrawing();
}

void generateMeat() {
    for(int i = 0; i < MEAT_COUNT; i++) {
        beefs[i].position.x = 270 + GetRandomValue(-120, 120);
        beefs[i].position.y = 650 + GetRandomValue(-50, 50);

        beefs[i].type = (GetRandomValue(0, 100) > 50) ? ((GetRandomValue(0, 100) > 50) ? BEEF_TYPE_1:BEEF_TYPE_2):((GetRandomValue(0, 100) > 50) ? BEEF_TYPE_3:BEEF_TYPE_4);
        
        beefs[i].currentSide = GetRandomValue(1, 2) == 1 ? FRONT : BACK;

        beefs[i].state = BEEF_STATE_NORMAL;

        beefs[i].frontState = BEEF_SIDE_STATE_RAW;
        beefs[i].backState = BEEF_SIDE_STATE_RAW;

        beefs[i].frontGrilledTime = 0;
        beefs[i].backGrilledTime = 0;

        beefs[i].timeNeedToCooked = GetRandomValue(5, 15);
        beefs[i].timeNeedToOverCooked = beefs[i].timeNeedToCooked + GetRandomValue(3, 8);
        beefs[i].timeNeedToOverCooked2 = beefs[i].timeNeedToOverCooked + GetRandomValue(2, 8);
        beefs[i].timeNeedToUneatable = beefs[i].timeNeedToOverCooked2 + GetRandomValue(5, 10);
    }
}

bool isMeatInGrill(struct BEEF beef) {

    // สูตร
    // p = (pow((x - h), 2) / pow(a, 2)) + (pow((y - k), 2) / pow(b, 2));
    // > 1 นอก , < 1 ใน , = 1 อยู่ตรงเส้นรอบวง
    // (x, y) คือจุดที่หา, (h, k) คือจุดศูนย์กลางวงรี, (a, b) คือขนาดของวงรีด้านกว้าง และสูงตามลำดับ
    //
    // if you hate math, you also hate programming too.
    //

    return (pow((beef.position.x - 783), 2) / pow(320, 2)) + (pow((beef.position.y - 334), 2) / pow(110, 2)) <= 1;
}

bool isMeatInSauceBowl(struct BEEF beef) {
    return (pow((beef.position.x - 1083), 2) / pow(120, 2)) + (pow((beef.position.y - 684), 2) / pow(50, 2)) <= 1;
}
