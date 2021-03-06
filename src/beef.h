#include "main.h"

#define MEAT_COUNT 10

// -----------------------

enum GAME_BEEF_PLAY_STATE {
    GAME_BEEF_PLAYING,
    GAME_BEEF_GAMEOVER
};

enum GAME_BEEF_PLAY_STATE CURRENT_BEEF_GAME_STATE;

// -----------------------

void generateMeat();

// -----------------------

enum BEEF_SIDE {
    FRONT,
    BACK
};

enum BEEF_STATE {
    BEEF_STATE_NORMAL,
    BEEF_STATE_ATE
};

enum BEEF_SIDE_STATE {
    BEEF_SIDE_STATE_RAW,
    BEEF_SIDE_STATE_COOKED,
    BEEF_SIDE_STATE_OVER_COOKED,
    BEEF_SIDE_STATE_OVER_COOKED_2,
    BEEF_SIDE_STATE_UNEATABLE
};

enum BEEF_TYPE {
    BEEF_TYPE_1,
    BEEF_TYPE_2,
    BEEF_TYPE_3,
    BEEF_TYPE_4
};

// -----------------------

struct BEEF {
    Vector2 position;

    enum BEEF_STATE state;
    
    enum BEEF_TYPE type;
    enum BEEF_SIDE currentSide;

    enum BEEF_STATE frontState;
    enum BEEF_STATE backState;

    double frontGrilledTime;
    double backGrilledTime;

    double timeNeedToCooked;
    double timeNeedToOverCooked;
    double timeNeedToOverCooked2;
    double timeNeedToUneatable;

    Sound grillSound;
};

struct BEEF beefs[MEAT_COUNT];

// -----------------------

Image tableImage;
Image panImage;
Image meatBowlImage;
Image sauceBowlImage;
Image rawMeatImage[4];
Image cookedMeatImage[4];
Image overCookedMeatImage[4];
Image overCooked2MeatImage[4];

// -----------------------

Texture2D tableTexture;
Texture2D panTexture;
Texture2D meatBowlTexture;
Texture2D sauceBowlTexture;
Texture2D rawMeatTexture[4];
Texture2D cookedMeatTexture[4];
Texture2D overCookedMeatTexture[4];
Texture2D overCooked2MeatTexture[4];

// -----------------------

Sound grillSound;
Sound gameOverSound;
Sound respawnSound;
Sound badScoreSound;
Sound goodScoreSound;
Sound gameStartSound;

// -----------------------

Vector2 mousePosition;
Vector2 lastMousePosition;

bool isDragging;
int draggingMeatIndex;

// -----------------------

int gameScore;
int gameHealth;
double gameTimeLeft;
double healthTimer;

// -----------------------

bool isMeatInGrill(struct BEEF);
bool isMeatInSauceBowl(struct BEEF beef);

void eatThisMeat(int meatIndex);
int scoreCalculateFromMeat(struct BEEF beef);
int healthCalculateFromMeat(struct BEEF beef);

int meatLeftCount();

// -----------------------

