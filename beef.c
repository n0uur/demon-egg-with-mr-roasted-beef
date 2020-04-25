#include "beef.h"
void flipMeat(Vector2 mousePosi, Texture2D meatT){
    Image meatI;
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            if(times == 0){
                meatI = GetTextureData(meatT);
                UnloadTexture(meatT);
                ImageFlipHorizontal(&meatI);
                meatT = LoadTextureFromImage(meatI);
                times++;
            }
        DrawTextureV(meatT, mousePosi, WHITE);
    }
    else if(IsMouseButtonUp(MOUSE_LEFT_BUTTON))times = 0;
}
void beefInit() {

    //Load Image
    tableImg = LoadImage("resources/roastedbeef/14.png");
    panImg = LoadImage("resources/roastedbeef/27_2.png");
    meatBowlImg = LoadImage("resources/roastedbeef/29.png");
    sauceBowlImg = LoadImage("resources/roastedbeef/32.png");
    rawMeat1Img = LoadImage("resources/roastedbeef/raw_meat/62_r.png");
    rawMeat2Img = LoadImage("resources/roastedbeef/raw_meat/68_r.png");

    //Resize for new screen size
    ImageResize(&tableImg, 1366, 720);
    ImageResize(&panImg, 1000, 400);
    ImageResize(&meatBowlImg, 500, 300);
    ImageResize(&sauceBowlImg, 400, 200);
    ImageResize(&rawMeat1Img, 140, 88);
    ImageResize(&rawMeat2Img, 140, 88);

    //Load to Vram
    table = LoadTextureFromImage(tableImg);
    pan = LoadTextureFromImage(panImg);
    meatBowl = LoadTextureFromImage(meatBowlImg);
    sauceBowl = LoadTextureFromImage(sauceBowlImg);
    rawMeat1 = LoadTextureFromImage(rawMeat1Img);
    rawMeat2 = LoadTextureFromImage(rawMeat2Img);

    //Unload From RAM
    UnloadImage(tableImg);
    UnloadImage(panImg);
    UnloadImage(meatBowlImg);
    UnloadImage(sauceBowlImg);
    UnloadImage(rawMeat1Img);
    UnloadImage(rawMeat2Img);

}

void beefMain() {
    Vector2 mPosition = { -100.0f, -100.0f };
    mPosition = GetMousePosition();

    BeginDrawing();

        ClearBackground(CHOCOLATE);
        DrawTexture(table, GetScreenWidth()/2 - table.width/2, GetScreenHeight()/2 - table.height/2 + 80, WHITE);
        DrawTexture(pan, GetScreenWidth()/2 - pan.width/2 + 100, GetScreenHeight()/2 - pan.height/2 - 30, WHITE);
        DrawTexture(meatBowl, GetScreenWidth()/2 - meatBowl.width/2 - 400, GetScreenHeight()/2 - meatBowl.height/2 + 240, WHITE);
        DrawTexture(sauceBowl, GetScreenWidth()/2 - sauceBowl.width/2 + 400, GetScreenHeight()/2 - sauceBowl.height/2 + 280, WHITE);
        DrawTexture(rawMeat1, GetScreenWidth()/2 - rawMeat1.width/2 - 400, GetScreenHeight()/2 - rawMeat1.height/2 + 240, WHITE);
        // DrawTexture(rawMeat2, GetScreenWidth()/2 - rawMeat2.width/2 - 300, GetScreenHeight()/2 - rawMeat2.height/2 + 200, WHITE);
        
        flipMeat(mPosition, rawMeat1); //codition get posi mouse click which meat has selected
        // flipMeat(mPosition, rawMeat2);

    EndDrawing();
}
