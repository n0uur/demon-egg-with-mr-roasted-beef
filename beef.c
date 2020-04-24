#include "main.h"
#define CHOCOLATE  CLITERAL(Color){ 118, 57, 16, 255 }  //For bg
#define screenWidth GetScreenWidth()    //ScreenWidth
#define screenHeight GetScreenHeight()  //ScreenHeight
void beefMain() {
    //Load Image
    Image table_img = LoadImage("resources/roastedbeef/14.png");
    Image pan_img = LoadImage("resources/roastedbeef/27_2.png");
    Image meat_bowl_img = LoadImage("resources/roastedbeef/29.png");
    Image sauce_bowl_img = LoadImage("resources/roastedbeef/32.png");

    //Resize for new screen size
    ImageResize(&table_img, 1366, 720);
    ImageResize(&pan_img, 1000, 400);
    ImageResize(&meat_bowl_img, 500, 300);
    ImageResize(&sauce_bowl_img, 400, 200);

    //Load to Vram
    Texture2D table = LoadTextureFromImage(table_img);
    Texture2D pan = LoadTextureFromImage(pan_img);
    Texture2D meat_bowl = LoadTextureFromImage(meat_bowl_img);
    Texture2D sauce_bowl = LoadTextureFromImage(sauce_bowl_img);

    //Unload From RAM
    UnloadImage(table_img);
    UnloadImage(pan_img);
    UnloadImage(meat_bowl_img);
    UnloadImage(sauce_bowl_img);

    BeginDrawing();

        ClearBackground(CHOCOLATE);
        DrawTexture(table, screenWidth/2 - table.width/2, screenHeight/2 - table.height/2 + 80, WHITE);
        DrawTexture(pan, screenWidth/2 - pan.width/2 + 100, screenHeight/2 - pan.height/2 - 30, WHITE);
        DrawTexture(meat_bowl, screenWidth/2 - meat_bowl.width/2 - 400, screenHeight/2 - meat_bowl.height/2 + 240, WHITE);
        DrawTexture(sauce_bowl, screenWidth/2 - sauce_bowl.width/2 + 400, screenHeight/2 - sauce_bowl.height/2 + 280, WHITE);

    EndDrawing();
}
