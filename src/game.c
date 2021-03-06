#include "main.h"

void gameInit() {

    const int screenWidth = 1366;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "ไข่ตัวร้ายกับนายเนื้อย่าง");

    InitAudioDevice();

    CURRENT_GAME_STATE = GAME_SELECT;

    SetTargetFPS(60);

    beefSplashPositionX = -300.0;
    beefSplashPositionY = 0.0;
    eggSplashPositionX = 100.0;
    eggSplashPositionY = 0.0;

    mainManuMusic = LoadMusicStream("resources/main_manu.ogg");
    isMainManuPlaying = true;
    PlayMusicStream(mainManuMusic);

    fontRSU = LoadFont("resources/fonts/CSChatThaiUI.ttf");
    fontBM = LoadFont("resources/fonts/rsu_bitmap.fnt");

    gameLogo = LoadImage("resources/ui/logo.png");
    beefSelect = LoadImage("resources/ui/select_beef.png");
    EggSelect = LoadImage("resources/ui/select_egg.png");

    ImageResize(&gameLogo, 512, 512);

    gameLogoTexture = LoadTextureFromImage(gameLogo);
    beefSelectTexture = LoadTextureFromImage(beefSelect);
    EggSelectTexture = LoadTextureFromImage(EggSelect);

    UnloadImage(gameLogo);
    UnloadImage(beefSelect);
    UnloadImage(EggSelect);
    
}

void gameMain() {

    gameInit();

    while (!WindowShouldClose())
    {
        if(CURRENT_GAME_STATE == GAME_SELECT) {
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | เลือกเกมที่ต้องการเล่น");
            gameSelectMain();
        }
        else if(CURRENT_GAME_STATE == GAME_EGG) {
            if(isMainManuPlaying) {
                StopMusicStream(mainManuMusic);
                isMainManuPlaying = false;
            }
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | ไข่ตัวร้าย");
            eggMain();
        }
        else if(CURRENT_GAME_STATE == GAME_BEEF) {
            if(isMainManuPlaying) {
                StopMusicStream(mainManuMusic);
                isMainManuPlaying = false;
            }
            SetWindowTitle("ไข่ตัวร้ายกับนายเนื้อย่าง | นายเนื้อย่าง");
            beefMain();
        }
    }

    gameDeinit();

}

void gameSelectMain() {
    
    if(!isMainManuPlaying) {
        PlayMusicStream(mainManuMusic);
        isMainManuPlaying = true;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        StopMusicStream(mainManuMusic);
        PlayMusicStream(mainManuMusic);
    }

    UpdateMusicStream(mainManuMusic);

    float currentMousePositionX = GetMousePosition().x;

    if(currentMousePositionX > 833) { // ไข่
        beefSplashPositionX = -700;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            eggInit();
            CURRENT_GAME_STATE = GAME_EGG;
        }
    }
    else if(currentMousePositionX < 533) { // เนื้อ
        beefSplashPositionX = 0;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            beefInit();
            CURRENT_GAME_STATE = GAME_BEEF;
        }
    }
    else {
        beefSplashPositionX = -300.0;
    }

    static float tmpBeefX = -400;
    static float tmpEggX = 200;

    tmpBeefX = (float)LERP(tmpBeefX, beefSplashPositionX, 0.05);
    tmpEggX = (float)LERP(tmpEggX, eggSplashPositionX, 0.05);

    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(EggSelectTexture, tmpEggX, eggSplashPositionY, WHITE);
        DrawTexture(beefSelectTexture, tmpBeefX, beefSplashPositionY, WHITE);

        DrawTexture(gameLogoTexture, 427, -100, WHITE);
        DrawTextEx(fontRSU, "PLEASE SELECT GAME", (Vector2){ 550, 600 }, 32, 2, WHITE);

        // if(IsKeyPressed(KEY_B)) CURRENT_GAME_STATE = GAME_BEEF; //Press B to run beef game

        // else if(IsKeyPressed(KEY_E)) CURRENT_GAME_STATE = GAME_EGG;

        // DrawText("Hi dad!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

}

void gameDeinit() {

    UnloadFont(fontRSU);
    UnloadFont(fontBM);

    CloseWindow();

}
