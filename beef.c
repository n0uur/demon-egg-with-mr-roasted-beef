#include "beef.h"

void beefInit() {

    //Load Image
    table_img = LoadImage("resources/roastedbeef/14.png");
    pan_img = LoadImage("resources/roastedbeef/27_2.png");
    meat_bowl_img = LoadImage("resources/roastedbeef/29.png");
    sauce_bowl_img = LoadImage("resources/roastedbeef/32.png");

    //Resize for new screen size
    ImageResize(&table_img, 1366, 720);
    ImageResize(&pan_img, 1000, 400);
    ImageResize(&meat_bowl_img, 500, 300);
    ImageResize(&sauce_bowl_img, 400, 200);

    //Load to Vram
    table = LoadTextureFromImage(table_img);
    pan = LoadTextureFromImage(pan_img);
    meat_bowl = LoadTextureFromImage(meat_bowl_img);
    sauce_bowl = LoadTextureFromImage(sauce_bowl_img);

    //Unload From RAM
    UnloadImage(table_img);
    UnloadImage(pan_img);
    UnloadImage(meat_bowl_img);
    UnloadImage(sauce_bowl_img);

}

void beefMain() {
    
    BeginDrawing();

        ClearBackground(CHOCOLATE);
        DrawTexture(table, GetScreenWidth()/2 - table.width/2, GetScreenHeight()/2 - table.height/2 + 80, WHITE);
        DrawTexture(pan, GetScreenWidth()/2 - pan.width/2 + 100, GetScreenHeight()/2 - pan.height/2 - 30, WHITE);
        DrawTexture(meat_bowl, GetScreenWidth()/2 - meat_bowl.width/2 - 400, GetScreenHeight()/2 - meat_bowl.height/2 + 240, WHITE);
        DrawTexture(sauce_bowl, GetScreenWidth()/2 - sauce_bowl.width/2 + 400, GetScreenHeight()/2 - sauce_bowl.height/2 + 280, WHITE);

    EndDrawing();
}
