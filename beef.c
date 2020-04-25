#include "beef.h"
void flip_meat(Vector2 mouse_posi, Texture2D meat_t){
    Image meat_i;
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            if(times == 0){
                meat_i = GetTextureData(meat_t);
                UnloadTexture(meat_t);
                ImageFlipHorizontal(&meat_i);
                meat_t = LoadTextureFromImage(meat_i);
                times++;
            }
        DrawTextureV(meat_t, mouse_posi, WHITE);
    }
    else if(IsMouseButtonUp(MOUSE_LEFT_BUTTON))times = 0;
}
void beefInit() {

    //Load Image
    table_img = LoadImage("resources/roastedbeef/14.png");
    pan_img = LoadImage("resources/roastedbeef/27_2.png");
    meat_bowl_img = LoadImage("resources/roastedbeef/29.png");
    sauce_bowl_img = LoadImage("resources/roastedbeef/32.png");
    raw_meat_1_img = LoadImage("resources/roastedbeef/raw_meat/62_r.png");
    raw_meat_2_img = LoadImage("resources/roastedbeef/raw_meat/68_r.png");

    //Resize for new screen size
    ImageResize(&table_img, 1366, 720);
    ImageResize(&pan_img, 1000, 400);
    ImageResize(&meat_bowl_img, 500, 300);
    ImageResize(&sauce_bowl_img, 400, 200);
    ImageResize(&raw_meat_1_img, 140, 88);
    ImageResize(&raw_meat_2_img, 140, 88);

    //Load to Vram
    table = LoadTextureFromImage(table_img);
    pan = LoadTextureFromImage(pan_img);
    meat_bowl = LoadTextureFromImage(meat_bowl_img);
    sauce_bowl = LoadTextureFromImage(sauce_bowl_img);
    raw_meat_1 = LoadTextureFromImage(raw_meat_1_img);
    raw_meat_2 = LoadTextureFromImage(raw_meat_2_img);

    //Unload From RAM
    UnloadImage(table_img);
    UnloadImage(pan_img);
    UnloadImage(meat_bowl_img);
    UnloadImage(sauce_bowl_img);
    UnloadImage(raw_meat_1_img);
    UnloadImage(raw_meat_2_img);

}

void beefMain() {
    Vector2 mPosition = { -100.0f, -100.0f };
    mPosition = GetMousePosition();

    BeginDrawing();

        ClearBackground(CHOCOLATE);
        DrawTexture(table, GetScreenWidth()/2 - table.width/2, GetScreenHeight()/2 - table.height/2 + 80, WHITE);
        DrawTexture(pan, GetScreenWidth()/2 - pan.width/2 + 100, GetScreenHeight()/2 - pan.height/2 - 30, WHITE);
        DrawTexture(meat_bowl, GetScreenWidth()/2 - meat_bowl.width/2 - 400, GetScreenHeight()/2 - meat_bowl.height/2 + 240, WHITE);
        DrawTexture(sauce_bowl, GetScreenWidth()/2 - sauce_bowl.width/2 + 400, GetScreenHeight()/2 - sauce_bowl.height/2 + 280, WHITE);
        DrawTexture(raw_meat_1, GetScreenWidth()/2 - raw_meat_1.width/2 - 400, GetScreenHeight()/2 - raw_meat_1.height/2 + 240, WHITE);
        DrawTexture(raw_meat_2, GetScreenWidth()/2 - raw_meat_2.width/2 - 300, GetScreenHeight()/2 - raw_meat_2.height/2 + 200, WHITE);

        flip_meat(mPosition, raw_meat_1); //codition get posi mouse click which meat has selected
        // flip_meat(mPosition, raw_meat_2);

    EndDrawing();
}
