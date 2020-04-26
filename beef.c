#include "beef.h"

void beefInit() {

    //Load Image
    tableImg = LoadImage("resources/roastedbeef/14.png");
    panImg = LoadImage("resources/roastedbeef/27_2.png");
    meatBowlImg = LoadImage("resources/roastedbeef/29.png");
    sauceBowlImg = LoadImage("resources/roastedbeef/32.png");
    rawMeat1Img = LoadImage("resources/roastedbeef/raw_meat/62_r.png");
    rawMeat2Img = LoadImage("resources/roastedbeef/raw_meat/68_r.png");
    rawMeat3Img = LoadImage("resources/roastedbeef/raw_meat/74_r.png");
    rawMeat4Img = LoadImage("resources/roastedbeef/raw_meat/80_r.png");

    //Resize for new screen size
    ImageResize(&tableImg, 1366, 720);
    ImageResize(&panImg, 1000, 400);
    ImageResize(&meatBowlImg, 500, 300);
    ImageResize(&sauceBowlImg, 400, 200);
    ImageResize(&rawMeat1Img, 140, 88);
    ImageResize(&rawMeat2Img, 140, 88);
    ImageResize(&rawMeat3Img, 140, 88);
    ImageResize(&rawMeat4Img, 140, 88);

    //Load to Vram
    table = LoadTextureFromImage(tableImg);
    pan = LoadTextureFromImage(panImg);
    meatBowl = LoadTextureFromImage(meatBowlImg);
    sauceBowl = LoadTextureFromImage(sauceBowlImg);
    rawMeat1 = LoadTextureFromImage(rawMeat1Img);
    rawMeat2 = LoadTextureFromImage(rawMeat2Img);
    rawMeat3 = LoadTextureFromImage(rawMeat3Img);
    rawMeat4 = LoadTextureFromImage(rawMeat4Img);

    //Unload From RAM
    UnloadImage(tableImg);
    UnloadImage(panImg);
    UnloadImage(meatBowlImg);
    UnloadImage(sauceBowlImg);
    UnloadImage(rawMeat1Img);
    UnloadImage(rawMeat2Img);
    UnloadImage(rawMeat3Img);
    UnloadImage(rawMeat4Img);

    //Position of beef
    beefArray[0].posX = SCREEN_WIDTH/2 - rawMeat1.width/2 - 400;
    beefArray[0].posY = SCREEN_HEIGHT/2 - rawMeat1.height/2 + 240;
    beefArray[1].posX = SCREEN_WIDTH/2 - rawMeat2.width/2 - 300;
    beefArray[1].posY = SCREEN_HEIGHT/2 - rawMeat2.height/2 + 200;
    beefArray[2].posX = SCREEN_WIDTH/2 - rawMeat3.width/2 - 400;
    beefArray[2].posY = SCREEN_HEIGHT/2 - rawMeat3.height/2 + 180;
    beefArray[3].posX = SCREEN_WIDTH/2 - rawMeat4.width/2 - 500;
    beefArray[3].posY = SCREEN_HEIGHT/2 - rawMeat4.height/2 + 180;

    rectanglePosX[0] = beefArray[0].posX + 18;
    rectanglePosX[1] = beefArray[1].posX + 25;
    rectanglePosX[2] = beefArray[2].posX + 15;
    rectanglePosX[3] = beefArray[3].posX + 25;

    rectanglePosY[0] = beefArray[0].posY;
    rectanglePosY[1] = beefArray[1].posY;
    rectanglePosY[2] = beefArray[2].posY - 4;
    rectanglePosY[3] = beefArray[3].posY;

    rectangleWidth[0] = rawMeat1.width - 23;
    rectangleWidth[1] = rawMeat2.width - 26;
    rectangleWidth[2] = rawMeat1.width - 23;
    rectangleWidth[3] = rawMeat1.width - 35;

    rectangleHeight[0] = rawMeat1.height - 10;
    rectangleHeight[1] = rawMeat2.height - 5;
    rectangleHeight[2] = rawMeat1.height - 10;
    rectangleHeight[3] = rawMeat1.height;

}

void beefMain() {
    //Rectangle Value for Drawing
    mPosition = GetMousePosition();

    BeginDrawing();

        ClearBackground(CHOCOLATE);
        DrawTexture(table, SCREEN_WIDTH/2 - table.width/2, SCREEN_HEIGHT/2 - table.height/2 + 80, WHITE);
        DrawTexture(pan, SCREEN_WIDTH/2 - pan.width/2 + 100, SCREEN_HEIGHT/2 - pan.height/2 - 30, WHITE);
        DrawTexture(meatBowl, SCREEN_WIDTH/2 - meatBowl.width/2 - 400, SCREEN_HEIGHT/2 - meatBowl.height/2 + 240, WHITE);
        DrawTexture(sauceBowl, SCREEN_WIDTH/2 - sauceBowl.width/2 + 400, SCREEN_HEIGHT/2 - sauceBowl.height/2 + 280, WHITE);
        
        DrawTexture(rawMeat1, beefArray[0].posX, beefArray[0].posY, WHITE);
        DrawRectangleLines(rectanglePosX[0], rectanglePosY[0], rectangleWidth[0], rectangleHeight[0], BLANK);
        
        DrawTexture(rawMeat2, beefArray[1].posX, beefArray[1].posY, WHITE);
        DrawRectangleLines(rectanglePosX[1], rectanglePosY[1], rectangleWidth[1], rectangleHeight[1], BLANK);

        DrawTexture(rawMeat3, beefArray[2].posX, beefArray[2].posY, WHITE);
        DrawRectangleLines(rectanglePosX[2], rectanglePosY[2], rectangleWidth[2], rectangleHeight[2], BLANK);

        DrawTexture(rawMeat4, beefArray[3].posX, beefArray[3].posY, WHITE);
        DrawRectangleLines(rectanglePosX[3], rectanglePosY[3], rectangleWidth[3], rectangleHeight[3], WHITE);

    EndDrawing();
}
