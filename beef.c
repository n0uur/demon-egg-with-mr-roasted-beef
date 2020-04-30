#include "beef.h"

void beefInit() {

    //Load Image
    tableImg = LoadImage("resources/roastedbeef/14.png");
    panImg = LoadImage("resources/roastedbeef/27_2.png");
    meatBowlImg = LoadImage("resources/roastedbeef/29.png");
    sauceBowlImg = LoadImage("resources/roastedbeef/32.png");
    rawMeatImg[0] = LoadImage("resources/roastedbeef/raw_meat/62_r.png");
    rawMeatImg[1] = LoadImage("resources/roastedbeef/raw_meat/68_r.png");
    rawMeatImg[2] = LoadImage("resources/roastedbeef/raw_meat/74_r.png");
    rawMeatImg[3] = LoadImage("resources/roastedbeef/raw_meat/80_r.png");

    //Resize for new screen size
    ImageResize(&tableImg, 1366, 720);
    ImageResize(&panImg, 1000, 400);
    ImageResize(&meatBowlImg, 500, 300);
    ImageResize(&sauceBowlImg, 400, 200);
    for(int i = 0; i < 4; i++)
        ImageResize(&rawMeatImg[i], 140, 88);

    //Load to Vram
    table = LoadTextureFromImage(tableImg);
    pan = LoadTextureFromImage(panImg);
    meatBowl = LoadTextureFromImage(meatBowlImg);
    sauceBowl = LoadTextureFromImage(sauceBowlImg);
    for(int i = 0; i < 4; i++)
        rawMeat[i] = LoadTextureFromImage(rawMeatImg[i]);
    
    //Unload From RAM
    UnloadImage(tableImg);
    UnloadImage(panImg);
    UnloadImage(meatBowlImg);
    UnloadImage(sauceBowlImg);
    for(int i = 0; i < 4; i++)
        UnloadImage(rawMeatImg[i]);

    //Position of beef
    for(int i = 0; i < 4; i++){
        beefArray[i].posX = SCREEN_WIDTH/2 - rawMeatImg[i].width/2 + calcBeefArrayPosX[i];
        beefArray[i].posY = SCREEN_HEIGHT/2 - rawMeatImg[i].height/2 + calcBeefArrayPosY[i];
        beefArray[i].CURRENT_SIDE = LEFT;
        beefArray[i].CURRENT_MEAT_STATE = RAW;
        rectanglePosX[i] = beefArray[i].posX + calcRectanglePosX[i];
        rectanglePosY[i] = beefArray[i].posY + calcRectanglePosY[i];
        rectangleHeight[i] = rawMeat[i].height + calcRectangleHeight[i];
        rectangleWidth[i] = rawMeat[i].width + calcRectangleWidth[i];
    }
}

void beefMain() {
    //Rectangle Value for Drawing
    mPosition = GetMousePosition();
    mouseBox.x = mPosition.x - mouseBox.width/2;
    mouseBox.y = mPosition.y - mouseBox.height/2;
    BeginDrawing();

        ClearBackground(CHOCOLATE);
        DrawTexture(table, SCREEN_WIDTH/2 - table.width/2, SCREEN_HEIGHT/2 - table.height/2 + 80, WHITE);
        DrawTexture(pan, SCREEN_WIDTH/2 - pan.width/2 + 100, SCREEN_HEIGHT/2 - pan.height/2 - 30, WHITE);
        DrawTexture(meatBowl, SCREEN_WIDTH/2 - meatBowl.width/2 - 400, SCREEN_HEIGHT/2 - meatBowl.height/2 + 240, WHITE);
        DrawTexture(sauceBowl, SCREEN_WIDTH/2 - sauceBowl.width/2 + 400, SCREEN_HEIGHT/2 - sauceBowl.height/2 + 280, WHITE);
        DrawRectangleRec(mouseBox, GREEN);
        
        for(int i = 0; i < 4; i++){
            DrawTexture(rawMeat[i], beefArray[i].posX, beefArray[i].posY, WHITE);
            DrawRectangleLines(rectanglePosX[i], rectanglePosY[i], rectangleWidth[i], rectangleHeight[i], WHITE);
            if (meatBox[i].collision&&meatBox[i].collisionArea == max&&IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                DrawText(FormatText("Collision Area: %d [%d]", max, i), SCREEN_WIDTH/2 - 100, 40 + 10, 20, BLACK);
                beefArray[i].posX = mouseBox.x;beefArray[i].posY = mouseBox.y;
                rectanglePosX[i] = beefArray[i].posX + calcRectanglePosX[i];
                rectanglePosY[i] = beefArray[i].posY + calcRectanglePosY[i];
                DrawRectangleRec(boxCollision, BLACK);
            }
        }
        beefAreaCheck();
    EndDrawing();
}

void beefAreaCheck(){
    max = 0;
    for(int i = 0; i < 4; i++){
        meatBox[i].collision = CheckCollisionRecs(mouseBox, meatBox[i].box);
        meatBox[i].box = (Rectangle){rectanglePosX[i], rectanglePosY[i], rectangleWidth[i], rectangleHeight[i]};
        if (meatBox[i].collision) boxCollision = GetCollisionRec(mouseBox, meatBox[i].box);
        meatBox[i].collisionArea = boxCollision.width*boxCollision.height;
        max = fmax(meatBox[i].collisionArea, max);
    }
}
